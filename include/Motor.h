#ifndef MOTOR
#define MOTOR

#include<Arduino.h>
class Motor
{
private:
    int IN1 = 0;  
    int IN2 = 0; 
    String topic;  
    int channel = 0; 
    const int freq = 450; 
    const int resolution = 8;

public:
    Motor(int, int, String);
    void setup();
    void move_cw(float); 
    void move_ccw(float);    
    String get_topic();
};

Motor::Motor(int IN1, int IN2, String topic)
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

String Motor::get_topic(){
    return this->topic; 
};

#endif