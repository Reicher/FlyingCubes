#pragma once

#include "Helpers.h"

class BlinkLED; 

template <typename T>
class Morph
{
 public:
  Morph();

  Morph(T min, T max, T v = 1);

  void setLED(BlinkLED* LED);
  T update(float dt);

  int m_cycles, m_period, m_flip;
  T m_min, m_max, m_v, m_current;

  BlinkLED* m_LED;
};
