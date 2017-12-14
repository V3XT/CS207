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

#define SAMPLERATE 8000

const int waveQuality = 256;  //The maximum height of a generated wave
const int pot1pin = A0;   //Input pin of the first potentiometer
const int pot2pin = A1;   //Input pin of the second potentiometer
const int bothWaves = 8; //Input for the toggle to control second potentiometer
int pot1 = 0;   //Stores the measurement of the first potentiometer
int pot2 = 0;   //Stores the measurement of the second potentiometer

//record an initial time
  long sampleStop = micros();
  char waveOne = 0, waveTwo = 0;
void setup() {
  //Initialize pins for the DAC
  DDRD = B11111111;
  pinMode(bothWaves,INPUT);

}

void loop() {

  while(1){
  
  if(digitalRead(bothWaves)){
    
     waveOne += 128/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,40,3150)));
     waveTwo += 128/(SAMPLERATE/(map(analogRead(pot2pin),0,1023,40,3150)));
     waveOne = waveOne % 128;
     waveTwo = waveTwo % 128;

     PORTD = waveOne + waveTwo;
  }
  else {
    waveOne += 256/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,40,3150)));
    
    PORTD = waveOne;
  }

  //wait for the right amount of time for 8000Hz
    sampleStop += 125;
    while(micros() < sampleStop){}
  }
}



