#pragma once

#include "Helpers.h"
#include "GPIOClass.h" 

template <typename T>
class Morph
{
 public:
  Morph();

  Morph(T min, T max, T v = 1);

  void setLED(GPIOClass* LED);
  T update();

  int m_cycles, m_period, m_flip;
  T m_min, m_max, m_v, m_current;

  GPIOClass* m_LED;
};
