# Informe Técnico: Sistema de Riego con ESP32

## Objetivo
El código implementa un **sistema de riego automatizado** utilizando un ESP32, simulando el control de una bomba de riego en base a sensores de lluvia y humedad del suelo, con visualización en pantalla LCD.

## Componentes Utilizados en la Simulación
- **ESP32**
- **Potenciómetro** para simular el sensor de humedad del suelo (YL-69)
- **Switch** para simular el sensor de lluvia (YL-83)
- **Potenciómetro** para simular el sensor de nivel del tanque
- **Pantalla LCD 16x2** (con I2C)
- **Relé** para controlar la bomba de riego

## Lógica de Funcionamiento

1. **Verificación de lluvia**: Si se detecta lluvia (entrada digital), el sistema apaga el riego.
   
2. **Verificación del nivel del tanque**: Si el tanque tiene menos del 20% de agua, el sistema no hace nada. Si tiene más del 20%, continúa la verificación de la humedad del suelo.

3. **Control del riego**:
   - Si la humedad del suelo es menor o igual al 15%, la bomba se activa (riego).
   - Si la bomba está activa, continúa el riego hasta que la humedad del suelo alcance el 70%, momento en que se apaga.

## Estructura de Salida en la Pantalla LCD
- Si está lloviendo: 
  - "Lluvia detectada" (1er renglón)
  - "Riego desactivado" (2do renglón)
- Si no llueve:
  - Se muestra la **humedad del suelo** en porcentaje (1er renglón).
  - El **nivel del tanque** en porcentaje (2do renglón).

## Consideraciones de Simulación
En la simulación, se reemplazan los sensores por **potenciómetros** para el nivel del tanque y la humedad del suelo, y un **switch** para la detección de lluvia.

## Conclusión
Este sistema simulado permite un control automático del riego basado en condiciones climáticas y del suelo, optimizando el uso del agua mediante la lógica de control establecida.
