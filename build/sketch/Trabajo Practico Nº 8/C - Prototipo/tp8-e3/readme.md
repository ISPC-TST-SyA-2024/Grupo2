#line 1 "d:\\Laura\\Carrera Telecomunicaciones\\PRIMER AÑO\\sensores y actuadores\\Grupo2\\Trabajo Practico Nº 8\\C - Prototipo\\tp8-e3\\readme.md"
## **Documentación: Implementación del Sensor de Lluvia Resistivo (YL-83)**

### **Descripción General**

Este proyecto tiene como objetivo simular el comportamiento de un **sensor de lluvia resistivo** (YL-83) utilizando el entorno de simulación **Wokwi**. Dado que Wokwi no cuenta con un modelo específico para este sensor, se emplea un **potenciómetro virtual** (slider) para emular las variaciones en la resistencia causadas por la lluvia.

El sistema está diseñado para leer estos valores analógicos y mostrarlos en un display **LCD 16x2 I2C**. La lectura simula el nivel de lluvia detectado por el sensor.

### **Objetivo**

Configurar y simular el sensor de lluvia resistivo en un entorno de simulación y validar su funcionamiento, mostrando los datos en una pantalla LCD.

### **Diagrama de Conexión**

| Componente | Pin en ESP32 |
| --- | --- |
| Slider (Deslizador) | A0 (GPIO 34) |
| Pantalla LCD (I2C) | SDA - GPIO 21, SCL - GPIO 22 |

### **Código Fuente**  

```cpp  

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración del LCD I2C (dirección 0x27 y tamaño 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin del deslizador (A0 en ESP32)
const int pinSlider = 34;

void setup() {
  // Inicialización de la comunicación serial
  Serial.begin(115200);

  // Inicialización de la pantalla LCD
  lcd.init();
  lcd.backlight();
  
  // Mensaje inicial en LCD
  lcd.setCursor(0, 0);
  lcd.print("Lluvia Nivel:");
}

void loop() {
  // Leer el valor del deslizador (0 a 4095)
  int valorSensor = analogRead(pinSlider);
  
  // Convertir el valor a porcentaje (0 a 100%)
  int nivelLluvia = map(valorSensor, 0, 4095, 0, 100);

  // Imprimir el nivel de lluvia en el monitor serial
  Serial.print("Nivel de lluvia: ");
  Serial.println(nivelLluvia);

  // Mostrar el nivel de lluvia en la pantalla LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpiar la línea
  lcd.setCursor(0, 1);
  lcd.print(nivelLluvia);
  lcd.print("%");

  // Esperar antes de la próxima lectura
  delay(500);
}
```


### **Simulación en Wokwi**

- Se utilizó el siguiente **JSON** para configurar la simulación en Wokwi, donde se incluye un deslizador y una pantalla LCD I2C conectados al ESP32.

  
<div style="text-align: center;">
  <img src="https://github.com/ISPC-TST-SyA-2024/Grupo2/blob/main/Trabajo%20Practico%20N%C2%BA%208/B%20-%20Investigacion/tp8-e3/lib/Wokwi.png" alt="Wokwi" style="width: 100%;">
</div>  

```json

{
  "components": [
    {
      "type": "esp32",
      "id": "esp32",
      "x": 0,
      "y": -96,
      "label": "ESP32"
    },
    {
      "type": "i2c-lcd",
      "id": "lcd",
      "x": 240,
      "y": -128,
      "label": "LCD",
      "wires": [
        ["esp32", "21", "sda"],
        ["esp32", "22", "scl"]
      ]
    },
    {
      "type": "slider",
      "id": "slider1",
      "x": 240,
      "y": 160,
      "min": 0,
      "max": 4095,
      "value": 0,
      "label": "Rain Sensor",
      "pin": "A0"
    }
  ]
}



```


### **Validación**

- Mueve el deslizador para cambiar el valor leído por el ESP32.
- Observa cómo el valor de porcentaje de lluvia varía en la pantalla LCD de 0% a 100%, dependiendo de la posición del deslizador.
- El sistema es considerado validado cuando los valores cambian correctamente y se reflejan en la pantalla LCD.

### **Conclusiones**  

En esta simulación Permite emular el comportamiento del sensor de lluvia resitivo utilizando un deslizador.
El codigo pretende ser simple de entender para luego poder ser adaptado a un caso mas complejo y su eventual migracion a un entorno físico.

