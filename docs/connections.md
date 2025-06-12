# Diagrama de Conexiones / Connection Diagram

## Componentes Necesarios / Required Components
1. ESP32
2. Driver DRV8825
3. Motor Paso a Paso (Stepper Motor)
4. Batería 12V
5. Interruptor (Switch)
6. Cables

## Conexiones / Connections

### ESP32 a DRV8825
- GPIO26 → STEP
- GPIO27 → DIR
- GPIO14 → ENABLE
- 3.3V → RESET, SLEEP
- GND → GND

### DRV8825 a Motor
- A1 → Bobina 1
- A2 → Bobina 1
- B1 → Bobina 2
- B2 → Bobina 2

### Alimentación / Power
- Batería 12V+ → VMOT del DRV8825
- Batería 12V- → GND del DRV8825

### Interruptor WiFi
- GPIO25 → Un terminal del interruptor
- GND → Otro terminal del interruptor

## Notas / Notes
- Usar cables de calibre adecuado para la corriente del motor
- Asegurar buenas conexiones a tierra
- Proteger las conexiones de la intemperie
- Verificar polaridad de la batería

## Diagrama / Diagram
El diagrama de conexiones se puede crear usando EasyEDA y se guardará en:
`docs/images/JLOutdoors_Feeder_Connections.png`

### Colores del Diagrama / Diagram Colors
- Rojo: Alimentación positiva (+)
- Negro: Tierra (GND)
- Azul: Señales de control
- Verde: Conexiones del motor 