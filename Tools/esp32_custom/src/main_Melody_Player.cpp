// #include <Arduino.h>
// #include <melody_player.h>
// #include <melody_factory.h>

// int buzzerPin = GPIO_NUM_27;

// const char melodyString[] = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";

// MelodyPlayer player(buzzerPin);

// void setup() {
//   Serial.begin(115200);
//   while (!Serial)
//     ;

//   Serial.println();
//   Serial.println("Melody Player - Load RTTTL melody");

//   Serial.print("Loading hardcoded melody... ");
//   Melody melody = MelodyFactory.loadRtttlString(melodyString);
//   if (melody) {
//     Serial.println("Done!");
//     Serial.print("Playing ");
//     Serial.print(melody.getTitle());
//     Serial.print("... ");
//     player.play(melody);
//     Serial.println("Done!");
//   } else {
//     Serial.println("Error");
//   }

//   delay(1000);
// }

// void loop() {}