#ifndef MOTOR
#define MOTOR

#include<Arduino.h>
class Motor
{
private:
    int IN1 = 0;  
    int IN2 = 0; 
    char *topic; 
    int channel = 0; 
    const int freq = 450; 
    const int resolution = 8;

public:
    Motor(int, int, char*);
    void setup();
    void get_topic();
    void move_cw(float); 
    void move_ccw(float);    
};

Motor::Motor(int IN1, int IN2, char* topic)
{
    this->IN1 = IN1; 
    this->IN2 = IN2;  
    this->topic = topic; 
}

void Motor::setup(){
    pinMode(this->IN2, OUTPUT); 
    ledcSetup(this->channel, this->freq, this->resolution); 
    ledcAttachPin(this->IN1, this->channel); 
}

void Motor::move_cw(float freq){
    digitalWrite(this->IN2, HIGH); 
    ledcWriteTone(this->channel, freq); 
}

void Motor::move_ccw(float freq){
    digitalWrite(this->IN2, LOW); 
    ledcWriteTone(this->channel, freq); 
}

void Motor::get_topic(){
    Serial.println(this->topic); 
};

#endif