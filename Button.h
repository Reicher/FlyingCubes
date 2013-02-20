#pragma once

#include <string>

#include "GPIOClass.h"

using namespace std;

class Button
{
 public:
  Button(string gpionum);

  bool IsPressedOnce();

 private:
  bool m_reported;
  GPIOClass m_button;
};
