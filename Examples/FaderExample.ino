#include "fader.h"

//      (Cap out, Cap in, Res in, Mot A, Mot B)
Fader f1(2, A9, A8, 3, 4);

void setup()                    
{
   Serial.begin(4608000);
   Serial.println("Serial initialized");
  // Serial.println(f1.getFader());
   Serial.println((f1.getTouch()) ? "Touch" : "No Touch");
   f1.setFader(512, true);
}

void loop()                    
{
    f1.update();
    Serial.println(f1.getFader());
}
