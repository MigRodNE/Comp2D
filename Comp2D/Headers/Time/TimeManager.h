/* TimeManager.h -- 'Comp2D' Game Engine 'TimeManager' class header file
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

#ifndef Comp2D_HEADERS_TIME_TIMEMANAGER_H_
#define Comp2D_HEADERS_TIME_TIMEMANAGER_H_

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/States/GameState.h"
#include "Comp2D/Headers/Time/Timer.h"

namespace Comp2D
{
	namespace Time
	{
		class TimeManager
		{
		private:
			Uint32 m_currentStateInitializedTime;
			Uint32 m_deltaTimeInMilliseconds;
			Uint32 m_scaledDeltaTimeInMilliseconds;

			float m_deltaTimeInSeconds;
			float m_scaledDeltaTimeInSeconds;
			float m_timeScale;

			Comp2D::Time::Timer pausableTimeSinceSDLInitializationTimer;
			Comp2D::Time::Timer pausableTimeSinceStateInitializedTimer;

			void pause();
			void setCurrentStateInitializedTime( Uint32 currentStateInitializedTime );
			void setDeltaTime( Uint32 deltaTime );
			void unpause();

		public:
			TimeManager();

			~TimeManager();

			void setTimeScale( float timeScale );

			Uint32 getDeltaTimeInMilliseconds();
			Uint32 getPausableTimeSinceSDLInitializationInMilliseconds();
			Uint32 getPausableTimeSinceStateInitializedInMilliseconds();
			Uint32 getScaledDeltaTimeInMilliseconds();
			Uint32 getTimeSinceSDLInitializationInMilliseconds();
			Uint32 getTimeSinceStateInitializedInMilliseconds();

			float getDeltaTimeInSeconds();
			float getPausableTimeSinceSDLInitializationInSeconds();
			float getPausableTimeSinceStateInitializedInSeconds();
			float getScaledDeltaTimeInSeconds();
			float getTimeScale();
			float getTimeSinceSDLInitializationInSeconds();
			float getTimeSinceStateInitializedInSeconds();

			friend class Comp2D::Game;
			friend class Comp2D::States::GameState;
		};
	}
}

#endif /* Comp2D_HEADERS_TIME_TIMEMANAGER_H_ */
