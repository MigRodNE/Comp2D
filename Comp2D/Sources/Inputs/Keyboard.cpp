/* Keyboard.cpp -- 'Comp2D' Game Engine 'Keyboard' class source file
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

#include "Comp2D/Headers/Inputs/Keyboard.h"

#include <SDL.h>

Uint8 Comp2D::Inputs::Keyboard::previousKeyboardState[Comp2D::Inputs::Keyboard::KEYBOARD_NUM_KEYS];
Uint8 Comp2D::Inputs::Keyboard::keyboardState[Comp2D::Inputs::Keyboard::KEYBOARD_NUM_KEYS];

void Comp2D::Inputs::Keyboard::updateKeyboardState()
{
	const Uint8* currentKeyboardState = SDL_GetKeyboardState( nullptr );

	for( int i = 0; i < KEYBOARD_NUM_KEYS; ++i )
	{
		previousKeyboardState[i] = keyboardState[i];
		keyboardState[i] = currentKeyboardState[i];
	}
}

bool Comp2D::Inputs::Keyboard::isKeyDown( int keyScancode )
{
	bool keyPreviousState = static_cast<bool>( previousKeyboardState[keyScancode] );
	bool keyState = static_cast<bool>( keyboardState[keyScancode] );

	return !keyPreviousState && keyState;
}

bool Comp2D::Inputs::Keyboard::isKeyPressed( int keyScancode )
{
	return static_cast<bool>( keyboardState[keyScancode] );
}

bool Comp2D::Inputs::Keyboard::isKeyHeld( int keyScancode )
{
	bool keyPreviousState = static_cast<bool>( previousKeyboardState[keyScancode] );
	bool keyState = static_cast<bool>( keyboardState[keyScancode] );

	return keyPreviousState && keyState;
}

bool Comp2D::Inputs::Keyboard::isKeyUp( int keyScancode )
{
	bool keyPreviousState = static_cast<bool>( previousKeyboardState[keyScancode] );
	bool keyState = static_cast<bool>( keyboardState[keyScancode] );

	return keyPreviousState && !keyState;
}
