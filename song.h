#include "pitches.h"

#define BUZZER_PIN 26
// Pokémon battle theme melody
int melody[] = {
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_F4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4,
    NOTE_A4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_D4, NOTE_F4, NOTE_E4,
    NOTE_F4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4,
    NOTE_AS4, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4,
    NOTE_F4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_F4, NOTE_G4,
    NOTE_D4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4,
    NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_AS4, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4};
int noteDurations[] = {
    8, 8, 8, 8, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    8, 8, 8, 8, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    8, 8, 8, 8, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    
void playSong()
{
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++)
  {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);

    noTone(BUZZER_PIN);
  }
}
