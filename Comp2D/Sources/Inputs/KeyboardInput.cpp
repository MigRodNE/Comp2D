/* KeyboardInput.cpp -- 'Comp2D' Game Engine 'KeyboardInput' class source file
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

#include "Comp2D/Headers/Inputs/KeyboardInput.h"

#include "Comp2D/Headers/Inputs/Input.h"
#include "Comp2D/Headers/Inputs/Keyboard.h"

Comp2D::Inputs::KeyboardInput::KeyboardInput( int keyScancode )
	:
	Input(),
	m_keyScancode{ keyScancode }
{

}

Comp2D::Inputs::KeyboardInput::~KeyboardInput()
{

}

bool Comp2D::Inputs::KeyboardInput::isInputDown() const
{
	return Comp2D::Inputs::Keyboard::isKeyDown( m_keyScancode );
}

bool Comp2D::Inputs::KeyboardInput::isInputPressed() const
{
	return Comp2D::Inputs::Keyboard::isKeyPressed( m_keyScancode );
}

bool Comp2D::Inputs::KeyboardInput::isInputHeld() const
{
	return Comp2D::Inputs::Keyboard::isKeyHeld( m_keyScancode );
}

bool Comp2D::Inputs::KeyboardInput::isInputUp() const
{
	return Comp2D::Inputs::Keyboard::isKeyUp( m_keyScancode );
}
