/* GameInputs.cpp -- 'Comp2D' Game Engine 'GameInputs' class source file
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

#include "Comp2D/Headers/Inputs/GameInputs.h"

#include <vector>

#include <SDL.h>

#include "Comp2D/Headers/Inputs/GameInput.h"
#include "Comp2D/Headers/Inputs/Keyboard.h"
#include "Comp2D/Headers/Inputs/KeyboardInput.h"
#include "Comp2D/Headers/Inputs/Mouse.h"
#include "Comp2D/Headers/Inputs/MouseInput.h"

std::vector<Comp2D::Inputs::GameInput*> Comp2D::Inputs::GameInputs::gameInputs;

void Comp2D::Inputs::GameInputs::initializeGameInputs()
{
	// ADD GAME INPUTS HERE IN THE SAME ORDER THEY APPEAR ON THE ENUMERATION
	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::Cancel,
			{
				new KeyboardInput( SDL_SCANCODE_ESCAPE )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::Submit,
			{
				new KeyboardInput( SDL_SCANCODE_RETURN )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::MoveLeft,
			{
				new KeyboardInput( SDL_SCANCODE_LEFT ),
				new KeyboardInput( SDL_SCANCODE_A )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::MoveRight,
			{
				new KeyboardInput( SDL_SCANCODE_RIGHT ),
				new KeyboardInput( SDL_SCANCODE_D )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::MoveUp,
			{
				new KeyboardInput( SDL_SCANCODE_UP ),
				new KeyboardInput( SDL_SCANCODE_W )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::MoveDown,
			{
				new KeyboardInput( SDL_SCANCODE_DOWN ),
				new KeyboardInput( SDL_SCANCODE_S )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::Fire,
			{
				new KeyboardInput( SDL_SCANCODE_SPACE ),
				new MouseInput( SDL_BUTTON_LEFT )
			}
		)
	);

	gameInputs.push_back
	(
		new GameInput
		(
			EGameInputNames::Reset,
			{
				new KeyboardInput( SDL_SCANCODE_R )
			}
		)
	);
}

void Comp2D::Inputs::GameInputs::updateInputDevicesStates()
{
	Comp2D::Inputs::Keyboard::updateKeyboardState();
	Comp2D::Inputs::Mouse::updateMouseState();
}

void Comp2D::Inputs::GameInputs::finalizeGameInputs()
{
	for( unsigned int i = 0; i < gameInputs.size(); ++i )
	{
		if( gameInputs[i] )
		{
			delete gameInputs[i];
			gameInputs[i] = nullptr;
		}
	}

	gameInputs.clear();
}

bool Comp2D::Inputs::GameInputs::isGameInputDown( EGameInputNames gameInputName )
{
	return gameInputs[ static_cast<int>( gameInputName ) ]->isGameInputDown();
}

bool Comp2D::Inputs::GameInputs::isGameInputPressed( EGameInputNames gameInputName )
{
	return gameInputs[ static_cast<int>( gameInputName ) ]->isGameInputPressed();
}

bool Comp2D::Inputs::GameInputs::isGameInputHeld( EGameInputNames gameInputName )
{
	return gameInputs[ static_cast<int>( gameInputName ) ]->isGameInputHeld();
}

bool Comp2D::Inputs::GameInputs::isGameInputUp( EGameInputNames gameInputName )
{
	return gameInputs[ static_cast<int>( gameInputName ) ]->isGameInputUp();
}
