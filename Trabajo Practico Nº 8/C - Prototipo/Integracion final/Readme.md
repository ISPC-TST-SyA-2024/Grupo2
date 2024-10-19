# Informe: Sistema de Riego Inteligente

## Introducción
El presente documento describe la implementación del sistema de riego inteligente utilizando un microcontrolador ESP32,propuesto en el trabajo practico numero 8 de la materia **Sensores y Actuadores** de la **Tecnicatura en telecomunicaciones** del **Instituto Superior Politécnico de Córdoba**

## Componentes Utilizados

- **Microcontrolador**: ESP32
- **Sensores**:
  - Sensor de humedad del suelo resistivo YL-69 (Sector 1)
  - Sensor de humedad del suelo capacitivo V1.2 (Sector 2)
  - Sensor de lluvia resistivo YL-83 (digital)
  - Sensor de distancia HC-SR04
- **Actuadores**:
  - Relé para la bomba de riego (Sector 1 y 2)
  - Relé para la electroválvula
- **Pantalla**: LCD I2C 20x4

## Definición de Pines
```cpp
#define PIN_SENSOR_HUMEDAD_YL69 34       // Pin para el sensor de humedad del suelo resistivo YL-69 (Sector 1)
#define PIN_SENSOR_HUMEDAD_CAPACITIVO 35 // Pin para el sensor de humedad del suelo capacitivo V1.2 (Sector 2)
#define PIN_SENSOR_LLUVIA 32             // Pin para el sensor de lluvia resistivo YL-83 (digital)
#define PIN_RELE_RIEGO_SECTOR1 14        // Pin para el relé de la bomba de riego para el sector 1
#define PIN_RELE_RIEGO_SECTOR2 26        // Pin para el relé de la bomba de riego para el sector 2
#define PIN_RELE_ELECTROVALVULA 27       // Pin para activar el relé de la electroválvula
#define TRIG_PIN 5                       // Pin TRIG del sensor HC-SR04
#define ECHO_PIN 18                      // Pin ECHO del sensor HC-SR04
```
## Lógica de Funcionamiento

## Orden Lógico de Actuación

1. **Lectura de Sensores**: Se leen los valores de humedad de los suelos y el sensor de lluvia, así como la distancia del tanque de agua.
2. **Detección de Lluvia**: Si se detecta lluvia, se apagan todos los sistemas de riego.
3. **Control del Nivel del Tanque**: Si el nivel del tanque es bajo, se activa la electroválvula para llenar el tanque. Si el tanque está lleno, se apaga la electroválvula.
4. **Control de Riego**:
    - Se verifica la humedad del suelo en ambos sectores.
    - Si la humedad del suelo está por debajo de un umbral (por ejemplo, 15%), se activa el riego correspondiente.
    - Se mantiene el riego si la humedad se encuentra por debajo de otro umbral (por ejemplo, 70%).
    - Si la humedad del suelo supera el límite, se apaga el riego.

## Configuración Inicial

En la función `setup()`, se configuran los pines como entradas o salidas y se inicializa la pantalla LCD:

```cpp
void setup() {
  // Configuración de pines de entrada y salida
  pinMode(PIN_SENSOR_HUMEDAD_YL69, INPUT);           // Sensor de humedad del suelo YL-69
  pinMode(PIN_SENSOR_HUMEDAD_CAPACITIVO, INPUT);     // Sensor de humedad capacitivo V1.2
  pinMode(PIN_SENSOR_LLUVIA, INPUT);                 // Sensor de lluvia (digital)
  pinMode(PIN_RELE_RIEGO_SECTOR1, OUTPUT);           // Relé para el riego sector 1
  pinMode(PIN_RELE_RIEGO_SECTOR2, OUTPUT);           // Relé para el riego sector 2
  pinMode(PIN_RELE_ELECTROVALVULA, OUTPUT);          // Relé para la electroválvula
  pinMode(TRIG_PIN, OUTPUT);                         // Pin TRIG del sensor de distancia
  pinMode(ECHO_PIN, INPUT);                          // Pin ECHO del sensor de distancia
  
  // Inicialización de la pantalla LCD
  lcd.init();
  lcd.backlight();                                   // Encender la luz de fondo de la pantalla
  lcd.setCursor(0, 0);                               // Colocar el cursor en la posición inicial
  lcd.print("Riego Smart");                          // Mostrar un mensaje inicial
  delay(2000);                                       // Esperar 2 segundos antes de continuar
}
``` 
## Medición de Nivel de Tanque

