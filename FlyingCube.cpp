#include "FlyingCube.h"
#include "BlinkLED.h"

FlyingCube::FlyingCube(SDL_Surface* screen, BlinkLED* LEDLight)
  : m_pScreen( screen )
  , m_border(0)
  , m_shapeMorphX(30.0, 150.0, 2.0)
  , m_shapeMorphY(30.0, 100.0, 2.0)
  , m_posMorphX((float)m_border, (float)screen->w - m_border - m_shapeMorphX.m_max, 2.0)
  , m_posMorphY((float)m_border, (float)screen->h - m_border - m_shapeMorphY.m_max, 2.0)
  , m_colorMorphR(0, 255, 2)
  , m_colorMorphG(0, 255, 2)
  , m_colorMorphB(0, 255, 2)
{
  m_posMorphX.setLED(LEDLight);
  m_posMorphY.setLED(LEDLight);

  update(0);
};

void FlyingCube::update(float ms)
{
  //Order Important!
  // Randomize and set dimenstions
  
  m_shape.w = m_shapeMorphX.update(ms);
  m_shape.h = m_shapeMorphY.update(ms);

  //Randomize and set position
  m_posMorphX.m_max = m_pScreen->w - m_border - m_shape.w;
  m_posMorphY.m_max = m_pScreen->h - m_border - m_shape.h;
  m_shape.x = m_posMorphX.update(ms);
  m_shape.y = m_posMorphY.update(ms);

  //Randomize color
  m_colorMorphR.update(ms);
  m_colorMorphG.update(ms);
  m_colorMorphB.update(ms);
};

void FlyingCube::draw()
{
  SDL_FillRect( m_pScreen, &m_shape, SDL_MapRGB(m_pScreen->format
	      , m_colorMorphR.m_current
	      , m_colorMorphG.m_current
	      , m_colorMorphB.m_current) );
};

