#include <VirtualWire.h>// INCLUYO LIBRERIA A UTILIZAR EN EL PROGRAMA

void setup()
{  // INICIALIZO LA CONFIGURACION SERIA A 9600 BAUDIOS
    Serial.begin(9600);    
    // ENVIO MENSAJE POR MONITOR SERIE
    Serial.println("Emisor RF");
    Serial.println("INGRESE 1 PARA ENVIAR EL NUMERO DE GRUPO");
    Serial.println("INGRESE 0 PARA ENVIAR NOMBRE DE LA MATERIA");
    // Se inicializa el RF
    vw_set_ptt_inverted(true);
    vw_set_tx_pin(12); //Pin 2 como salida para el RF 
    vw_setup(2000); // velocidad: Bits per segundo
}
 // VARIABLE QUE ALMACENA EL CARACTER ENVIADO
  char dato[1];
void loop()
{
       Serial.println("INGRESE CARACTER");
       dato[0]=Serial.read();// VALOR INICIAL
     while (!Serial.available() > 0);// validacion de que ingreso un caracter
       vw_send((uint8_t*)dato,sizeof(dato));// CONFIGURO PARA ENVIAR DATO DEL CARACTER ALMACENADO EN LA VARIABLE CHAR dato
       vw_wait_tx();     //ESPERO LA TRANSMISION    
     // ENVIO MENSAJE POR EL MONITOR SERIE
     if ( dato[0]=='1')
     {
    Serial.println("Emisor Enviando 1");
      vw_send((uint8_t*)dato,sizeof(dato));// CONFIGURO PARA ENVIAR
     vw_wait_tx();    // ESPERA PARA ENVIAR
    
     }
     else if ( dato[0]=='0')
      {    // ENVIO MENSAJE POR EL MONITOR SERIE     
    Serial.println("Emisor Enviando 0");
      vw_send((uint8_t*)dato,sizeof(dato));// CONFIGURO PARA ENVIAR
     vw_wait_tx();    // ESPERA PARA ENVIAR
  
      }
      else 
      {
        Serial.println(" CARACTER INCORRECTO");
      }
   
    // ENVIO MENSAJE POR EL MONITOR SERIE     
    delay(500);// DELAY DE 1 SEGUNDO 
}
