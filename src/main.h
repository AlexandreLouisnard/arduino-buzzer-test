// DESCRIPTION:
// This code is used for buzzer testing on different software setups (DC/tone/toneAC, frequency, volume, etc.) and hardware setups (UC, voltage, with/without transistor, with/without serial/parallel resistor, etc.).

// INSTRUCTIONS:
// 1. main.h: Choose (uncomment) a UC below.
// 2. main.cpp: Uncomment #include <toneAC.h> if needed (not compatible with ATTiny85).
// 3. platformio.ini: Uncomment build config for the chosen UC.
// 4. Wire circuit according to pins defined below.
// 		* With tone() and playDCsound(), BUZZER_PIN controls a transistor wired such as Vcc -> buzzer + -> buzzer - -> transistor C -> transistor E -> GND.
//		* With toneAC(), buzzer is directly wired between the pins.

// NOTES:
// * UC freq (burnt in bootloader and defined in platformio.ini) have an impact on the tone sound.


// Choose a UC
// #define ARDUINO_NANO
#define ATTINY85

#ifdef ARDUINO_NANO
#define BUZZER_PIN 8
// With toneAC, buzzer pins are D9 & D10
#endif

#ifdef ATTINY85
#define BUZZER_PIN PB3
// toneAC does not work with ATTiny85
#endif

#define WHOLE_NOTE_DURATION_MS 600

/**
 * Plays a melody.
 * 
 * melody[]: the notes
 * size: the melody[] size
 * notesDuration[]: each note duration (1 (or 0, default) for a whole note, 4 for a quarter note, 8 for an eight note, etc.)
 */
void playMelody(int melody[], int size, int notesDurations[]);

/**
 * Applies DC current to BUZZER_PIN for 1 second, without using any tone function.
 */
void playDCsound();
