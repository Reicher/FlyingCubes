#include "FlyingCube.h"

FlyingCube::FlyingCube(SDL_Surface* screen, GPIOClass* LEDLight)
  : m_pScreen( screen )
  , m_border(0)
  , m_shapeMorphX(30.0, 150.0, 3.0)
  , m_shapeMorphY(30.0, 100.0, 3.0)
  , m_posMorphX((float)m_border, (float)screen->w - m_border - m_shapeMorphX.m_max, 3.0)
  , m_posMorphY((float)m_border, (float)screen->h - m_border - m_shapeMorphY.m_max, 3.0)
  , m_colorMorphR(0, 255, 3)
  , m_colorMorphG(0, 255, 3)
  , m_colorMorphB(0, 255, 3)
{
  update();
};

void FlyingCube::update()
{
  //Order Important!
  // Randomize and set dimenstions
  
  m_shape.w = m_shapeMorphX.update();
  m_shape.h = m_shapeMorphY.update();

  //Randomize and set position
  m_shape.x = m_posMorphX.update();
  m_shape.y = m_posMorphY.update();

  //Randomize color
  m_colorMorphR.update();
  m_colorMorphG.update();
  m_colorMorphB.update();

  //  m_posMorphX.update(m_border, m_pScreen->w - m_border - m_shapeMorphX.m_current);
  //  m_posMorphY.update(m_border, m_pScreen->h - m_border - m_shapeMorphY.m_current);
};

void FlyingCube::draw()
{
  SDL_FillRect( m_pScreen, &m_shape, SDL_MapRGB(m_pScreen->format
	      , m_colorMorphR.m_current
	      , m_colorMorphG.m_current
	      , m_colorMorphB.m_current) );
};

