#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

// Pines para el controlador DRV8825
const int STEP_PIN = 26;    // Controla los pasos del motor
const int DIR_PIN = 27;     // Controla la dirección del motor
const int ENABLE_PIN = 14;  // Habilita/deshabilita el motor para ahorrar energía
const int WIFI_SWITCH_PIN = 25;  // Pin para el switch del WiFi

// Configuración del AP
const char* ssid = "Feeder_ESP32";
const char* password = "12345678";

// Variables de configuración
struct Config {
    int timeWheel = 50;    // Tiempo de giro en segundos
    int timeTok = 10;      // Intervalo de tiempo
    char hourOrMin = 'm';  // 'h' para horas, 'm' para minutos
    bool wifiEnabled = true; // Estado del WiFi
} config;

// Dirección en EEPROM para guardar la configuración
const int EEPROM_SIZE = 512;
const int CONFIG_ADDRESS = 0;

// Crear servidor web
AsyncWebServer server(80);

// HTML como constante
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Feeder Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            background-color: #f0f0f0;
        }
        .container {
            background-color: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
            max-width: 600px;
            margin: 0 auto;
        }
        .brand {
            text-align: center;
            margin-bottom: 30px;
            padding: 20px;
            background: linear-gradient(45deg, #2c3e50, #3498db);
            border-radius: 8px;
            color: white;
        }
        .brand h1 {
            margin: 0;
            font-size: 2.5em;
            text-transform: uppercase;
            letter-spacing: 2px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        .brand p {
            margin: 5px 0 0 0;
            font-size: 1.2em;
            opacity: 0.9;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }
        input, select {
            width: 100%;
            padding: 8px;
            margin-bottom: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            width: 100%;
            font-size: 16px;
        }
        button:hover {
            background-color: #45a049;
        }
        .status {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            text-align: center;
        }
        .wifi-status {
            text-align: center;
            margin: 20px 0;
            padding: 10px;
            background-color: #f8f9fa;
            border-radius: 4px;
        }
        .wifi-status.on {
            color: #28a745;
        }
        .wifi-status.off {
            color: #dc3545;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="brand">
            <h1>JLOutdoors</h1>
            <p>Wildlife Feeder Control</p>
        </div>
        <div class="wifi-status" id="wifiStatus">
            WiFi Status: Checking...
        </div>
        <form id="configForm">
            <div class="form-group">
                <label for="timeWheel">Motor Run Time (seconds):</label>
                <input type="number" id="timeWheel" name="timeWheel" min="1" required>
            </div>
            <div class="form-group">
                <label for="timeTok">Interval Time:</label>
                <input type="number" id="timeTok" name="timeTok" min="1" required>
            </div>
            <div class="form-group">
                <label for="hourOrMin">Time Unit:</label>
                <select id="hourOrMin" name="hourOrMin">
                    <option value="m">Minutes</option>
                    <option value="h">Hours</option>
                </select>
            </div>
            <button type="submit">Save Configuration</button>
        </form>
        <div class="status" id="status"></div>
    </div>

    <script>
        // Función para verificar el estado del WiFi
        async function checkWiFiStatus() {
            const wifiStatus = document.getElementById('wifiStatus');
            try {
                const response = await fetch('/config');
                if (response.ok) {
                    wifiStatus.textContent = 'WiFi Status: Connected';
                    wifiStatus.className = 'wifi-status on';
                } else {
                    throw new Error('WiFi disconnected');
                }
            } catch (error) {
                wifiStatus.textContent = 'WiFi Status: Disconnected';
                wifiStatus.className = 'wifi-status off';
            }
        }

        // Verificar estado del WiFi cada 5 segundos
        setInterval(checkWiFiStatus, 5000);
        checkWiFiStatus();

        document.getElementById('configForm').onsubmit = async (e) => {
            e.preventDefault();
            const status = document.getElementById('status');
            status.textContent = 'Saving...';
            
            const data = {
                timeWheel: document.getElementById('timeWheel').value,
                timeTok: document.getElementById('timeTok').value,
                hourOrMin: document.getElementById('hourOrMin').value
            };

            try {
                const response = await fetch('/save', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(data)
                });
                
                if (response.ok) {
                    status.textContent = 'Configuration saved successfully!';
                    status.style.backgroundColor = '#dff0d8';
                } else {
                    throw new Error('Failed to save');
                }
            } catch (error) {
                status.textContent = 'Error saving configuration';
                status.style.backgroundColor = '#f2dede';
            }
        };

        // Load current configuration
        window.onload = async () => {
            try {
                const response = await fetch('/config');
                const config = await response.json();
                document.getElementById('timeWheel').value = config.timeWheel;
                document.getElementById('timeTok').value = config.timeTok;
                document.getElementById('hourOrMin').value = config.hourOrMin;
            } catch (error) {
                console.error('Error loading configuration:', error);
            }
        };
    </script>
</body>
</html>
)rawliteral";

// Función para guardar configuración en EEPROM
void saveConfig() {
    EEPROM.put(CONFIG_ADDRESS, config);
    EEPROM.commit();
}

// Función para cargar configuración desde EEPROM
void loadConfig() {
    EEPROM.get(CONFIG_ADDRESS, config);
}

// Función para activar el motor con movimiento suave
void activateMotor() {
    digitalWrite(ENABLE_PIN, LOW);  // Habilitar el motor (LOW = encendido)
    digitalWrite(DIR_PIN, HIGH);    // Dirección de giro
    
    // Girar el motor por timeWheel segundos con movimiento suave
    unsigned long startTime = millis();
    while (millis() - startTime < (config.timeWheel * 1000)) {
        // Movimiento suave con microstepping
        for(int i = 0; i < 4; i++) {  // 4 microsteps
            digitalWrite(STEP_PIN, HIGH);
            delayMicroseconds(1500);  // Velocidad más suave
            digitalWrite(STEP_PIN, LOW);
            delayMicroseconds(1500);
        }
    }
    
    digitalWrite(ENABLE_PIN, HIGH);  // Deshabilitar el motor (HIGH = apagado)
}

// Función para manejar el WiFi
void handleWiFi() {
    static bool lastWifiState = false;
    bool currentWifiState = digitalRead(WIFI_SWITCH_PIN);
    
    if (currentWifiState != lastWifiState) {
        if (currentWifiState) {
            // Activar WiFi
            WiFi.softAP(ssid, password);
            WiFi.setTxPower(WIFI_POWER_19dBm);
            server.begin();
            Serial.println("WiFi AP Started");
        } else {
            // Desactivar WiFi
            WiFi.softAPdisconnect(true);
            server.end();
            Serial.println("WiFi AP Stopped");
        }
        lastWifiState = currentWifiState;
        config.wifiEnabled = currentWifiState;
        saveConfig();
    }
}

void setup() {
    Serial.begin(115200);
    
    // Inicializar EEPROM
    EEPROM.begin(EEPROM_SIZE);
    loadConfig();
    
    // Configurar pines
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(WIFI_SWITCH_PIN, INPUT_PULLUP);  // Usar resistencia pull-up interna
    
    // Inicializar el motor en estado deshabilitado
    digitalWrite(ENABLE_PIN, HIGH);  // HIGH = motor deshabilitado
    
    // Iniciar WiFi si está habilitado
    if (config.wifiEnabled) {
        WiFi.softAP(ssid, password);
        WiFi.setTxPower(WIFI_POWER_19dBm);
        
        // Configurar rutas del servidor web
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send_P(200, "text/html", index_html);
        });
        
        server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
            String json = "{\"timeWheel\":" + String(config.timeWheel) + 
                         ",\"timeTok\":" + String(config.timeTok) + 
                         ",\"hourOrMin\":\"" + String(config.hourOrMin) + "\"}";
            request->send(200, "application/json", json);
        });
        
        server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request){}, NULL,
            [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
                DynamicJsonDocument doc(1024);
                deserializeJson(doc, (char*)data);
                
                config.timeWheel = doc["timeWheel"];
                config.timeTok = doc["timeTok"];
                config.hourOrMin = doc["hourOrMin"].as<const char*>()[0];
                
                saveConfig();
                request->send(200, "text/plain", "OK");
            });
        
        server.begin();
    }
    
    // Activar motor inicialmente
    activateMotor();
}

void loop() {
    // Manejar el switch del WiFi
    handleWiFi();
    
    static unsigned long lastActivation = 0;
    unsigned long currentTime = millis();
    unsigned long interval;
    
    // Calcular intervalo en milisegundos
    if (config.hourOrMin == 'h') {
        interval = config.timeTok * 3600000;  // Convertir horas a milisegundos
    } else {
        interval = config.timeTok * 60000;    // Convertir minutos a milisegundos
    }
    
    // Verificar si es tiempo de activar el motor
    if (currentTime - lastActivation >= interval) {
        activateMotor();
        lastActivation = currentTime;
    }
    
    // Modo de ahorro de energía
    if (!config.wifiEnabled || WiFi.softAPgetStationNum() == 0) {
        delay(1000);  // Espera más tiempo si el WiFi está desactivado o no hay clientes
    } else {
        delay(100);   // Respuesta más rápida si hay clientes
    }
} 