La función `medirDistancia()` utiliza el sensor HC-SR04 para calcular la distancia desde la superficie del agua hasta el sensor, lo que se usa para determinar el nivel del tanque.


```cpp
long medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);       // Asegurarse de que TRIG esté en LOW
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);      // Enviar un pulso TRIG
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracion = pulseIn(ECHO_PIN, HIGH);  // Medir la duración del pulso ECHO
  
  // Calcular la distancia en cm (basada en la velocidad del sonido)
  long distancia = duracion * 0.034 / 2;
  
  return distancia;
}

```

En el programa se calcula un tanque de 1000 litros, lo que corresponde a un objeto de 141 cm de alto. Se definió que la distancia mínima donde estará ubicado el sensor será de 20 cm desde el nivel máximo de agua en el tanque. Esto se refleja en las siguientes constantes:

```cpp
const int ALTURA_TANQUE_MIN = 20;        // Altura mínima del tanque (sensor a máximo nivel de agua)
const int ALTURA_TANQUE_MAX = 141;       // Altura máxima del tanque (tanque vacío)
```

## Control del Riego

En la función `loop()`, se leen los valores de los sensores y se controla el riego basado en condiciones como la lluvia y el nivel del tanque:

```cpp
void loop() {
  // Leer valores de los sensores
  int humedad_suelo_YL69_raw = analogRead(PIN_SENSOR_HUMEDAD_YL69);          // Leer sensor YL-69 (Sector 1)
  int humedad_suelo_capacitivo_raw = analogRead(PIN_SENSOR_HUMEDAD_CAPACITIVO); // Leer sensor capacitivo (Sector 2)
  bool llueve = digitalRead(PIN_SENSOR_LLUVIA) == LOW;                       // Leer sensor de lluvia (LOW indica lluvia)
  long distancia = medirDistancia();                                         // Medir la distancia del tanque

  // Calcular el nivel del tanque en porcentaje
  int nivel_tanque_pct = map(distancia, ALTURA_TANQUE_MAX, ALTURA_TANQUE_MIN, 0, 100);
  
  // Convertir valores de humedad a porcentaje
  int humedad_suelo_sector1_pct = map(humedad_suelo_YL69_raw, 0, 4095, 0, 100);  // Sector 1 (YL-69)
  int humedad_suelo_sector2_pct = map(humedad_suelo_capacitivo_raw, 0, 4095, 0, 100);  // Sector 2 (Capacitivo)

  // Comprobar si está lloviendo
  if (llueve) {
    mostrarEstado("Lluvia detectada", "Riego OFF", "", "");
    // Desactivar riego
  } 
  else if (nivel_tanque_pct <= 20) {
    mostrarEstado("Tanque bajo:", String(nivel_tanque_pct) + "%", "Electrov activada", "");
    // Activar electroválvula
  } 
  else if (nivel_tanque_pct >= 90) {
    // Apagar electroválvula
  } 
  else {
    // Mostrar estado de humedad del suelo y controlar riego
  }
}

```

## Visualización

El estado del sistema se muestra en la pantalla LCD en múltiples líneas, incluyendo la humedad de los sectores, el nivel del tanque y el estado del riego:

```cpp
void mostrarEstado(String linea1, String linea2, String linea3, String linea4) {
  lcd.clear();                       // Limpiar la pantalla
  lcd.setCursor(0, 0);               // Colocar el cursor en la primera línea
  lcd.print(linea1);                 // Mostrar la primera línea
  lcd.setCursor(0, 1);               // Colocar el cursor en la segunda línea
  lcd.print(linea2);                 // Mostrar la segunda línea
  lcd.setCursor(0, 2);               // Colocar el cursor en la tercera línea
  lcd.print(linea3);                 // Mostrar la tercera línea
  lcd.setCursor(0, 3);               // Colocar el cursor en la cuarta línea
  lcd.print(linea4);                 // Mostrar la cuarta línea
}

```
