#pragma once

#include "GPIOClass.h"
 
class BlinkLED
{
 public:
  BlinkLED(string gpionum);

  void update(float dt);
  void setOnFor(int ms);
  void finish();
 
 private:
  GPIOClass m_LED;
  float m_time2Shine;

};
