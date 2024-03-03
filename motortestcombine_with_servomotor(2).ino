
#include <Servo.h>
Servo myservo;

int humidity_input = A0 ; //anolog input for humidity
int humidity_val; //accept the value from detector

int servo_pin = 9;

int current_degree = 0;//current angle of servo motor
int threshold_for_rotation = 100;//will be changed later

#define ESC_PIN 2
Servo esc;
double Serial_value = 0.0;
double Speed;

unsigned long previousMillisServo = 0;
const long intervalServo = 15; // Execute every 15 milliseconds

unsigned long previousMillisESC = 0;
const long intervalESC = 1000; // Execute every 1000 milliseconds


void setup() {
  //setup for servo
  myservo.attach(9);
  myservo.write(current_degree);
  
  // Setup for brushless motor
  esc.attach(ESC_PIN, 1000, 2000);
  esc.write(0);
  

}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisServo >= intervalServo) 
  {
    previousMillisServo = currentMillis;
    humidity_val = analogRead(humidity_input);
    if (myservo.read() > 170 && humidity_val < threshold_for_rotation )
    {
      current_degree = 0;
      myservo.write(current_degree);
      while(true)
      {
        //do nothing to stop the programm
      }
    }
    else 
    {
      if (humidity_val < threshold_for_rotation)
      {
        current_degree += 20;
        if (current_degree >= 170) current_degree = 170;
        myservo.write(current_degree);
      }
    }
  }
  if(currentMillis - previousMillisESC >= intervalESC)
  {
    previousMillisESC = currentMillis;
    while(Serial.available()) {
      double tmp=Serial.parseFloat();
      
      if (tmp!=0.0){
        Serial_value=tmp; 
      } 
      if (tmp==1.0){
        Serial_value=0.0;
      }
      Serial.println(Serial_value);
      Speed=(Serial_value/(2450*5))*180;
      Serial.println(Speed);
      esc.write(Speed);
    }
  }
  
}
