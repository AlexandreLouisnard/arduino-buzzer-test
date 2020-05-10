/**
 * Buzzer test with Arduino: notes: melody, etc.
 * 
 * SETUP: plays a melody, plays all notes.
 * LOOP: plays a note. Press +/- and p/m to increase/decrease frequency. Press s to start/stop the noise.
 */

#include <Arduino.h>
#include "pitches.h"
#include "main.h"
#include "ArduinoUtils.h"

#define BUZZER_PIN 8
#define WHOLE_NOTE_DURATION_MS 600

// Buzzer copntrol
int freq = 440; // Hz
int pause = false;

void setup()
{
  Serial.begin(9600);

  // Play buzzer without tone
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2 * WHOLE_NOTE_DURATION_MS);
  digitalWrite(BUZZER_PIN, LOW);

  // Play a melody
  int melody[] = {
      NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
  int notesDurations[] = {
      4, 8, 8, 4, 4, 4, 4, 4};
  playMelody(melody, 8, notesDurations);

  // Play all notes
  // playMelody(ALL_NOTES, ALL_NOTES_COUNT, 0);
}

void loop()
{
  int previousFreq = freq;
  if (Serial.available() > 0)
  {
    char receivedChar = Serial.read();
    ardprintf("pressed %c", (char *)receivedChar);
    switch (receivedChar)
    {
    case '+':
      freq++;
      break;
    case '-':
      freq--;
      break;
    case 'p':
      freq += 100;
      break;
    case 'm':
      freq -= 100;
      break;
    case 's':
      pause = !pause;
      break;
    }
  }

  if (previousFreq != freq)
  {
    ardprintf("f = %d Hz", freq);
  }

  if (pause == true)
  {
    noTone(BUZZER_PIN);
  }
  else
  {
    tone(BUZZER_PIN, freq);
  }
}

void playMelody(int melody[], int size, int notesDurations[])
{
  ardprintf("playMelody() with notes: %d ", size);
  for (int thisNote = 0; thisNote < size; thisNote++)
  {
    int noteDuration = WHOLE_NOTE_DURATION_MS;
    if (notesDurations != 0 && notesDurations[thisNote] != 0)
    {
      noteDuration = noteDuration / notesDurations[thisNote];
    }
    ardprintf("note: %d Hz, %d ms", melody[thisNote], noteDuration);

    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(BUZZER_PIN);
  }
}