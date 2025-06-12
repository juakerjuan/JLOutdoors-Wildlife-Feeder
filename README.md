# 🦌 JLOutdoors Wildlife Feeder 🦌
## Automatic Wildlife Feeding System / Sistema Automático de Alimentación para Vida Silvestre

[![ESP32](https://img.shields.io/badge/ESP32-Development-blue)](https://www.espressif.com/en/products/socs/esp32)
[![Arduino](https://img.shields.io/badge/Arduino-Compatible-green)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 📋 Table of Contents / Tabla de Contenidos
- [Description / Descripción](#description--descripción)
- [Hardware Connections / Conexiones de Hardware](#hardware-connections--conexiones-de-hardware)
- [Software Setup / Configuración del Software](#software-setup--configuración-del-software)
- [Usage / Uso](#usage--uso)
- [Features / Características](#features--características)

## Description / Descripción
This project creates an automatic wildlife feeder using an ESP32 microcontroller. The system dispenses food at configurable intervals and can be controlled via a web interface.

Este proyecto crea un comedero automático para vida silvestre usando un microcontrolador ESP32. El sistema distribuye alimento en intervalos configurables y puede ser controlado mediante una interfaz web.

## Hardware Connections / Conexiones de Hardware
### ESP32 to DRV8825 Connections / Conexiones ESP32 a DRV8825
| ESP32 Pin | DRV8825 Pin | Description / Descripción |
|-----------|-------------|--------------------------|
| GPIO 26   | STEP        | Motor step control / Control de pasos del motor |
| GPIO 27   | DIR         | Motor direction / Dirección del motor |
| GPIO 14   | ENABLE      | Motor enable/disable / Habilitar/deshabilitar motor |
| GPIO 25   | -           | WiFi switch input / Entrada del switch WiFi |

### Power Connections / Conexiones de Energía
- Connect 12V battery to DRV8825 power input
- Conectar batería de 12V a la entrada de energía del DRV8825

## Software Setup / Configuración del Software
### Required Libraries / Bibliotecas Requeridas
1. Open Arduino IDE / Abrir el IDE de Arduino
2. Go to Tools -> Manage Libraries / Ir a Herramientas -> Gestionar Bibliotecas
3. Install / Instalar:
   - AsyncTCP
   - ESPAsyncWebServer
   - ArduinoJson

### Upload Process / Proceso de Subida
1. Install ESP32 Sketch Data Upload plugin / Instalar el plugin ESP32 Sketch Data Upload
2. Create `data` folder / Crear carpeta `data`
3. Copy `index.html` to `data` folder / Copiar `index.html` a la carpeta `data`
4. Configure IDE / Configurar IDE:
   - Board: ESP32 Dev Module
   - Port: Select your COM port
   - Upload Speed: 115200
5. Upload code / Subir código:
   - Click upload button / Hacer clic en el botón de subir
   - Wait for completion / Esperar a que termine

## Usage / Uso
1. Power on the system / Encender el sistema
2. Toggle WiFi switch / Activar el switch WiFi
3. Connect to WiFi "Feeder_ESP32" (password: 12345678)
4. Open browser and navigate to 192.168.4.1
5. Configure feeding times / Configurar tiempos de alimentación:
   - Motor run time (seconds) / Tiempo de giro del motor (segundos)
   - Interval time / Tiempo de intervalo
   - Time unit (hours/minutes) / Unidad de tiempo (horas/minutos)

## Features / Características
- 🌐 Web interface for easy configuration / Interfaz web para configuración fácil
- 🔄 Automatic feeding at set intervals / Alimentación automática en intervalos establecidos
- 🔋 Low power consumption / Bajo consumo de energía
- 🔌 Physical WiFi switch for power saving / Switch físico WiFi para ahorro de energía
- 🛠️ Easy to modify and customize / Fácil de modificar y personalizar

---
### 📺 YouTube Channel / Canal de YouTube
Subscribe to JLOutdoors for more wildlife and outdoor projects!
¡Suscríbete a JLOutdoors para más proyectos de vida silvestre y exteriores!

### ⚠️ Safety Notes / Notas de Seguridad
- Keep the feeder away from children / Mantener el comedero lejos de niños
- Regular maintenance required / Se requiere mantenimiento regular
- Check battery level periodically / Verificar nivel de batería periódicamente

### 🔧 Troubleshooting / Solución de Problemas
If the system doesn't work / Si el sistema no funciona:
1. Check all connections / Verificar todas las conexiones
2. Ensure battery is charged / Asegurar que la batería esté cargada
3. Verify WiFi switch position / Verificar posición del switch WiFi
4. Check Serial Monitor for errors / Revisar Monitor Serie para errores 