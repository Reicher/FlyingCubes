#pragma once

#include <cstdlib>
#include <ctime>
#include "SDL/SDL.h"

#include "Morph.h"

class BlinkLED;

class FlyingCube
{
 public:
  FlyingCube(SDL_Surface* screen, BlinkLED* LEDLight);

  void update(float ms);

  void draw();
 
 private:

  SDL_Surface* m_pScreen;
  int m_border;
  SDL_Rect m_shape;

  Morph<float> m_shapeMorphX, m_shapeMorphY;
  Morph<float> m_posMorphX, m_posMorphY;
  Morph<int> m_colorMorphR, m_colorMorphG, m_colorMorphB;
};
