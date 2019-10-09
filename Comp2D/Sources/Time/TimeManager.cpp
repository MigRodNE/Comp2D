/* TimeManager.cpp -- 'Comp2D' Game Engine 'TimeManager' class source file
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

#include "Comp2D/Headers/Time/TimeManager.h"

#include <cmath>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Time/Timer.h"

Comp2D::Time::TimeManager::TimeManager()
	:
	m_currentStateInitializedTime( 0 ),
	m_deltaTimeInMilliseconds( 0 ),
	m_scaledDeltaTimeInMilliseconds( 0 ),
	m_deltaTimeInSeconds( 0.0f ),
	m_scaledDeltaTimeInSeconds( 0.0f ),
	m_timeScale( 1.0f )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager Constructor body Start\n" );
	#endif

	pausableTimeSinceSDLInitializationTimer.start( SDL_GetTicks() );

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager Constructor body End\n" );
	#endif
}

Comp2D::Time::TimeManager::~TimeManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager Destroyed\n" );
	#endif
}

void Comp2D::Time::TimeManager::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager pause\n" );
	#endif

	pausableTimeSinceSDLInitializationTimer.pause();
	pausableTimeSinceStateInitializedTimer.pause();
}

void Comp2D::Time::TimeManager::setCurrentStateInitializedTime( Uint32 currentStateInitializedTime )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager setCurrentStateInitializedTime: currentStateInitializedTime = %u\n", currentStateInitializedTime );
	#endif

	m_currentStateInitializedTime = currentStateInitializedTime;

	pausableTimeSinceStateInitializedTimer.start( currentStateInitializedTime );

	if( Comp2D::Game::isPaused() )
	{
		pausableTimeSinceStateInitializedTimer.pause();
	}
}

void Comp2D::Time::TimeManager::setDeltaTime( Uint32 deltaTime )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager setDeltaTime: deltaTime = %u\n", deltaTime );
	#endif

	m_deltaTimeInMilliseconds = deltaTime;
	m_scaledDeltaTimeInMilliseconds = static_cast<Uint32>( round( static_cast<float>( m_deltaTimeInMilliseconds ) * m_timeScale ) );
	m_deltaTimeInSeconds = static_cast<float>( m_deltaTimeInMilliseconds ) / 1000.0f;
	m_scaledDeltaTimeInSeconds = m_deltaTimeInSeconds * m_timeScale;
}

void Comp2D::Time::TimeManager::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager unpause\n" );
	#endif

	pausableTimeSinceSDLInitializationTimer.unpause();
	pausableTimeSinceStateInitializedTimer.unpause();
}

void Comp2D::Time::TimeManager::setTimeScale( float timeScale )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager setTimeScale: timeScale = %f\n", timeScale );
	#endif

	m_timeScale = timeScale;

	m_scaledDeltaTimeInMilliseconds = static_cast<Uint32>( round( static_cast<float>( m_deltaTimeInMilliseconds ) * m_timeScale ) );
	m_scaledDeltaTimeInSeconds = m_deltaTimeInSeconds * m_timeScale;
}

Uint32 Comp2D::Time::TimeManager::getDeltaTimeInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getDeltaTimeInMilliseconds\n" );
	#endif

	return m_deltaTimeInMilliseconds;
}

Uint32 Comp2D::Time::TimeManager::getPausableTimeSinceSDLInitializationInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getPausableTimeSinceSDLInitializationInMilliseconds\n" );
	#endif

	return pausableTimeSinceSDLInitializationTimer.getElapsedTimeInMilliseconds();
}

Uint32 Comp2D::Time::TimeManager::getPausableTimeSinceStateInitializedInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getPausableTimeSinceStateInitializedInMilliseconds\n" );
	#endif

	return pausableTimeSinceStateInitializedTimer.getElapsedTimeInMilliseconds();
}

Uint32 Comp2D::Time::TimeManager::getScaledDeltaTimeInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getScaledDeltaTimeInMilliseconds\n" );
	#endif

	return m_scaledDeltaTimeInMilliseconds;
}

Uint32 Comp2D::Time::TimeManager::getTimeSinceSDLInitializationInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getTimeSinceSDLInitializationInMilliseconds\n" );
	#endif

	return SDL_GetTicks();
}

Uint32 Comp2D::Time::TimeManager::getTimeSinceStateInitializedInMilliseconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getTimeSinceStateInitializedInMilliseconds\n" );
	#endif

	return SDL_GetTicks() - m_currentStateInitializedTime;
}

float Comp2D::Time::TimeManager::getDeltaTimeInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getDeltaTimeInSeconds\n" );
	#endif

	return m_deltaTimeInSeconds;
}

float Comp2D::Time::TimeManager::getPausableTimeSinceSDLInitializationInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getPausableTimeSinceSDLInitializationInSeconds\n" );
	#endif

	return pausableTimeSinceSDLInitializationTimer.getElapsedTimeInSeconds();
}

float Comp2D::Time::TimeManager::getPausableTimeSinceStateInitializedInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getPausableTimeSinceStateInitializedInSeconds\n" );
	#endif

	return pausableTimeSinceStateInitializedTimer.getElapsedTimeInSeconds();
}

float Comp2D::Time::TimeManager::getScaledDeltaTimeInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getScaledDeltaTimeInSeconds\n" );
	#endif

	return m_scaledDeltaTimeInSeconds;
}

float Comp2D::Time::TimeManager::getTimeScale()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getTimeScale\n" );
	#endif

	return m_timeScale;
}

float Comp2D::Time::TimeManager::getTimeSinceSDLInitializationInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getTimeSinceSDLInitializationInSeconds\n" );
	#endif

	return static_cast<float>( SDL_GetTicks() ) / 1000.0f;
}

float Comp2D::Time::TimeManager::getTimeSinceStateInitializedInSeconds()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimeManager getTimeSinceStateInitializedInSeconds\n" );
	#endif

	return static_cast<float>( SDL_GetTicks() - m_currentStateInitializedTime ) / 1000.0f;
}
