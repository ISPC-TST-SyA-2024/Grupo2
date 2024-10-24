![image](https://github.com/user-attachments/assets/89e84d76-4a2f-4848-96d8-e6211ea4b608)**Archivos que constituyen lo resuelto para la consigna nº1  
![Uploading image.png…]()






TX código arduino TX :
  ```cpp  
 #include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX en pin 10, TX en pin 11

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Transmisor listo");
  delay(2000);  // Esperar 2 segundos antes de enviar el primer mensaje
}


void loop() {
  String mensaje = "Hola desde el Transmisor (TX)";
  mySerial.println(mensaje);
  Serial.println("Transmisor envía: " + mensaje);

  delay(1000);

  if (mySerial.available()) {
    String respuesta = mySerial.readStringUntil('\n');
    Serial.println("Transmisor recibió respuesta: " + respuesta);
  }

  delay(2000);
} 
  ```

RX código arduino RX  
 ```cpp  
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX en pin 10, TX en pin 11

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Receptor listo");
}

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX en pin 10, TX en pin 11

void setup() {
 Serial.begin(9600);
 mySerial.begin(9600);
 Serial.println("Receptor listo");
}

if (mySerial.available()) {
    // Leer el mensaje del transmisor
    String mensajeRecibido = mySerial.readStringUntil('\n');
    Serial.println("Receptor recibió: " + mensajeRecibido);

    // Responder al transmisor
    String respuesta = "Mensaje recibido por RX";
    mySerial.println(respuesta);
    Serial.println("Receptor envía: " + respuesta);
  } else {
    Serial.println("Esperando mensaje...");  // Imprimir si no hay datos disponibles
  }

  delay(500); // Pequeña espera para evitar sobrecargar el loop
}
  ```

