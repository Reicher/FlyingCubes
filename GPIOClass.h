#pragma once

#include <string>

using namespace std;

//! Brief Each object instantiated from this class will control a GPIO pin
class GPIOClass
{
 public:

  //! Creates a GPIO object that controls GPIO4
  GPIOClass();

  //! Creates a GPIO object that controls a GPIO pin
  //! @param x Pin number to control
  GPIOClass( string x);
  
  //! Exports GPIO
  int export_gpio();

  //! Unexports GPIO
  int unexport_gpio();

  //! Set direction
  int setdir_gpio( string dir);

  //! Set value (for input pins)
  int setval_gpio( string val);

  //! Get the current value of the pin
  int getval_gpio( string& val);

  //! Returns the GPIO number associated with this pin
  string get_gpionum();
 
 private:
  string gpionum;
};
