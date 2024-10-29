#include <VirtualWire.h>// INCLUYO LIBRERIA
// CONFIGURACION
void setup()
{
 
    // Se inicializa el RF
    vw_set_ptt_inverted(true); // 
    vw_set_rx_pin(12);  //Pin 2 como entrada del RF
    vw_setup(2000);  // velocidad: Bits per segundo
    Serial.begin(9600);  // CONFIGURO EL MONITOR SERIE
    Serial.println("RECEPTOR");// ENVIO MENSAJE
    vw_rx_start();       // Se inicia como receptor
    
    //pinMode(13, OUTPUT);    //Configuramos el pin del Led como SALIDA, LED INTEGRADO QUE SE ENCIENDE Y SE APAGA SEGUN EL CARACTER RECIBIDO
    
    //digitalWrite(13, false);// ESTA APAGADO AL INICIAR LA PROGRAMACION
}
// VARIABLE QUE ALMACENA EL CARACTER RECIBIDO
char dato [1];
void loop()
{  // CONFIGURO EL DATO A RECIBIR
    uint8_t dato [VW_MAX_MESSAGE_LEN];// CONFIGURO EL DATO QUE SE RECIBE PARA SU INTERPRETACION
    uint8_t datoleng=VW_MAX_MESSAGE_LEN;
 
    //verificamos si hay un dato valido en el RF
    if (vw_get_message(dato,&datoleng))
    {  
        if( dato[0]=='1') // SI DATO ES DE VALOR 1
        {
            Serial.println("GRUPO 3");// ENVIO MENSAJE POR MONITOR SERIE
           // digitalWrite(13, HIGH); //Encendemos el Led DEL PIN 13
            delay(500); // SE ENCIENDE POR DOS SEGUNDOS
        }
        if( dato[0]=='0') 
        {    Serial.println(" SENSORES Y ACTUADORES");//  SE ENVIA LA PALABRA SENSORES Y ACTUADORES SI EL CARACTER ES OTRO VALOR
             delay(500);// DELAY DE DOS SEGUNDOS
            //digitalWrite(13, LOW); //Apagamos el Led
        }            
    }
}
