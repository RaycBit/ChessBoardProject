/*
* Name(s): Raymundo Carrasco, Ayana Smith
* Date: April 26, 2017
* Filename:interactive_chessboard_r.c_a.s_a.r.ino 
* Description: The following program codes for the shift registers, hall effect sensors, 
* and for the neopixels, it reads the hall effect sensor then sends the data
* via the shift register to the microcontroller. If its the sensor is reading 0,
* then there is a magnet close to the sensor which lights up the neopixel. 
*
* 
* Notes: some notes for the reader about this project 
* 
 */


#include <Adafruit_NeoPixel.h> //Neopixel library added/ included

int shift_load = 5; //Sets microcontroller pin 6 as shift_load
int clk = 10; //Sets microcontroller pin 7 as clock pin
int Qh = 9; //Sets microcontroller pin 8 as Qh pin
int delayval = 30; //Sets delay value to 30 milliseconds

#define NUMPIXELS      64 // The quantity of neopixels that are on the chessboard (constant value)
#define PIN            6 // The pin that the neopixels are attached to on the microcontroller (constant value)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

boolean sensorValue [64];   //Sets an array of 64
boolean data;   //Stores data on boolean datatype

void setup() {
  pinMode(shift_load, OUTPUT);  //Sets shift_load as OUTPUT
  pinMode(clk, OUTPUT);   //Sets clock pin as OUTPUT 
  pinMode(Qh, INPUT);   //Sets Qh pin as INPUT
  
  digitalWrite(shift_load, HIGH);   //Sets shift_Load to a known or starting value 
  
  Serial.begin(9600); //Initiates serial monitor 
  pixels.begin(); // This initializes the NeoPixel library.

  
}

void loop() {
  shift_act();  // calls function to load sensor data
  
  for (int x=0; x < 64; x++) {
    digitalWrite(clk, LOW);   //Activates
    digitalWrite(clk, HIGH);  //Clock
    digitalWrite(clk, LOW); //Pin

    sensorValue[x] = digitalRead(Qh);  // Stores sensor value to the array
    
    Serial.print("value["); Serial.print(x+1); Serial.print("]: "); 
    Serial.println(sensorValue[x]);
    delay(5);  //sets delay
  
  if(sensorValue[x] == 0){
    pixels.setPixelColor(x, pixels.Color(0,150,0)); // bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    } 
   else{
    pixels.setPixelColor(x, pixels.Color(153, 255, 255)); // Sky Blue color 
   
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
   }
  
  }
}

void shift_act() {
  digitalWrite(shift_load, LOW);    //Loads sensor data
  delay(5); // delay time (in milliseconds)
  digitalWrite(shift_load, HIGH);   //To the shift register
  
}

