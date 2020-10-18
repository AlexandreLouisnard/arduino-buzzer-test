/**
 * Buzzer test with Arduino: notes: melody, etc.
 * 
 * Uses both tone() (from Android) and toneAC (from library) :
 * - tone() on pin BUZZER_PIN
 * - toneAC() on pins :
 *      Pins  9 & 10 - ATmega328, ATmega128, ATmega640, ATmega8, Uno, Leonardo, etc.
 *      Pins 11 & 12 - ATmega2560/2561, ATmega1280/1281, Mega
 *      Pins 12 & 13 - ATmega1284P, ATmega644
 *      Pins 14 & 15 - Teensy 2.0
 *      Pins 25 & 26 - Teensy++ 2.0
 * 
 * Press :
 * spacebar to pause/resume the sound
 * a to increase freq
 * q to decrease freq
 * z to increase freq by zz100
 * s to decrease freq by 100
 * e to increase volume
 * d to decrease volume
 * 1 to play DC sound
 * 2 to play a melody
 */

#include <Arduino.h>
#include "main.h"
// Only include toneAC for Arduino
// #include <toneAC.h>
#include "pitches.h"
#include "ArduinoUtils.h"

// Buzzer control
int freq = 440; // Hz
#ifdef ARDUINO_NANO
int vol = 10; // Volume for toneAC from 0 to 10
#endif
int pause = false;

void setup()
{
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  int previousFreq = freq;
#ifdef ARDUINO_NANO
  int previousVol = vol;
#endif
  if (Serial.available() > 0)
  {
    char receivedChar = Serial.read();
    ardprintf("pressed %c", (char *)receivedChar);
    switch (receivedChar)
    {

    case ' ':
      pause = !pause;
      ardprintf("pause = %d", pause);
      break;
    case 'a':
      freq++;
      break;
    case 'q':
      freq--;
      break;
    case 'z':
      freq += 100;
      break;
    case 's':
      freq -= 100;
      break;
#ifdef ARDUINO_NANO
    case 'e':
      if (vol < 10)
      {
        vol++;
      }
      break;
    case 'd':
      if (vol > 0)
      {
        vol--;
      }
      break;
#endif
    case '1':
      // Play DC sound
      playDCsound();
      break;
    case '2':
      // Play a melody
      int melody[] = {
          NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
      int notesDurations[] = {
          4, 8, 8, 4, 4, 4, 4, 4};
      playMelody(melody, 8, notesDurations);
      break;
    }
  }

  if (previousFreq != freq)
  {
    ardprintf("f = %d Hz", freq);
  }

#ifdef ARDUINO_NANO
  if (previousVol != vol)
  {
    ardprintf("vol = %d (from 0 to 10)", vol);
  }
#endif

  if (pause == true)
  {
    noTone(BUZZER_PIN);
#ifdef ARDUINO_NANO
    noToneAC();
#endif
  }
  else
  {
    tone(BUZZER_PIN, freq);
#ifdef ARDUINO_NANO
    toneAC(freq, vol);
#endif
  }
}

void playMelody(int melody[], int size, int notesDurations[])
{
  ardprintf("playMelody() with %d notes", size);
  for (int thisNote = 0; thisNote < size; thisNote++)
  {
    int noteDuration = WHOLE_NOTE_DURATION_MS;
    if (notesDurations != 0 && notesDurations[thisNote] != 0)
    {
      noteDuration = noteDuration / notesDurations[thisNote];
    }
    ardprintf("note: %d Hz, %d ms", melody[thisNote], noteDuration);

    tone(BUZZER_PIN, melody[thisNote], noteDuration);
#ifdef ARDUINO_NANO
    toneAC(melody[thisNote], vol, noteDuration, true);
#endif

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(BUZZER_PIN);
#ifdef ARDUINO_NANO
    noToneAC();
#endif
  }
}

void playDCsound()
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}