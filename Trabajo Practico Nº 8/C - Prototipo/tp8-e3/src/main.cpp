#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configurar la pantalla I2C (dirección 0x27 y tamaño de 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin del slider (A0 en ESP32)
const int pinSlider = 34; // Pin ADC0 en ESP32

void setup() {
  // Iniciar la comunicación serial
  Serial.begin(115200);

  // Iniciar la pantalla LCD
  lcd.init();
  lcd.backlight();

  // Mensaje de bienvenida en LCD
  lcd.setCursor(0, 0);
  lcd.print("Lluvia Nivel:");
}

void loop() {
  // Leer el valor del slider (0 a 4095 en ESP32)
  int valorSensor = analogRead(pinSlider);
  
  // Convertir el valor a un rango de 0 a 100
  int nivelLluvia = map(valorSensor, 0, 4095, 0, 100);

  // Mostrar el valor en el monitor serial
  Serial.print("Nivel de lluvia: ");
  Serial.println(nivelLluvia);

  // Mostrar el nivel de lluvia en la pantalla LCD
  lcd.setCursor(0, 1); // Segunda fila
  lcd.print("                "); // Limpiar la línea
  lcd.setCursor(0, 1); // Segunda fila
  lcd.print(nivelLluvia);
  lcd.print("%");

  // Esperar 500ms antes de la siguiente lectura
  delay(500);
}
