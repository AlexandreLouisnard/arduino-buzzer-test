#include <Arduino.h>
#include "main.h"
// Only include toneAC for Arduino
#include <toneAC.h>
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
#ifdef ARDUINO_NANO
  Serial.begin(9600);
#endif

  pinMode(BUZZER_PIN, OUTPUT);

  // playAllNotes();
}

void loop()
{
#ifdef ARDUINO_NANO
  checkSerialInput();
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

#ifdef ARDUINO_NANO
boolean checkSerialInput()
{
  int previousFreq = freq;
#ifdef ARDUINO_NANO
  int previousVol = vol;
#endif

  if (Serial.available() > 0)
  {
    char receivedChar = (char)Serial.read();
    ardprintf("pressed %c", (char *)receivedChar);
    switch (receivedChar)
    {

    case ' ':
    {
      pause = !pause;
      ardprintf("pause = %d", pause);
      break;
    }
    case 'a':
    {
      freq++;
      break;
    }
    case 'q':
    {
      freq--;
      break;
    }
    case 'z':
    {
      freq += 100;
      break;
    }
    case 's':
    {
      freq -= 100;
      break;
    }
#ifdef ARDUINO_NANO
    case 'e':
    {
      if (vol < 10)
      {
        vol++;
      }
      break;
    }
    case 'd':
    {
      if (vol > 0)
      {
        vol--;
      }
      break;
    }
#endif
    case '1':
    { // Play DC sound
      playDCsound();
      break;
    }
    case '2':
    {
      // Play a melody
      uint16_t notes[] = {
          NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
      uint16_t notesDurations[] = {
          4, 8, 8, 4, 4, 4, 4, 4};
      playMelody(notes, 8, notesDurations);
      break;
    }
    case '3':
    { // Play all notes
      playAllNotes();
      break;
    }
    default:
      return false;
    }
  }
  else
  {
    return false;
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

  return true;
}
#endif

void playMelody(uint16_t *notes, uint16_t notesSize, uint16_t *notesDurations)
{
#ifdef ARDUINO_NANO
  ardprintf("playMelody() with %d notes", notesSize);
#endif
  for (uint16_t i = 0; i < notesSize; i++)
  {
#ifdef ARDUINO_NANO
    if (checkSerialInput() == true)
    {
      return;
    }
#endif
    uint16_t noteDuration = WHOLE_NOTE_DURATION_MS;
    if (notesDurations != NULL && notesDurations[i] != 0)
    {
      noteDuration = noteDuration / notesDurations[i];
    }

#ifdef ARDUINO_NANO
    ardprintf("note: %d Hz, %d ms", notes[i], noteDuration);
    toneAC(notes[i], vol, noteDuration, true);
#endif
    tone(BUZZER_PIN, notes[i], noteDuration);

    delay(noteDuration * 1.2);

#ifdef ARDUINO_NANO
    noToneAC();
#endif
    noTone(BUZZER_PIN);
  }
}

void playAllNotes()
{
#ifdef ARDUINO_NANO
  ardprintf("playAllNotes()");
#endif
#define NOTES_COUNT 68
  uint16_t notes[] = {/* 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98,  */ 104, 110, 117, 124, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 699, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2218, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978 /* , 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544, 13290, 14080, 14917, 15804, 16744, 17740, 18795, 19912, 21096, 22351, 23680, 25088, 26580, 28160, 29834, 31609 */};
  playMelody(notes, NOTES_COUNT, NULL);
}

void playDCsound()
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}
