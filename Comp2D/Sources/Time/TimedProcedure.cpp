/* TimedProcedure.cpp -- 'Comp2D' Game Engine 'TimedProcedure' class source file
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

#include "Comp2D/Headers/Time/TimedProcedure.h"

#include <functional>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Time/TimeManager.h"

Comp2D::Time::TimedProcedure::TimedProcedure
(
	unsigned int id,
	std::function<void()> timedProcedure,
	Uint32 callbackTimeInMilliseconds,
	bool pausable
	/*bool useTimeScale,
	bool useDeltaTime*/
)
	:
	m_pausable( pausable ),
	m_paused( false ),
	/*m_useTimeScale( useTimeScale ),
	m_useDeltaTime( useDeltaTime ),*/
	m_id( id ),
	m_callbackTimeInMilliseconds( callbackTimeInMilliseconds ),
	m_timeSinceSDLInitializationInMillisecondsOnPaused( 0 ),
	m_timedProcedure( timedProcedure )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u Constructor body Start\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u Constructor body End\n", m_id );
	#endif
}

Comp2D::Time::TimedProcedure::~TimedProcedure()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u Destroying\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u Destroyed\n", m_id );
	#endif
}

bool Comp2D::Time::TimedProcedure::operator==( const TimedProcedure& rhs ) const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u operator==: rhs with ID %u\n", m_id, rhs.m_id );
	#endif

	return m_id == rhs.m_id;
}

bool Comp2D::Time::TimedProcedure::operator!=( const TimedProcedure& rhs ) const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u operator!=: rhs with ID %u\n", m_id, rhs.m_id );
	#endif

	return !(*this == rhs);
}

void Comp2D::Time::TimedProcedure::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u pause\n", m_id );
	#endif

	//if( !isPaused() )
	//{
		m_timeSinceSDLInitializationInMillisecondsOnPaused = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();
		m_paused = true;
	//}
}

void Comp2D::Time::TimedProcedure::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u unpause\n", m_id );
	#endif

	//if( isPaused() )
	//{
		Uint32 timeLeftToCallbackInMilliseconds = m_callbackTimeInMilliseconds - m_timeSinceSDLInitializationInMillisecondsOnPaused;
		m_callbackTimeInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() +
									   timeLeftToCallbackInMilliseconds;
		m_paused = false;
	//}
}

bool Comp2D::Time::TimedProcedure::isPausable() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u isPausable\n", m_id );
	#endif

	return m_pausable;
}

bool Comp2D::Time::TimedProcedure::isPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u isPaused\n", m_id );
	#endif

	return m_paused;
}

bool Comp2D::Time::TimedProcedure::checkCallbackTime( Uint32 currentTime )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u checkCallbackTime: currentTime = %u\n", m_id, currentTime );
	#endif

	if( !isPaused() && SDL_TICKS_PASSED( currentTime, getCallbackTimeInMilliseconds() ) )
	{
		m_timedProcedure();

		return true;
	}

	return false;
}

unsigned int Comp2D::Time::TimedProcedure::getID() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u getID\n", m_id );
	#endif

	return m_id;
}

Uint32 Comp2D::Time::TimedProcedure::getCallbackTimeInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u getCallbackTimeInMilliseconds\n", m_id );
	#endif

	return m_callbackTimeInMilliseconds;
}

Uint32 Comp2D::Time::TimedProcedure::getTimeSinceSDLInitializationInMillisecondsOnPaused()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u getTimeSinceSDLInitializationInMillisecondsOnPaused\n", m_id );
	#endif

	return m_timeSinceSDLInitializationInMillisecondsOnPaused;
}

float Comp2D::Time::TimedProcedure::getCallbackTimeInSeconds()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u getCallbackTimeInSeconds\n", m_id );
	#endif

	return static_cast<float>( getCallbackTimeInMilliseconds() ) / 1000.0f;
}

float Comp2D::Time::TimedProcedure::getTimeSinceSDLInitializationInSecondsOnPaused()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimedProcedure with ID %u getTimeSinceSDLInitializationInSecondsOnPaused\n", m_id );
	#endif

	return static_cast<float>( getTimeSinceSDLInitializationInMillisecondsOnPaused() ) / 1000.0f;
}
