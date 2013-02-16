#include "BlinkLED.h"

#include <iostream>

BlinkLED::BlinkLED(string gpionum)
  : m_LED(gpionum)
  , m_time2Shine(0)
{
  m_LED.export_gpio();
  m_LED.setdir_gpio("out");
}

void BlinkLED::update(float dt)
{

  string val;
  m_LED.getval_gpio(val);
  if(val == "0" && m_time2Shine > 0)
    {
      m_LED.setval_gpio("1");
    }
  else if(val == "1" && m_time2Shine < 0)
    {
      m_LED.setval_gpio("0");
    }
  
  m_time2Shine -= dt;
 
}

void BlinkLED::setOnFor(int ms)
{
  m_time2Shine = (float)ms/1000.0f;
}

void BlinkLED::finish()
{
  m_LED.setval_gpio("0");
  m_LED.unexport_gpio();
}
