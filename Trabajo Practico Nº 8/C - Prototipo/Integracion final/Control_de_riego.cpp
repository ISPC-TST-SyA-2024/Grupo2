#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_SENSOR_HUMEDAD_YL69 34       // Pin para el sensor de humedad del suelo YL-69 (Sector 1)
#define PIN_SENSOR_HUMEDAD_CAPACITIVO 35 // Pin para el sensor de humedad del suelo Capacitivo (Sector 2)
#define PIN_SENSOR_LLUVIA 32             // Pin para el sensor de lluvia (digital)
#define PIN_RELE_RIEGO_SECTOR1 14        // Pin para el relé de la bomba de riego para el sector 1
#define PIN_RELE_RIEGO_SECTOR2 26        // Pin para el relé de la bomba de riego para el sector 2
#define PIN_RELE_ELECTROVALVULA 27       // Pin para activar el relé de la electroválvula
#define TRIG_PIN 5                       // Pin TRIG del sensor HC-SR04 (sensor de distancia)
#define ECHO_PIN 18                      // Pin ECHO del sensor HC-SR04

LiquidCrystal_I2C lcd(0x27, 20, 4);      // Configuración de la pantalla LCD 20x4

const int ALTURA_TANQUE_MIN = 10;        // Altura mínima del tanque (sensor a máximo nivel de agua)
const int ALTURA_TANQUE_MAX = 141;       // Altura máxima del tanque (tanque vacío) basandome en el general de los tanques de 1000L tienen una altura de 141 cm por 100 cm de diametro

bool releRiegoSector1Activo = false;     // Estado del relé del riego para el sector 1
bool releRiegoSector2Activo = false;     // Estado del relé del riego para el sector 2
bool releElectrovalvulaActivo = false;   // Estado del relé de la electroválvula

void setup() {
  // Configuración de pines de entrada y salida
  pinMode(PIN_SENSOR_HUMEDAD_YL69, INPUT);           // Sensor de humedad del suelo YL-69
  pinMode(PIN_SENSOR_HUMEDAD_CAPACITIVO, INPUT);     // Sensor de humedad capacitivo
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

// Función para medir la distancia con el sensor HC-SR04
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

// Función para mostrar múltiples líneas en la pantalla LCD
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

// Función principal del programa
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

  // Variable para almacenar el estado de riego en la cuarta línea
  String estadoRiego = "";

  // Comprobar si está lloviendo
  if (llueve) {
    // Si está lloviendo, apagar el riego y mostrar estado
    mostrarEstado("Lluvia detectada", "Riego OFF", "", "");
    digitalWrite(PIN_RELE_RIEGO_SECTOR1, LOW);          // Apagar riego sector 1
    digitalWrite(PIN_RELE_RIEGO_SECTOR2, LOW);          // Apagar riego sector 2
    digitalWrite(PIN_RELE_ELECTROVALVULA, LOW);         // Apagar electroválvula
    releRiegoSector1Activo = false;
    releRiegoSector2Activo = false;
    releElectrovalvulaActivo = false;
  } 
  else if (nivel_tanque_pct <= 20) {  // Revisar si el tanque tiene agua baja
    // Si el nivel del tanque es bajo, activar la electroválvula
    mostrarEstado("Tanque bajo:", String(nivel_tanque_pct) + "%", "Electrov activada", "");
    digitalWrite(PIN_RELE_ELECTROVALVULA, HIGH);        // Activar electroválvula para llenar el tanque
    releElectrovalvulaActivo = true;
  } 
  else if (nivel_tanque_pct >= 90) {  // Si el tanque está lleno, apagar la electroválvula
    digitalWrite(PIN_RELE_ELECTROVALVULA, LOW);         // Apagar electroválvula
    releElectrovalvulaActivo = false;
  } 
  else {
    // Si no llueve y el tanque tiene suficiente agua, mostrar el estado de la humedad del suelo
    mostrarEstado("Hum. Sector 1: " + String(humedad_suelo_sector1_pct) + "%", 
                  "Hum. Sector 2: " + String(humedad_suelo_sector2_pct) + "%", 
                  "Nivel tanque: " + String(nivel_tanque_pct) + "%", estadoRiego);

    // Control de riego para el sector 1 (YL-69)
    if (humedad_suelo_sector1_pct <= 15) {
      digitalWrite(PIN_RELE_RIEGO_SECTOR1, HIGH);       // Activar riego en sector 1
      releRiegoSector1Activo = true;
    } 
    else if (releRiegoSector1Activo && humedad_suelo_sector1_pct <= 70) {
      digitalWrite(PIN_RELE_RIEGO_SECTOR1, HIGH);       // Mantener riego en sector 1
    } 
    else {
      digitalWrite(PIN_RELE_RIEGO_SECTOR1, LOW);        // Apagar riego en sector 1
      releRiegoSector1Activo = false;
    }

    // Control de riego para el sector 2 (Capacitivo)
    if (humedad_suelo_sector2_pct <= 15) {
      digitalWrite(PIN_RELE_RIEGO_SECTOR2, HIGH);       // Activar riego en sector 2
      releRiegoSector2Activo = true;
    } 
    else if (releRiegoSector2Activo && humedad_suelo_sector2_pct <= 70) {
      digitalWrite(PIN_RELE_RIEGO_SECTOR2, HIGH);       // Mantener riego en sector 2
    } 
    else {
      digitalWrite(PIN_RELE_RIEGO_SECTOR2, LOW);        // Apagar riego en sector 2
      releRiegoSector2Activo = false;
    }

    // Determinar el mensaje a mostrar en la cuarta línea
    if (releRiegoSector1Activo && releRiegoSector2Activo) {
      estadoRiego = "Regando sector 1 y 2";
    } 
    else if (releRiegoSector1Activo) {
      estadoRiego = "Regando sector 1";
    } 
    else if (releRiegoSector2Activo) {
      estadoRiego = "Regando sector 2";
    } 
    else {
      estadoRiego = "Riego OFF";
    }

    // Actualizar la cuarta línea con el estado del riego
    mostrarEstado("Hum. Sector 1: " + String(humedad_suelo_sector1_pct) + "%", 
                  "Hum. Sector 2: " + String(humedad_suelo_sector2_pct) + "%", 
                  "Nivel tanque: " + String(nivel_tanque_pct) + "%", estadoRiego);
  }

  delay(2000);  // Esperar 2 segundos antes de la siguiente actualización
}
