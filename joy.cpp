#include "SDL.h"
#include <cstdio>


int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO	| SDL_INIT_JOYSTICK);

	SDL_Surface *video = SDL_SetVideoMode(640,480,0,SDL_SWSURFACE);

	SDL_Joystick *joy;

// Check for joystick
if(SDL_NumJoysticks()<1)
{
	printf("No joysticks availables, quiting");
	SDL_Quit();
	return 1;
}
  // Open joystick
  joy=SDL_JoystickOpen(0);
  
  if(joy)
  {
    printf("Opened Joystick 0\n");
    printf("Name: %s\n", SDL_JoystickName(0));
    printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
    printf("Number of Hats: %d\n", SDL_JoystickNumHats(joy));
    printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
    printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
  }
  else
    printf("Couldn't open Joystick 0\n");

	SDL_Event e;
	while ( SDL_WaitEvent(&e) )
	{
	if ( e.type == SDL_JOYBUTTONDOWN )
	{
		printf("Pressed button %d\n", e.jbutton.button);
	}
	else if ( e.type == SDL_JOYBUTTONUP )
	{
		printf("Released button %d\n", e.jbutton.button);
	}
	else if ( e.type == SDL_JOYHATMOTION )
	{
		printf("Hat %d is ", e.jhat.hat);
		if ( e.jhat.value & SDL_HAT_CENTERED ) puts(" centered ");
		if ( e.jhat.value & SDL_HAT_UP ) puts(" up ");
		if ( e.jhat.value & SDL_HAT_RIGHT ) puts(" right ");
		if ( e.jhat.value & SDL_HAT_DOWN ) puts(" down ");
		if ( e.jhat.value & SDL_HAT_LEFT ) puts(" left ");
		puts("\n");
	}
	else if ( e.type == SDL_JOYAXISMOTION )
	{
		printf("Axis %d is %d\n", e.jaxis.axis, e.jaxis.value);
	}
	else if ( e.type == SDL_QUIT )
	{
		break;
	}

	}

  if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);

	SDL_Quit();
	return 0;
}

