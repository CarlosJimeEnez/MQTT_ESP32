#ifndef MOTOR
#define MOTOR

#include<Arduino.h>
class Motor
{
private:
    int IN1 = 0;  
    int IN2 = 0; 
    String topic;  
    int channel1 = 0; 
    int channel2 = 0; 
    const int freq = 450; 
    const int resolution = 8;

public:
    Motor(int, int, int, int,String);
    void setup();
    void move_cw(float); 
    void move_ccw(float);
    void set_motor(int dir, int pmwVal);     
    String get_topic();
};

Motor::Motor(int IN1, int IN2, int channel1, int channel2, String topic)
{
    this->IN1 = IN1; 
    this->IN2 = IN2;  
    this->channel1 = channel1; 
    this->channel2 = channel2; 
    this->topic = topic; 
}

void Motor::setup(){
    ledcSetup(this->channel1, this->freq, this->resolution); 
    ledcSetup(this->channel2, this->freq, this->resolution); 

    ledcAttachPin(this->IN1, this->channel1); 
    ledcAttachPin(this->IN2, this->channel2); 
}

void Motor::move_cw(float pwmVal){
    ledcWrite(this->channel2, 0); 
    ledcWrite(this->channel1, pwmVal); 
}

void Motor::move_ccw(float pwmVal){
    ledcWrite(this->channel2, pwmVal); 
    ledcWrite(this->channel1, 0);  
}

void Motor::set_motor(int dir, int pwmVal){
    if (dir == 1)
    {
        move_cw(pwmVal);
        Serial.println("UP");
    }
    else{
        move_ccw(pwmVal); 
    }
}

String Motor::get_topic(){
    return this->topic; 
};

#endif