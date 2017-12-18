/* Author: Viktor Fries
 * Date: Dec 18, 2017
 * 
 * This is the main source file for the code run by the arduino.
 * It contains the formulas that allow it to produce waves
 * and control a speaker in a ruben's tube.
 * 
 * Pins 0-7 will be used to control a Digital to Analog Converter
 * which will allow for the creation of 8 bit audio
 * 
 */
 
///////////////////////
// DEFINED CONSTANTS //
///////////////////////
// DEFAULT: 8000.0
#define SAMPLERATE      8000.0  // The number of audio samples created per sececond
// DEFAULT: 125.0 
#define SAMPLELENGTH    125.0   // 1 000 000 / SAMPLERATE
// DEFAULT: 256
#define AMPLITUDE       256     // The maximum amplitude of a generated wave
// DEFAULT: 128
#define HALFAMPLITUDE   128     // AMPLITUDE / 2
// DEFAULT: 2086
#define MAXFREQ         2086    // The maximum frequency wave that can be generated
// DEFAULT: 40
#define MINFREQ         40      // The minimum frequency wave that can be generated

////////////////
// INPUT PINS //
////////////////
// DEFAULT: A0
#define pot1pin         A0      // Input pin of the first potentiometer
// DEFAULT: A1
#define pot2pin         A1      // Input pin of the second potentiometer
// DEFAULT: 8
#define bothWaves       8       // Input for the switch

// Record the time the program starts
long startTime = micros();
// Floats to store the current amplitude of the generated waves
float waveOne = 0, waveTwo = 0;

///////////
// SETUP //
///////////
void setup() {
  // Initialize PORTD for the DAC
  DDRD = B11111111;
  // Set digital pin to input
  pinMode(bothWaves,INPUT);
}

//////////
// LOOP //
//////////
void loop() {
  // While is faster than void loop()
  while(1){

  // If bothWaves is HIGH run logic for generating two waves
  if(digitalRead(bothWaves)){
     // Map the input of the corresponding potentiometer to the min and max frequency
     // Then convert it to the rate of change per sample by HALFAMPLITUDE(SAMPLERATE/FREQUENCY)
     // Only half the amplitude is to prevent waveOne + waveTwo from ever being greater than
     // Amplitude
     waveOne += HALFAMPLITUDE/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,MINFREQ,MAXFREQ)));
     waveTwo += HALFAMPLITUDE/(SAMPLERATE/(map(analogRead(pot2pin),0,1023,MINFREQ,MAXFREQ)));

     // Prevent waves from exceeding max amplitude
     // Also prevents possibility of exceeding maximum float size 
     if (waveOne > HALFAMPLITUDE) waveOne -= HALFAMPLITUDE;
     if (waveTwo > HALFAMPLITUDE) waveTwo -= HALFAMPLITUDE;

     // Output the waves to the DAC. 
     // Conversion of float to int occurs automatically
     PORTD =  waveOne + waveTwo;
  }
  // Else run logic for generating one wave
  else {
    // Map the input of the corresponding potentiometer to the min and max frequency
    // Then convert it to the rate of change per sample by HALFAMPLITUDE(SAMPLERATE/FREQUENCY)
    // Only half the amplitude is to prevent waveOne + waveTwo from ever being greater than
    // Amplitude
    waveOne += AMPLITUDE/(SAMPLERATE/(map(analogRead(pot1pin),0,1023,MINFREQ,MAXFREQ)));

    // Prevent wave from exceeding max amplitude
    // Also prevents possibility of exceeding maximum float size
    if (waveOne > AMPLITUDE) waveOne -= AMPLITUDE;

    // Output the wave to the DAC. 
    // Conversion of float to int occurs automatically
    PORTD = waveOne;

  }

    // Wait until SAMPLELENGTH microseconds have passed
    // to output audio at SAMPLERATE Hz
    startTime += SAMPLELENGTH;
    while(micros() < startTime){}
  }
}



