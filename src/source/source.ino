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

#define SAMPLERATE 8000.0   //The number of audio samples per second
#define SAMPLELENGTH 125.0  //1 000 000 / SAMPLERATE
#define WAVEQUALITY 256     //The maximum height of a generated wave
#define HALFWAVEQUALITY 128 ///WAVEQUALITY / 2

#define pot1pin A0  //Input pin of the first potentiometer
#define pot2pin A1  //Input pin of the second potentiometer
#define bothWaves 8 //Input for the toggle to control second potentiometer

//record an initial time
  long sampleStop = micros();
  float waveOne = 0, waveTwo = 0;
  char waveOut = 0;
void setup() {
  //Initialize pins for the DAC
  DDRD = B11111111;
  pinMode(bothWaves,INPUT);
  Serial.begin(9600);
}

void loop() {

  while(1){
  
  if(digitalRead(bothWaves)){
    
     waveOne += HALFWAVEQUALITY/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,40,2086)));
     waveTwo += HALFWAVEQUALITY/(SAMPLERATE/(map(analogRead(pot2pin),0,1023,40,2086)));

     //Prevent waves from exceedind max amplitude
     if (waveOne > HALFWAVEQUALITY) waveOne -= HALFWAVEQUALITY;
     if (waveTwo > HALFWAVEQUALITY) waveTwo -= HALFWAVEQUALITY;
      
     PORTD =  waveOne + waveTwo;
  }
  else {
    waveOne += WAVEQUALITY/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,40,2086)));
    if (waveOne > WAVEQUALITY) waveOne -= WAVEQUALITY;
    PORTD = waveOne;

  }

  //wait for the right amount of time for 8000Hz
    sampleStop += SAMPLELENGTH;
    while(micros() < sampleStop){}
  }
}



