#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Setup_functions.h>
#include <vector>
#include <callback.h>


#define LED_BUILTIN 1
#define LED 18 

WiFiClient espClient; 
PubSubClient client(espClient);
Motor mot1(12, 13, "esp32/mot1"); 
Motor mot2(4, 5, "esp32/mot2"); 


//-------- Wifi variables ------ //
// const char *ssid = "RS_NETWORK_1_2.4G"; 
// const char *password = "rsautomation2017"; 
//const char *ssid = "BUAP_Estudiantes"; 
//const char *password = "f85ac21de4"; 
const char *ssid = "MEGACABLE-979F"; 
const char *password = "8eAYgaeY"; 

// ------------------- mqtt Broker: 
const char *mqtt_broker = "broker.emqx.io";
// TOPICS: 
std::vector<const char *> topics = {"esp32/mot1", "esp32/mot2", "esp32/mot3", "esp32/Begin"}; 
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

/**********************************   SETUP  ************************************/

void setup() {
    Serial.begin(115200);
//// --------------- CONEXIONES RED ------------  ////
    conexion_wifi(ssid, password);

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

// -------------------- publish and subscribe --- //
    client.publish(topics[0], "Holas desde la ESP");
    for(auto topic: topics){
        Serial.println(topic); 
        client.subscribe(topic);
    }
    client.subscribe("Begin");
}

void loop() {
    client.loop();
}
