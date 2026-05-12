#define LEDC_CHANNEL 0
#define LEDC_TIMER_BIT 8

#define do 262
#define re  294
#define sol  392
#define la  440
#define siB 466
#define fa  349
#define miB 311

int melody[] = { re, sol, la, siB, la, sol, fa, miB, miB, re, miB, re, miB, do, sol};
int durations[] = { 2 , 2, 8, 8, 8, 4, 8, 8, 2, 8, 8, 8, 8 , 2 , 2 };
// 2 = half note
// 4 = quarter 
//  8 = eighth

bool playingNow = false;

void setup() {
  Serial.begin(115200);
  
  ledcSetup(LEDC_CHANNEL, 2000, LEDC_TIMER_BIT);
  ledcAttachPin(25, LEDC_CHANNEL);
}

void loop() {
  playMelody(melody, durations, sizeof(melody) / sizeof(melody[0]));
  delay(1000);
}

void playMelody(int notes[], int durations[], int length) {
  if (playingNow) return;
  playingNow = true;
  
  for (int i = 0; i < length; i++) {
    int duration = 1000 / durations[i]; 
    
    ledcWriteTone(LEDC_CHANNEL, notes[i]);
    
    delay(duration);
    
    ledcWriteTone(LEDC_CHANNEL, 0);
    delay(duration * 0.3); // 30%
  }
  
  playingNow = false;
}