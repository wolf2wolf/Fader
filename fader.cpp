#include "fader.h"

Fader::Fader(uint8_t cOutPin, uint8_t cInPin, uint8_t fInPin, uint8_t motA, uint8_t motB) {
  this-> cOutPin = cOutPin;
  this-> cInPin = cInPin;
  this-> fInPin = fInPin;
  this-> motA = motA;
  this-> motB = motB;
  init();
}

void Fader::init() {
  pinMode(cOutPin, OUTPUT);
  pinMode(motA, OUTPUT);
  pinMode(motB, OUTPUT);

  pinMode(cInPin, INPUT);
  pinMode(fInPin, INPUT);

  //analogReadRes(12);        // Changing ADC resolution to 12 bits (4095)
  //analogReadAveraging(32);  // To reduce noise, average 32 samples each read.

  fTouch.begin(cOutPin, cInPin, VMAX, U_FREQUENCY, THRESHOLD, RATIO);
  toFadeOn = false;
  touchResume = false;
}

uint16_t Fader::getFader() {
  return analogRead(fInPin);
}

bool Fader::getTouch() {
  // need to figure out the threshold for touch
  return ((fTouch.touch() < T_THRESHOLD) ? true : false);
}

void Fader::update() {
  // if a move command is active, check if slider is in correct position
  // if slider is out of position, make sure motor is on
  // if touch is detected, make sure motor is idle
  // if interrupt resume is off, disable move command if touch is detected
  
  if (!toFadeOn) {
    digitalWrite(motA, LOW);
    digitalWrite(motB, LOW);
    return;
  }

  if (getTouch()) {
    if (!touchResume) toFadeOn = false;
    digitalWrite(motA, LOW);
    digitalWrite(motB, LOW);
    return;
  }

  uint16_t curVal = getFader();
  if ((curVal > toFade * (1 - M_THRESHOLD)) && (curVal < toFade * (1 + M_THRESHOLD))) {
    digitalWrite(motA, LOW);
    digitalWrite(motB, LOW);
    return;
  }

  if (getFader() > toFade) {
    digitalWrite(motA, HIGH);
    digitalWrite(motB, LOW);
  }else if (getFader() < toFade) {
    digitalWrite(motA, LOW);
    digitalWrite(motB, HIGH);
  }
}

void Fader::setFader(uint16_t toFade, bool touchResume) {
  this-> toFade = toFade;
  this-> touchResume = touchResume;
  toFadeOn = true;
}
