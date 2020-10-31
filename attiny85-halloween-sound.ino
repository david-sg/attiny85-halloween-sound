
// original file from https://create.arduino.cc/projecthub/aams86/add-lights-and-spooky-music-to-your-jack-o-lantern-de6d16
// shrunk the music a little to fit in the attiny, and use a sleep library to save batter.
// test show about 20ma when music playin, and 0.00x when sleeping.

#include "tinysnore.h" // Include TinySnore Library

int speakerPin = 1; //change to match pin for speaker (1 is physical pin 6 on the attiny85)
int numTones = 120; //change this to reflect the number of notes in your song
int cs6 = 1109; // frequencies of the notes used in the song
int fs5 = 740;
int d6 = 1175;
int c6 = 1047;
int f5 = 698;
int b5 = 988;
int e5 = 659;
int bf5 = 932;
int ef5 = 622;
int b4 = 494;
int g5 = 784;
int wait = 200;  // length of the notes

int tones[] = { cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5, //notes in the song
                cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5, 
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5,
                cs6, fs5, fs5, cs6, fs5, fs5, cs6, fs5,  d6, fs5,
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                 c6,  f5,  f5,  c6,  f5,  f5,  c6,  f5, cs6,  f5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                 b5,  e5,  e5,  b5,  e5,  e5,  b5,  e5,  c6,  e5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5,
                bf5, ef5, ef5, bf5, ef5, ef5, bf5, ef5,  b5, ef5};
        
unsigned long current_song_time = 0; unsigned long prev_song_time = 0; int note_count = 0; int on_off = 0; //variables for running the song

void setup(){

}

void loop()
{
  current_song_time = millis();
  if(on_off == 0)
  {
    if (current_song_time - prev_song_time >= 20){
      if(note_count+1==numTones){
        wait = 0; // set to 0 to add sleep
                snore(5000); // Deep sleeps for 5 seconds, (low power) then resumes from here
        on_off++;
        on_off %= 2;
      } else{
        prev_song_time = current_song_time;
        tone(speakerPin, tones[note_count]);
        on_off++;
        on_off %= 2;
      }
    }
  } else {
    if (current_song_time - prev_song_time >= wait){//delays[note_count]
      prev_song_time = current_song_time;
      noTone(speakerPin);
      note_count++;
      note_count %= numTones;
      on_off++;
      on_off %= 2;
      wait = 200;
    }
  }
}
