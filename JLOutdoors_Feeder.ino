#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

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
    
    // Inicializar LittleFS
    if(!LittleFS.begin(true)){
        Serial.println("LittleFS Mount Failed");
        return;
    }
    
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
            request->send(LittleFS, "/index.html", "text/html");
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