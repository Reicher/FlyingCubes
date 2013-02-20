#include <stdio.h>
#include <iostream>
#include <list>
#include <cstdlib>

#include "SDL/SDL.h"
#include "FlyingCube.h"
#include "BlinkLED.h"
#include "Button.h"

using namespace std;

int main( int argc, char* argv[] )
{
  BlinkLED* LEDLight = NULL;
  Button* iButton = NULL;
  Button* dButton = NULL;
  int nCubes = 1;

  //Get user input
  for(int a = 1; a < argc; a++)
    {
      if(strcmp(argv[a], "-c") == 0 && argc > a)
	nCubes = atoi(argv[a+1]);
      else if(strcmp(argv[a], "-l") == 0 && argc > a)
	LEDLight = new BlinkLED(argv[a+1]);
      else if(strcmp(argv[a], "-ib") == 0 && argc > a)
	iButton = new Button(argv[a+1]);
      else if(strcmp(argv[a], "-db") == 0 && argc > a)
	dButton = new Button(argv[a+1]);
    }

  srand(static_cast<unsigned>(time(0)));
  Uint32 m_oldTime, m_currentTime;
  float ftime;
  m_currentTime = SDL_GetTicks();

  //Start SDL
  SDL_Init( SDL_INIT_VIDEO );

  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  int systemX = videoInfo->current_w;
  int systemY = videoInfo->current_h;
  Uint8 bpp = videoInfo->vfmt->BitsPerPixel;

  //Set up screen
  SDL_Surface* screen = NULL;
  screen = SDL_SetVideoMode(systemX, systemY, bpp, SDL_SWSURFACE);

  if(!screen)
    {
      printf( "SDL_SetVideoMode fialed:( \n" );
      return 0;
    }

  list<FlyingCube> cubes;
  for(int i = 0; i < nCubes; i++)
    {
      cubes.push_back(FlyingCube(screen, LEDLight));
    }

  bool isRunning = true;
  SDL_Event event;

  while( isRunning){

    m_oldTime = m_currentTime;
    m_currentTime = SDL_GetTicks();
    ftime = (m_currentTime - m_oldTime) / 1000.0f;

    SDL_FillRect(screen, NULL, 0x0000000);

    if( SDL_PollEvent( &event ) )
      {
	if( event.type == SDL_KEYDOWN )
	  {
	    SDLKey keyPressed = event.key.keysym.sym;
	    switch( keyPressed )
	      {
	      case SDLK_ESCAPE:
		isRunning = false;
		break;
	      }
	  }
      }

    //Drawin
    for(list<FlyingCube>::iterator it = cubes.begin(); it != cubes.end(); ++it)
      {
	it->update(ftime);
	it->draw();
      }

    //LEDS
    if(LEDLight)
      LEDLight->update(ftime);

    //Buttons
    if(iButton)
      {
	if(iButton->IsPressedOnce())
	  cubes.push_back(FlyingCube(screen, LEDLight));
      }
    if(dButton)
      {
	if(dButton->IsPressedOnce())
	  cubes.pop_back();
      }

    //Update screem
    SDL_Flip( screen );

    SDL_Delay( 10 );
  }

  //Turn off and unexport gpio
  if(LEDLight)
    LEDLight->finish();

  //Quit SDL
  SDL_Quit();

  return 0;
}
