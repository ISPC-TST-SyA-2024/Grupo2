#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SOIL_SENSOR_PIN 34  // Pin para el sensor de humedad del suelo
#define RAIN_SENSOR_PIN 32  // Pin para el sensor de lluvia (digital)
#define RELAY_PIN 14        // Pin para activar la bomba de riego
#define TANK_LEVEL_PIN 33   // Pin para el sensor de nivel del tanque (entrada analógica)

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C para la pantalla LCD

bool releActivo = false; // Estado inicial del relé

void setup() {
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(TANK_LEVEL_PIN, INPUT);

  lcd.init();   // Inicializar la pantalla LCD
  lcd.backlight(); // Encender luz de fondo
  lcd.setCursor(0, 0);
  lcd.print("Riego Inteligente");
  delay(2000);
}

void loop() {
  int humedad_suelo_raw = analogRead(SOIL_SENSOR_PIN);
  bool llueve = digitalRead(RAIN_SENSOR_PIN) == LOW; // Si está en LOW, está lloviendo
  int nivel_tanque_raw = analogRead(TANK_LEVEL_PIN);
  
  // Convertir valores a porcentaje
  int humedad_suelo_pct = map(humedad_suelo_raw, 0, 4095, 0, 100);
  int nivel_tanque_pct = map(nivel_tanque_raw, 0, 4095, 0, 100);

  // Mostrar datos en la pantalla LCD
  lcd.clear();
  
  // 1. ¿Llueve?
  if (llueve) {
    lcd.setCursor(0, 0);
    lcd.print("Lluvia detectada");
    lcd.setCursor(0, 1);
    lcd.print("Riego desactivado");
    digitalWrite(RELAY_PIN, LOW);  // Apagar bomba
    releActivo = false;            // Actualizar estado del relé
  } 
  else {
    // No llueve, ahora revisar tanque
    if (nivel_tanque_pct <= 20) {
      lcd.setCursor(0, 0);
      lcd.print("Tanque bajo: ");
      lcd.print(nivel_tanque_pct);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Riego desactivado");
      digitalWrite(RELAY_PIN, LOW);  // Apagar bomba
      releActivo = false;            // Actualizar estado del relé
    } 
    else {
      // El tanque tiene suficiente agua
      lcd.setCursor(0, 0);
      lcd.print("Humedad: ");
      lcd.print(humedad_suelo_pct);
      lcd.print("%");

      // Revisar la humedad del suelo
      if (humedad_suelo_pct <= 15) {
        lcd.setCursor(0, 1);
        lcd.print("Riego activado");
        digitalWrite(RELAY_PIN, HIGH);  // Activar bomba
        releActivo = true;              // Actualizar estado del relé
      } 
      else if (releActivo && humedad_suelo_pct <= 70) {
        lcd.setCursor(0, 1);
        lcd.print("Riego activado");
        digitalWrite(RELAY_PIN, HIGH);  // Mantener bomba activada
      } 
      else {
        lcd.setCursor(0, 1);
        lcd.print("Riego desactivado");
        digitalWrite(RELAY_PIN, LOW);   // Apagar bomba
        releActivo = false;             // Actualizar estado del relé
      }
    }
  }

  delay(2000);  // Esperar 2 segundos antes de actualizar
}
