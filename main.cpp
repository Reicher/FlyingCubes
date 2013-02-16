#include <stdio.h>
#include <list>
#include <cstdlib>

#include "SDL/SDL.h"
#include "FlyingCube.h"
#include "BlinkLED.h"

using namespace std;

int main( int argc, char* args[] )
{
  BlinkLED LEDLight("17");

  //Get user input
  int nCubes = 1;
  if(argc > 1)
    {
      nCubes = atoi(args[1]);
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
      cubes.push_back(FlyingCube(screen, &LEDLight));
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
    LEDLight.update(ftime);

    //Update screem
    SDL_Flip( screen );

    SDL_Delay( 10 );
  }

  //Turn off and unexport gpio
  LEDLight.finish();

  //Quit SDL
  SDL_Quit();

  return 0;
}
