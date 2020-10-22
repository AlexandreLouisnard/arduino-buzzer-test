/*
*** DESCRIPTION ***
This code is used for buzzer testing on different software setups (DC/tone/toneAC, frequency, volume, etc.) and hardware setups (UC, voltage, with/without transistor, with/without serial/parallel resistor, etc.).

*** BUILD INSTRUCTIONS ***
1. main.h: Choose (uncomment) a UC below.
2. main.cpp: Uncomment #include <toneAC.h> if needed (not compatible with ATTiny85).
3. platformio.ini: Uncomment build config for the chosen UC.
	** Note: beware that UC freq value (burnt in bootloader and defined in platformio.ini, they msut be the same) have an impact on the tone() sound. For tone() to produce a correct sound, freq must be set at least to to 8 MHz (and the bootloader must be burnt with that frequency too).
4. Wire circuit according to pins defined below.
		* With tone() and playDCsound(), BUZZER_PIN controls a transistor wired such as Vcc -> buzzer + -> buzzer - -> transistor C -> transistor E -> GND.
		* With toneAC(), buzzer is directly wired between the pins.

*** USE INSTRUCTIONS ***
Uses both tone() (from Arduino) and toneAC (from library) :
- tone() on pin BUZZER_PIN
- toneAC() on pins :
     Pins  9 & 10 - ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, etc.
     Pins 11 & 12 - ATmega2560/2561, ATmega1280/1281, Mega
     Pins 12 & 13 - ATmega1284P, ATmega644
     Pins 14 & 15 - Teensy 2.0
     Pins 25 & 26 - Teensy++ 2.0

Press :
spacebar to pause/resume the sound
a to increase freq
q to decrease freq
z to increase freq by zz100
s to decrease freq by 100
e to increase volume
d to decrease volume
1 to play DC sound
2 to play a melody
*/

////////////// CHOOSE A UC //////////////
#define ARDUINO_NANO
// #define ATTINY85
 ////////////////////////////////////////

#ifdef ARDUINO_NANO
#define BUZZER_PIN 8
// With toneAC, buzzer pins are D9 & D10
#endif

#ifdef ATTINY85
#define BUZZER_PIN PB3
// toneAC does not work with ATTiny85
#endif

#define WHOLE_NOTE_DURATION_MS 600


#ifdef ARDUINO_NANO
boolean checkSerialInput();
#endif

/**
 * Plays a melody.
 * 
 * *notes: the notes
 * notesSize: the notes array size
 * *notesDuration: each note duration (1 (or 0, default) for a whole note, 4 for a quarter note, 8 for an eight note, etc.)
 */
void playMelody(uint16_t *notes, uint16_t notesSize, uint16_t *notesDurations);

void playAllNotes();

/**
 * Applies DC current to BUZZER_PIN for 1 second, without using any tone function.
 */
void playDCsound();
