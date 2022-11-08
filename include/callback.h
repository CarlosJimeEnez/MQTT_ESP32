#ifndef Callback_function
#define Callback_function
#include <Arduino.h>
#include <Motor.h>

Motor mot1(12, 13, "esp32/mot1"); 
Motor mot2(4, 5, "esp32/mot2"); 
Motor motores[2] = {mot1, mot2}; 
int motor_setpoints[3] = {0,0,0}; 

/* ------------- Funcion de llegada de los valores -------------------------- */
void callback(char *topic, byte *payload, unsigned int length){
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
    Serial.println((char) payload[i]);
    }

    // ------- Conversion de char a int  --------- //
    String topic_string = topic;
    String concatenacion = ""; 
    String auxiliar = "0"; 
    for (size_t i = 0; i < length; i++)
    {
        auxiliar = String((char) payload[i]); 
        concatenacion = concatenacion + auxiliar; 
    }
    int payload_int = concatenacion.toInt(); 
    
    // -------- MATCH TOPICS ------ // 
    for (size_t i = 0; i < 2; i++)
    {
        if (topic_string == motores[i].get_topic())
        {
            motor_setpoints[i] = payload_int; 
            Serial.println("Topic MATCH: " + motores[i].get_topic() + " " + String(motor_setpoints[i])); 
        }
    }

    // ---------- BEGIN -------- //
    if(topic_string == "Begin"){
        Serial.println("BEGIN"); 
    }
    
    Serial.println(payload_int);
    Serial.println("-----------------------");
}


#endif