#ifndef __FADER_H
#define __FADER_H

#include <Arduino.h>
#include <FastCapacitiveSensor.h>

#define VMAX 5.0
#define THRESHOLD 10
#define U_FREQUENCY 10
#define RATIO 0.2
#define M_THRESHOLD 0.02
#define T_THRESHOLD 27.5

class Fader {
  private:
    FastCapacitiveSensor fTouch;
    uint8_t cOutPin;
    uint8_t cInPin;
    uint8_t fInPin;
    uint8_t motA;
    uint8_t motB;
    uint16_t toFade;
    bool toFadeOn;
    bool touchResume;

  public:
    Fader(uint8_t cOutPin, uint8_t cInPin, uint8_t fInPin, uint8_t motA, uint8_t motB);
    void init();
    uint16_t getFader();
    bool getTouch();
    void update();
    void setFader(uint16_t toFade, bool touchResume = false);
};

#endif
