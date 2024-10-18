https://wokwi.com/projects/412083807539505153

Link correspondiente a la tarea 1, realizada en la plataforma de wokwi.

Código utilizado para la simulación
from machine import Pin, ADC
import time

sensorPin = 34  # Pin del sensor (potenciómetro) en el ESP32
ledPin = 17     # Pin del LED
threshold = 2000  # Umbral de humedad

# Configurar el pin del LED como salida
led = Pin(ledPin, Pin.OUT)

# Configurar el pin del sensor como entrada analógica
sensor = ADC(Pin(sensorPin))
sensor.width(ADC.WIDTH_12BIT)  # Ajusta la resolución de lectura
sensor.atten(ADC.ATTN_11DB)    # Ajusta la atenuación para rango de voltaje (0 - 3.6V)

while True:
    sensorValue = sensor.read()  # Leer el valor analógico del sensor (0-4095)
    print("Humedad del suelo (simulada):", sensorValue)
    
    # Control del LED según el valor del sensor
    if sensorValue > threshold:
        led.on()  # Encender el LED si el suelo está seco
    else:
        led.off()  # Apagar el LED si el suelo está húmedo

    time.sleep(1)  # Esperar 1 segundo entre lecturas
```

## EXPLICACIÓN DEL CÓDIGO
Lectura del sensor(En este caso al no encontrarse disponible en la biblioteca de **Wokwi** el sensor resisitivo de humeddad YL-69 HL-69 o FC-28 se simula el comportamiento de los mismos con un potenciómetro, el cual se ajusta manualmente para los valores de humedad, debido a que el mismo permite cambiar la resistencia simulando de manera similar el trabajo que realiza el sensor de humedad resistivo)

- ### Potenciómetro

El ``` analogRead(sensorPin) ``` Lee el valor del potenciómetro, que simula el sensor de humedad. El valor varía de 0 a 4095 en el ESP32.
- ### Monitor serial

``` Serial.println(sensorValue)``` Imprime el valor en el serial "Serial Monitor" para que se vean los cambios en tiempo real

- ### Control del LED

El LED se enciende si el valor del sensor es mayo que el umbral(en este caso 2000), lo que significa que el suelo está "seco".
Si el valor del sensor es menor que el umbral,  el LED se apaga, lo que indica que el suelo está "húmedo".





