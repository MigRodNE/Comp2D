/* GameInput.cpp -- 'Comp2D' Game Engine 'GameInput' class source file
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

#include "Comp2D/Headers/Inputs/GameInput.h"

#include <vector>

#include "Comp2D/Headers/Inputs/Input.h"

Comp2D::Inputs::GameInput::GameInput( EGameInputNames gameInputName, std::vector<Input*> inputs )
	:
	m_gameInputName{ gameInputName },
	m_inputs{ inputs }
{

}

Comp2D::Inputs::GameInput::~GameInput()
{
	for( unsigned int i = 0; i < m_inputs.size(); ++i )
	{
		if( m_inputs[i] )
		{
			delete m_inputs[i];
			m_inputs[i] = nullptr;
		}
	}

	m_inputs.clear();
}

Comp2D::Inputs::EGameInputNames Comp2D::Inputs::GameInput::getGameInputName() const
{
	return m_gameInputName;
}

bool Comp2D::Inputs::GameInput::isGameInputDown() const
{
	for( unsigned int i = 0; i < m_inputs.size(); ++i )
	{
		if( m_inputs[i]->isInputDown() )
		{
			return true;
		}
	}

	return false;
}

bool Comp2D::Inputs::GameInput::isGameInputPressed() const
{
	for( unsigned int i = 0; i < m_inputs.size(); ++i )
	{
		if( m_inputs[i]->isInputPressed() )
		{
			return true;
		}
	}

	return false;
}

bool Comp2D::Inputs::GameInput::isGameInputHeld() const
{
	for( unsigned int i = 0; i < m_inputs.size(); ++i )
	{
		if( m_inputs[i]->isInputHeld() )
		{
			return true;
		}
	}

	return false;
}

bool Comp2D::Inputs::GameInput::isGameInputUp() const
{
	for( unsigned int i = 0; i < m_inputs.size(); ++i )
	{
		if( m_inputs[i]->isInputUp() )
		{
			return true;
		}
	}

	return false;
}
