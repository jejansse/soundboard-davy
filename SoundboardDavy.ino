/* SoundboardDavy.pde
 *
 * A soundboard with assorted sounds from Willy's en Marjetten.
 *
 */
#include <WaveHC.h>
#include <WaveUtil.h>
#include <Keypad.h>

// Keypad constants & init

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {A5, A2, A3, A4};
byte colPins[COLS] = {7, 8, 6};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Wave HC constants & init

SdReader card;  // This object holds the info for the card
FatVolume vol;  // This holds the info for the partition on the card
FatReader root;  // This holds the information for the volume root
FatReader file;  // This holds the information for the file
WaveHC wave;  // This is the wave (audio) object

// Function definition
void playFile(char* name);

void setup() {
  Serial.begin(9600);
  
  if (!card.init()) {
    Serial.println("Card init failed!");
  }
  
  // enable optimized read
  card.partialBlockRead(true);
  
  if (!vol.init(card)) {
    Serial.println("No partition found!");
  }
  
  if (!root.openRoot(vol)) {
    Serial.println("Couldn't open root dir!");
  }
  
  Serial.println("Files found:");
  root.ls();
}

void loop() {
  char key = kpd.getKey();
  if(key) {
    if(wave.isplaying) {
      wave.stop();
    }
    switch(key) {
     case('1'):
      playFile("drugs2");
      break;
     case('2'):
      playFile("kleine");
      break;
     case('3'):
      playFile("lindsay");
      break;
     case('4'):
      playFile("nolapola");
      break;
     case('5'):
      playFile("noprob~2");
      break;
     case('6'):
      playFile("okidokee");
      break;
     case('7'):
      playFile("prijsk~2");
      break;
     case('8'):
      playFile("tijdbom");
      break;
     case('9'):
      playFile("hondje");
      break;
     case('*'):
      playFile("tvidee");
      break;
     case('0'):
      playFile("vrouwt~1");
      break;
     case('#'):
      playFile("brugs");
      break;
     default:
      break;
    }
  }
}

void playFile(char* name) {
  char filename[13];
  
  (void)sprintf(filename, "%s.wav", name);
  Serial.print("File: ");
  Serial.println(filename);
  
  if (!file.open(root, filename)) {
    Serial.print("Couldn't open file ");
    Serial.println(filename);
    return;
  }
  if (!wave.create(file)) {
    Serial.println("Not a valid WAV");
    return;
  }
  wave.play();
  return;
}
