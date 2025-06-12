# 🦌 JLOutdoors Wildlife Feeder / Comedero Automático JLOutdoors

## 📋 Table of Contents / Tabla de Contenidos
- [Description / Descripción](#description--descripción)
- [Materials / Materiales](#materials--materiales)
- [Connections / Conexiones](#connections--conexiones)
- [Installation / Instalación](#installation--instalación)
- [Usage / Uso](#usage--uso)
- [Features / Características](#features--características)

## Description / Descripción
This project creates an automatic wildlife feeder using an ESP32 and a stepper motor. The system is controlled through a web page that you can open from your phone or computer.

Este proyecto permite crear un comedero automático para vida silvestre usando un ESP32 y un motor paso a paso. El sistema se controla mediante una página web que puedes abrir desde tu teléfono o computadora.

## Materials / Materiales
| English | Español |
|---------|---------|
| ESP32 | ESP32 |
| DRV8825 Driver | Driver DRV8825 |
| Stepper Motor | Motor paso a paso |
| 12V Battery | Batería 12V |
| Switch (optional) | Interruptor (opcional) |
| Wires | Cables |

## Connections / Conexiones
| ESP32 | DRV8825 | Description / Descripción |
|-------|----------|--------------------------|
| GPIO26 | STEP | Motor step control / Control de pasos |
| GPIO27 | DIR | Motor direction / Dirección del motor |
| GPIO14 | ENABLE | Motor enable/disable / Habilitar/deshabilitar |
| 3.3V | RESET, SLEEP | Reset and sleep pins / Pines de reset y sleep |
| GND | GND | Ground / Tierra |

## Installation / Instalación

### 1. Install Arduino IDE / Instalar Arduino IDE
1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
   Descarga Arduino IDE desde [arduino.cc](https://www.arduino.cc/en/software)
2. Install the program
   Instala el programa

### 2. Install ESP32 Drivers / Instalar Drivers ESP32
1. Download CP210x drivers from [Silicon Labs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
   Descarga los drivers CP210x desde [Silicon Labs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
2. Install the drivers
   Instala los drivers
3. Restart your computer
   Reinicia tu computadora

### 3. Configure ESP32 / Configurar ESP32
1. Open Arduino IDE / Abre Arduino IDE
2. Go to File > Preferences / Ve a Archivo > Preferencias
3. Add to "Additional URLs" / Agrega en "URLs adicionales":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools > Board > Boards Manager / Ve a Herramientas > Placa > Gestor de tarjetas
5. Search for "esp32" and install "ESP32 by Espressif Systems"
   Busca "esp32" e instala "ESP32 by Espressif Systems"

### 4. Install Libraries / Instalar Bibliotecas
1. Go to Tools > Manage Libraries / Ve a Herramientas > Gestionar Bibliotecas
2. Search and install these libraries / Busca e instala estas bibliotecas:
   - AsyncTCP
   - ESPAsyncWebServer
   - ArduinoJson

### 5. Upload Code / Subir Código
1. Download files from this repository
   Descarga los archivos de este repositorio
2. Open `JLOutdoors_Feeder.ino` in Arduino IDE
   Abre `JLOutdoors_Feeder.ino` en Arduino IDE
3. Select your ESP32 board in Tools > Board
   Selecciona tu placa ESP32 en Herramientas > Placa
4. Select the correct COM port in Tools > Port
   Selecciona el puerto COM correcto en Herramientas > Puerto
5. Click the upload button (arrow)
   Haz clic en el botón de subir (flecha)

### 6. Upload Web Files / Subir Archivos Web
1. Install "ESP32 Sketch Data Upload" from Tools > Manage Libraries
   Instala "ESP32 Sketch Data Upload" desde Herramientas > Gestionar Bibliotecas
2. Create a folder called `data` in the same location as the .ino file
   Crea una carpeta llamada `data` en la misma ubicación que el archivo .ino
3. Copy `index.html` into the `data` folder
   Copia `index.html` dentro de la carpeta `data`
4. Click Tools > ESP32 Sketch Data Upload
   Haz clic en Herramientas > ESP32 Sketch Data Upload

## Usage / Uso
1. Connect the battery / Conecta la batería
2. Turn on the switch (if installed) / Enciende el interruptor (si lo instalaste)
3. Connect to WiFi "Feeder_ESP32" (password: 12345678)
   Conéctate al WiFi "Feeder_ESP32" (contraseña: 12345678)
4. Open 192.168.4.1 in your browser
   Abre 192.168.4.1 en tu navegador
5. Configure feeding times
   Configura los tiempos de alimentación

## Features / Características
| English | Español |
|---------|---------|
| WiFi control from any device | Control por WiFi desde cualquier dispositivo |
| Automatic energy saving | Ahorro de energía automático |
| Easy configuration | Fácil configuración |
| Simple web interface | Interfaz web simple |
| Battery powered | Funciona con batería |

## 📺 YouTube Channel / Canal de YouTube
Visit [JLOutdoors](https://www.youtube.com/@JLOutdoors) for more projects and tutorials.
Visita [JLOutdoors](https://www.youtube.com/@JLOutdoors) para más proyectos y tutoriales.

## ⚠️ Important Notes / Notas Importantes
| English | Español |
|---------|---------|
| Keep the battery charged | Mantén la batería cargada |
| Protect the system from rain | Protege el sistema de la lluvia |
| Clean the feeder regularly | Limpia el comedero regularmente |
| Don't touch wires with battery connected | No toques los cables con la batería conectada |

## ❓ Help / Ayuda
If you have problems / Si tienes problemas:

### Common Issues / Problemas Comunes

#### 1. ESP32 Not Detected / ESP32 No Detectado
If you see "Failed to connect to ESP32" or "No serial data received":
Si ves "Failed to connect to ESP32" o "No serial data received":

1. Hold the BOOT button on ESP32
   Mantén presionado el botón BOOT en el ESP32
2. Click the upload button in Arduino IDE
   Haz clic en el botón de subir en Arduino IDE
3. When you see "Connecting..." release the BOOT button
   Cuando veas "Connecting..." suelta el botón BOOT

#### 2. Wrong COM Port / Puerto COM Incorrecto
1. Open Device Manager / Abre el Administrador de Dispositivos
2. Look under "Ports (COM & LPT)"
   Busca en "Puertos (COM y LPT)"
3. Connect/disconnect ESP32 to see which port appears/disappears
   Conecta/desconecta el ESP32 para ver qué puerto aparece/desaparece
4. Select the correct port in Arduino IDE
   Selecciona el puerto correcto en Arduino IDE

#### 3. Driver Issues / Problemas con Drivers
1. Download CP210x drivers from [Silicon Labs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
   Descarga los drivers CP210x desde [Silicon Labs](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
2. Uninstall existing drivers
   Desinstala los drivers existentes
3. Install new drivers
   Instala los nuevos drivers
4. Restart computer
   Reinicia la computadora

#### 4. USB Cable Issues / Problemas con Cable USB
1. Try a different USB cable
   Prueba un cable USB diferente
2. Some cables are charge-only, make sure yours supports data
   Algunos cables son solo para carga, asegúrate que el tuyo soporte datos

#### 5. ESP32 Board Settings / Configuración de la Placa ESP32
Make sure these settings are correct / Asegúrate que estas configuraciones sean correctas:
- Board: "ESP32 Dev Module"
- Upload Speed: "115200"
- CPU Frequency: "240MHz (WiFi/BT)"
- Flash Frequency: "80MHz"
- Flash Mode: "QIO"
- Flash Size: "4MB (32Mb)"
- Partition Scheme: "Default 4MB with spiffs"
- Core Debug Level: "None"
- PSRAM: "Disabled"

### General Troubleshooting / Solución de Problemas General
1. Check all connections / Verifica todas las conexiones
2. Make sure battery is charged / Asegúrate de que la batería esté cargada
3. Restart ESP32 / Reinicia el ESP32
4. Check serial monitor in Arduino IDE / Revisa el monitor serial en Arduino IDE
5. If ESP32 is not detected, install CP210x drivers / Si el ESP32 no es detectado, instala los drivers CP210x 