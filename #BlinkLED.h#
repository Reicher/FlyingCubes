#pragma once

#include "GPIOClass.h"

class BlinkLED
{
 public:
  BlinkLED(string gpionum);

  void update(float dt);
  void setOnfor(int ms);
  void finish();
 
 private:
  GPIOClass m_LED;
  int m_time2Shine;

};
