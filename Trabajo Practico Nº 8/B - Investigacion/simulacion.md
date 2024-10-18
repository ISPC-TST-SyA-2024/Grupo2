https://wokwi.com/projects/new/esp32

link correspondiente a la tarea 1, realizada en la plataforma de wokwi.

código utiulizado para la simulación
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
