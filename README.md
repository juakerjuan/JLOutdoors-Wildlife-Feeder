# 🦌 Comedero Automático para Vida Silvestre JLOutdoors

## 📋 Contenido
- [Descripción](#descripción)
- [Materiales Necesarios](#materiales-necesarios)
- [Conexiones](#conexiones)
- [Instrucciones de Instalación](#instrucciones-de-instalación)
- [Uso](#uso)
- [Características](#características)

## 📝 Descripción
Este proyecto permite crear un comedero automático para vida silvestre usando un ESP32 y un motor paso a paso. El sistema se controla mediante una página web que puedes abrir desde tu teléfono o computadora.

## 🛠️ Materiales Necesarios
- ESP32
- Driver DRV8825
- Motor paso a paso
- Batería 12V
- Interruptor (opcional)
- Cables

## 🔌 Conexiones
Conecta los componentes así:

| ESP32 | DRV8825 |
|-------|----------|
| GPIO26 | STEP |
| GPIO27 | DIR |
| GPIO14 | ENABLE |
| 3.3V | RESET, SLEEP |
| GND | GND |

## 📱 Instrucciones de Instalación

### 1. Instalar Arduino IDE
1. Descarga Arduino IDE desde [arduino.cc](https://www.arduino.cc/en/software)
2. Instala el programa

### 2. Configurar ESP32 en Arduino
1. Abre Arduino IDE
2. Ve a Archivo > Preferencias
3. En "URLs adicionales" agrega:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Ve a Herramientas > Placa > Gestor de tarjetas
5. Busca "esp32" e instala "ESP32 by Espressif Systems"

### 3. Instalar Bibliotecas
1. Ve a Herramientas > Gestionar Bibliotecas
2. Busca e instala estas bibliotecas:
   - AsyncTCP
   - ESPAsyncWebServer
   - ArduinoJson

### 4. Subir el Código
1. Descarga los archivos de este repositorio
2. Abre `JLOutdoors_Feeder.ino` en Arduino IDE
3. Selecciona tu placa ESP32 en Herramientas > Placa
4. Haz clic en el botón de subir (flecha)

### 5. Subir Archivos Web
1. Instala "ESP32 Sketch Data Upload" desde Herramientas > Gestionar Bibliotecas
2. Crea una carpeta llamada `data` en la misma ubicación que el archivo .ino
3. Copia el archivo `index.html` dentro de la carpeta `data`
4. Haz clic en Herramientas > ESP32 Sketch Data Upload

## 🚀 Uso
1. Conecta la batería
2. Enciende el interruptor (si lo instalaste)
3. Conéctate al WiFi "Feeder_ESP32" (contraseña: 12345678)
4. Abre 192.168.4.1 en tu navegador
5. Configura los tiempos de alimentación

## ⭐ Características
- Control por WiFi desde cualquier dispositivo
- Ahorro de energía automático
- Fácil configuración
- Interfaz web simple
- Funciona con batería

## 📺 Canal de YouTube
Visita [JLOutdoors](https://www.youtube.com/@JLOutdoors) para más proyectos y tutoriales.

## ⚠️ Notas Importantes
- Mantén la batería cargada
- Protege el sistema de la lluvia
- Limpia el comedero regularmente
- No toques los cables con la batería conectada

## ❓ Ayuda
Si tienes problemas:
1. Verifica todas las conexiones
2. Asegúrate de que la batería esté cargada
3. Reinicia el ESP32
4. Revisa el monitor serial en Arduino IDE

---

# 🦌 JLOutdoors Wildlife Feeder

[English version below]

## 📋 Table of Contents
- [Description](#description)
- [Required Materials](#required-materials)
- [Connections](#connections)
- [Installation Instructions](#installation-instructions)
- [Usage](#usage)
- [Features](#features)

## 📝 Description
This project creates an automatic wildlife feeder using an ESP32 and a stepper motor. The system is controlled through a web page that you can open from your phone or computer.

## 🛠️ Required Materials
- ESP32
- DRV8825 Driver
- Stepper Motor
- 12V Battery
- Switch (optional)
- Wires

## 🔌 Connections
Connect the components as follows:

| ESP32 | DRV8825 |
|-------|----------|
| GPIO26 | STEP |
| GPIO27 | DIR |
| GPIO14 | ENABLE |
| 3.3V | RESET, SLEEP |
| GND | GND |

## 📱 Installation Instructions

### 1. Install Arduino IDE
1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the program

### 2. Configure ESP32 in Arduino
1. Open Arduino IDE
2. Go to File > Preferences
3. Add to "Additional URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools > Board > Boards Manager
5. Search for "esp32" and install "ESP32 by Espressif Systems"

### 3. Install Libraries
1. Go to Tools > Manage Libraries
2. Search and install these libraries:
   - AsyncTCP
   - ESPAsyncWebServer
   - ArduinoJson

### 4. Upload Code
1. Download files from this repository
2. Open `JLOutdoors_Feeder.ino` in Arduino IDE
3. Select your ESP32 board in Tools > Board
4. Click the upload button (arrow)

### 5. Upload Web Files
1. Install "ESP32 Sketch Data Upload" from Tools > Manage Libraries
2. Create a folder called `data` in the same location as the .ino file
3. Copy `index.html` into the `data` folder
4. Click Tools > ESP32 Sketch Data Upload

## 🚀 Usage
1. Connect the battery
2. Turn on the switch (if installed)
3. Connect to WiFi "Feeder_ESP32" (password: 12345678)
4. Open 192.168.4.1 in your browser
5. Configure feeding times

## ⭐ Features
- WiFi control from any device
- Automatic energy saving
- Easy configuration
- Simple web interface
- Battery powered

## 📺 YouTube Channel
Visit [JLOutdoors](https://www.youtube.com/@JLOutdoors) for more projects and tutorials.

## ⚠️ Important Notes
- Keep the battery charged
- Protect the system from rain
- Clean the feeder regularly
- Don't touch wires with battery connected

## ❓ Help
If you have problems:
1. Check all connections
2. Make sure battery is charged
3. Restart ESP32
4. Check serial monitor in Arduino IDE 