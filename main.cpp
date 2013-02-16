#include <stdio.h>
#include <list>
#include <cstdlib>

#include "SDL/SDL.h"
#include "FlyingCube.h"
#include "GPIOClass.h"

using namespace std;

int main( int argc, char* args[] )
{
  //Setup GPIO
  GPIOClass* gpio17 = new GPIOClass("17");
  gpio17->export_gpio();
  gpio17->setdir_gpio("out");

  //Get user input
  int nCubes = 1;
  if(argc > 1)
    {
      nCubes = atoi(args[1]);
    }

  SDL_Surface* screen = NULL;

  srand(static_cast<unsigned>(time(0)));

  //Start SDL
  SDL_Init( SDL_INIT_VIDEO );

  const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
  int systemX = videoInfo->current_w;
  int systemY = videoInfo->current_h;
  Uint8 bpp = videoInfo->vfmt->BitsPerPixel;

  //Set up screen
  screen = SDL_SetVideoMode(systemX, systemY, bpp, SDL_SWSURFACE);

  if(!screen)
    {
      printf( "SDL_SetVideoMode fialed:( \n" );
      return 0;
    }

  list<FlyingCube> cubes;
  for(int i = 0; i < nCubes; i++)
    {
      cubes.push_back(FlyingCube(screen, gpio17));
    }

  bool isRunning = true;
  SDL_Event event;

  while( isRunning){

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
	it->update();
	it->draw();
      }

    //Update screem
    SDL_Flip( screen );

    SDL_Delay( 10 );
  }

  //Unexport gpio
  gpio17->unexport_gpio();

  //Quit SDL
  SDL_Quit();

  return 0;
}
