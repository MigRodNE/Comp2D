/* Mouse.cpp -- 'Comp2D' Game Engine 'Mouse' class source file
  version 1.0.0, October 9th, 2019

  Copyright (C) 2018-2019 Miguel Rodrigo Auto Gomes

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	 claim that you wrote the original software. If you use this software
	 in a product, an acknowledgment in the product documentation would be
	 appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	 misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Miguel Rodrigo Auto Gomes
  migrodne@gmail.com

*/

#include "Comp2D/Headers/Inputs/Mouse.h"

#include <SDL.h>

int Comp2D::Inputs::Mouse::mouseX = 0;
int Comp2D::Inputs::Mouse::mouseY = 0;

Uint32 Comp2D::Inputs::Mouse::previousMouseState = 0;
Uint32 Comp2D::Inputs::Mouse::mouseState = 0;

void Comp2D::Inputs::Mouse::updateMouseState()
{
	Uint32 currentMouseState = SDL_GetMouseState( &mouseX, &mouseY );

	previousMouseState = mouseState;
	mouseState = currentMouseState;
}

bool Comp2D::Inputs::Mouse::isMouseButtonDown( int mouseButtonValue )
{
	bool mouseButtonPreviousState = static_cast<bool>( previousMouseState & SDL_BUTTON( mouseButtonValue ) );
	bool mouseButtonState = static_cast<bool>( mouseState & SDL_BUTTON( mouseButtonValue ) );

	return !mouseButtonPreviousState && mouseButtonState;
}

bool Comp2D::Inputs::Mouse::isMouseButtonPressed( int mouseButtonValue )
{
	return static_cast<bool>( mouseState & SDL_BUTTON( mouseButtonValue ) );
}

bool Comp2D::Inputs::Mouse::isMouseButtonHeld( int mouseButtonValue )
{
	bool mouseButtonPreviousState = static_cast<bool>( previousMouseState & SDL_BUTTON( mouseButtonValue ) );
	bool mouseButtonState = static_cast<bool>( mouseState & SDL_BUTTON( mouseButtonValue ) );

	return mouseButtonPreviousState && mouseButtonState;
}

bool Comp2D::Inputs::Mouse::isMouseButtonUp( int mouseButtonValue )
{
	bool mouseButtonPreviousState = static_cast<bool>( previousMouseState & SDL_BUTTON( mouseButtonValue ) );
	bool mouseButtonState = static_cast<bool>( mouseState & SDL_BUTTON( mouseButtonValue ) );

	return mouseButtonPreviousState && !mouseButtonState;
}

int Comp2D::Inputs::Mouse::getMouseX()
{
	return mouseX;
}

int Comp2D::Inputs::Mouse::getMouseY()
{
	return mouseY;
}
