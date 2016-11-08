/*
 Using the SparkFun HX711 breakout board with a scale
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.

 Arduino pin 
 4 -> HX711 CLK
 5 -> DAT
 5V -> VCC
 GND -> GND
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h" 

#define calibration_factor 222 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  5
#define CLK  4

int inc = 0;
int incomingByte;

HX711 scale(DOUT, CLK);

void setup() {
  
  Serial.begin(115200);

  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();	//Assuming there is no weight on the scale at start up, reset the scale to 0
}

void loop() {
  
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    // if it's a capital R, reset the program
    if (incomingByte == 'R') {
      setup();
      Serial.println("# RESET ~");
    }
  }
  
  if(scale.get_units(10) > 10){
      Serial.print("#");
      Serial.print(scale.get_units(10), 1); //scale.get_units() returns a float
      Serial.print("~");
      Serial.println();
      inc = 0;
      delay(250);
  }
  else{
    if(inc == 0){
    Serial.println("# Waiting for reading from scale. ~");
    inc++;
    delay(250);
    }
  }
}
