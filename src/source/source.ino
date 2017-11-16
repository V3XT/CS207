/* Author: Viktor Fries
 * Date: Nov 16, 2017
 * 
 * This is the main source file for the code run by the arduino.
 * It contains the formulas that allow it to produce waves
 * and control a speaker in a ruben's tube.
 * 
 * Pins 0-7 will be used to control a Digital to Analog converter
 * which will allow for the creation of 8 bit audio
 * 
 */

const int waveQuality = 256;  //The maximum height of a generated wave
const int pot1pin = A0;   //Input pin of the first potentiometer
const int pot2pin = A1;   //Input pin of the second potentiometer
const int pot2pinBool = A2; //Input for the toggle to control second potentiometer
int pot1 = 0;   //Stores the measurement of the first potentiometer
int pot2 = 0;   //Stores the measurement of the second potentiometer


void setup() {
  //Initialize pins for the DAC
  for (int i = 0; i < 8; i++){
    pinMode(i, OUTPUT);
  }

}

void loop() {
  //Read the current values of the poteniometers
  //This code will probably be refactored directly into
  //Other statements to increase proccessing speed
  pot1 = analogRead(pot1pin); 
  pot2 = analogRead(pot2pin);
  

}
