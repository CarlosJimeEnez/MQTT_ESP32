#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <functions.h>

#define LED_BUILTIN 1
#define LED 18 
bool led_status = false;


WiFiClient espClient; 
PubSubClient client(espClient); 

//-------- Wifi variables ------ //
// const char *ssid = "RS_NETWORK_1_2.4G"; 
// const char *password = "rsautomation2017"; 
//const char *ssid = "BUAP_Estudiantes"; 
//const char *password = "f85ac21de4"; 
const char *ssid = "MEGACABLE-979F"; 
const char *password = "8eAYgaeY"; 

// ------------------- mqtt Broker: 
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/mot1";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

void interrupt(){
  digitalWrite(LED, HIGH); 
}

/**********************************   SETUP  ************************************/
void setup() {
 Serial.begin(115200);

 /* ----------------------- CONEXION WIFI ----------------------- */
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 
 // --------------------- connecting to a mqtt broker ------------------ */
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

  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(23), interrupt, RISING); 
  // -------------------- publish and subscribe
  client.publish(topic, "Holas desde la ESP");
  client.subscribe(topic);
}

void loop() {
    client.loop();
}
