#ifndef Callback_function
#define Callback_function
#include <Arduino.h>
#include <Motor.h>

/* ------------- Funcion de llegada de los valores -------------------------- */
void callback(char *topic, byte *payload, unsigned int length){
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
    }

    String topic_string = topic;

    String concatenacion = ""; 
    String auxiliar = "0"; 
    for (size_t i = 0; i < length; i++)
    {
        auxiliar = String((char) payload[i]); 
        concatenacion = concatenacion + auxiliar; 
    }
    int payload_int = concatenacion.toInt(); 
    
    Serial.println(payload_int);
    Serial.println("-----------------------");
    
}


#endif