#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Smart-Grow"
  https://create.arduino.cc/cloud/things/bfb272c6-0605-40a3-b6de-abebe909afa5 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  String plantName;
  float moisture;
  CloudLight light;
  bool lowWater;
  bool pump;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <stdio.h>


int Moisturepin= A1;
int Pumppin = 2;
float value1 = 0;
int LEDs =0;
int greenLED = 0;
int redLED = 1;
int floatswitch = 3;
int switchstate = 0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  pinMode(Pumppin, OUTPUT);
  pinMode(Moisturepin,INPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(floatswitch, INPUT_PULLUP);
  digitalWrite(Pumppin,HIGH);
  digitalWrite(greenLED,HIGH);
  digitalWrite(redLED,LOW);
  delay(500);
  //plantName = "Welcome to Smart-Grow. Please Type one of the following options, or type nothing for the default settings: \n For Basil, type 'Basil' \n For Tomatoes, type 'Tomato' \n For Succulents, type 'Succulent'";
  //Serial.println(plantName);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
}

void loop() {
  ArduinoCloud.update();
  Serial.print("Moisture Level:");
  value1 = analogRead(Moisturepin);
  switchstate = digitalRead(floatswitch);
  moisture = analogRead(Moisturepin);
  Serial.println(value1);
  digitalWrite(greenLED, HIGH);
  
  if (switchstate == 1) {
  digitalWrite(redLED,LOW);
  lowWater = 0;
  if(LEDs == 1){
    digitalWrite(Pumppin, LOW);
    pump = 1;
  }
  else{
    pump = 0;
    if(plantName == "Basil"){
      if(value1>665.6)
      {
        digitalWrite(Pumppin,HIGH);
        pump = 0;
      }
      else
      {
        digitalWrite(Pumppin,LOW);
        pump = 1;
      }
    } else if  (plantName == "Tomato"){
    
      if(value1>819.2)
      {
        digitalWrite(Pumppin,HIGH);
        pump = 0;
      }
      else
      {
        digitalWrite(Pumppin,LOW);
        pump = 1;
      }
    } else if (plantName == "Succulent"){
    
      if(value1>204.8)
      {
        digitalWrite(Pumppin,HIGH);
        pump = 0;
      }
      else
      {
        digitalWrite(Pumppin,LOW);
        pump = 1;
      }
    } else {
      if(value1>700){
        digitalWrite(Pumppin,HIGH);
      }else{
        digitalWrite(Pumppin,LOW);
      }
    }
  }
  } else {
    digitalWrite(redLED,HIGH);
    lowWater = 1;
    digitalWrite(Pumppin,HIGH);
    pump = 0;
  }
}



/*
  Since Light is READ_WRITE variable, onLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightChange()  {
  LEDs = light;
  
}


/*
  Since PlantName is READ_WRITE variable, onPlantNameChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPlantNameChange()  {

}




