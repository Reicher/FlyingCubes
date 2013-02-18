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
  T update(const float dt);

  int m_cycles, m_period, m_direction;
  T m_min, m_max, m_v, m_current;

 private:
  bool hitRoof();
  bool hitFloor();
  void keepWithinBorders();

  BlinkLED* m_LED;
};
