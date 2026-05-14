# ESP32 Melody Laser Transmitter

### Short Story

This is a project I made once I knew how to they use light to send data (especially in internet). It plays a melody on an ESP32, sends the sound through a laser, and picks it up with a solar panel connected to a speaker.Then enjoy your music.

### How It Works

The ESP32 makes tones on pin 25. That signal goes into a transistor that turns the laser on and off really fast (so fast it looks like it's dimming). The laser light hits a solar panel, which changes light back into electricity. Then the speaker amplifies it and you hear the melody.

### Parts list

- ESP32 board (any kind)
- Laser diode (red, 5mW, cheap from Amazon)
- NPN transistor (any)
- Resistors: 1k ohm and 100 ohm
- Small solar panel (I got a 5V one from an old light)
- Powered speaker (any with aux input works)
- lithium battery or phone charger for the laser (optional you can connect to the vin but be careful it can harm components)
- Wires and breadboard

### Circuit

Transmitter side:

- ESP32 pin 25 -> 1k resistor -> transistor base
- Transistor emitter -> ground (connect to ESP32 ground)
- Transistor collector -> laser negative (short leg)
- Laser positive (long leg) -> 100 ohm resistor -> +5V from the power source 
- Also connect the power source's ground to ESP32 ground

Receiver side is easy: just connect the solar panel wires to a 3.5mm audio cable. Positive to the tip, negative to the sleeve. Plug that into the speaker.

### Code

Here's the code. It plays a short melody.

```cpp
#define LEDC_CHANNEL 0
#define LEDC_TIMER_BIT 8

#define do 262
#define re 294
#define sol 392
#define la 440
#define siB 466
#define fa 349
#define miB 311

int melody[] = {re, sol, la, siB, la, sol, fa, miB, miB, re, miB, re, miB, do, sol};
int durations[] = {2, 2, 8, 8, 8, 4, 8, 8, 2, 8, 8, 8, 8, 2, 2};
// 2=half, 4=quarter, 8=eighth

bool playing = false;

void setup() {
  ledcSetup(LEDC_CHANNEL, 2000, LEDC_TIMER_BIT);
  ledcAttachPin(25, LEDC_CHANNEL);
}

void loop() {
  playMelody(melody, durations, 15);
  delay(1000);
}

void playMelody(int notes[], int durations[], int length) {
  if (playing) return;
  playing = true;
  
  for (int i = 0; i < length; i++) {
    int durationMs = 1000 / durations[i];
    ledcWriteTone(LEDC_CHANNEL, notes[i]);
    delay(durationMs);
    ledcWriteTone(LEDC_CHANNEL, 0);
    delay(durationMs * 0.3);
  }
  
  playing = false;
}
```

To change the song, just change the numbers in the melody array. You can look up note frequencies online.

### Setup Steps

1. Upload the code to ESP32 using Arduino IDE.
2. Build the laser driver circuit on a breadboard.
3. Aim the laser at the solar panel (start close, like 10cm).
4. Connect solar panel to speaker.
5. Turn on speaker (low volume first).
6. Power ESP32 and the laser supply. Should hear the song.

### Problems I Ran Into (troubleshooting)

- No sound: Forgot to connect grounds together. The ESP32 ground and the charger ground must be connected.
- Laser always on: My transistor was backwards. Collector and emitter matter.
- Distorted audio: Too much ambient light on the solar panel. I put a paper tube between laser and panel to block room light. (I didn't run into this)
- Quiet sound: Move laser closer or get a bigger solar panel.

### Safety

**Don't** point the laser at **anyone's eyes**. Even a small one can **hurt**. I aimed mine at a wall and put the solar panel in front of it.

### Conclusion

This was a fun project. It shows how light can carry sound. I got it working across my room (about 3 to 4 meters). You could probably go farther with a better laser or bigger panel.

### License 

**MIT** - Open Source

### Author 

George Tomeh
