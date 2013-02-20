#include "Button.h"

Button::Button(string gpionum)
  : m_button(gpionum)
  , m_reported(false)
{
  m_button.export_gpio();
  m_button.setdir_gpio("in");

 
}

bool Button::IsPressedOnce()
{
  string val;
  m_button.getval_gpio(val);
  bool pressed = val == "0" ? true : false;

  if(pressed && !m_reported)
    {
      m_reported = true;
      return true;
    } 
  else if(!pressed && m_reported)
    m_reported = false;
 
  return false;
}
