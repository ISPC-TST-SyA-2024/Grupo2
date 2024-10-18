https://wokwi.com/projects/new/esp32

Link correspondiente a la tarea 1, realizada en la plataforma de wokwi.

Código utilizado para la simulación
```cpp
int sensorPin = 34;  // Pin del sensor (potenciómetro) en el ESP32
int sensorValue = 0; // Variable para almacenar el valor leído
int ledPin = 13;     // Pin del LED
int threshold = 2000;  // Umbral de humedad

void setup() {
  pinMode(ledPin, OUTPUT);  // Configurar el LED como salida
  Serial.begin(115200);     // Iniciar la comunicación serial
}

void loop() {
  sensorValue = analogRead(sensorPin);  // Leer el valor analógico del sensor
  Serial.print("Humedad del suelo (simulada): ");
  Serial.println(sensorValue);  // Mostrar el valor en el monitor serial
  
  // Control del LED según el valor del sensor
  if (sensorValue > threshold) {
    digitalWrite(ledPin, HIGH);  // Encender el LED si el suelo está seco
  } else {
    digitalWrite(ledPin, LOW);   // Apagar el LED si el suelo está húmedo
  }

  delay(1000);  // Esperar 1 segundo entre lecturas
}
```

## EXPLICACIÓN DEL CÓDIGO
Lectura del sensor(En este caso al no encontrarse disponible en la biblioteca de Wokwi el sensor resisitivo de humeddad YL-69 HL-69 o FC-28 se simula el comportamiento de los mismos con un potenciómetro, el cual se ajusta manualmente para los valores de humedad, debido a que el mismo permite cambiar la resistencia simulando de manera similar el trabajo que realiza el sensor de humedad resistivo)

### Potenciómetro

El ``` analogRead(sensorPin) ``` Lee el valor del potenciómetro, que simula el sensor de humedad. El valor varía de 0 a 4095 en el ESP32.
### Monitor serial

``` Serial.println(sensorValue)``` Imprime el valor en el serial "Serial Monitor" para que se vean los cambios en tiempo real

### Control del LED

El LED se enciende si el valor del sensor es mayo que el umbral(en este caso 2000), lo que significa que el suelo está "seco".
Si el valor del sensor es menor que el umbral,  el LED se apaga, lo que indica que el suelo está "húmedo".





