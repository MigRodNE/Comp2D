/* GameInput.h -- 'Comp2D' Game Engine 'GameInput' class header file
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

#ifndef Comp2D_HEADERS_INPUTS_GAMEINPUT_H_
#define Comp2D_HEADERS_INPUTS_GAMEINPUT_H_

#include <vector>

#include "Comp2D/Headers/Inputs/Input.h"

// TODO: (BUG) Caso em que um dos inputs está pressionado e outro está Down ou UP
//		 - considerar usar dois for loops encadeados ou separados

namespace Comp2D
{
	namespace Inputs
	{
		enum class EGameInputNames
		{
			Cancel,
			Submit,
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			Fire,
			Reset,
			N_EGameInputNames
		};

		class GameInput
		{
		private:
			EGameInputNames m_gameInputName;

			std::vector<Input*> m_inputs;

		public:
			GameInput( EGameInputNames gameInputName, std::vector<Input*> inputs );
			~GameInput();

			EGameInputNames getGameInputName() const;

			bool isGameInputDown() const;
			bool isGameInputPressed() const;
			bool isGameInputHeld() const;
			bool isGameInputUp() const;

			//float getGameInputAxisValue() const;
		};
	}
}

#endif /* Comp2D_HEADERS_INPUTS_GAMEINPUT_H_ */
