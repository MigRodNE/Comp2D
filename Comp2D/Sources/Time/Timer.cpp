/* Timer.cpp -- 'Comp2D' Game Engine 'Timer' class source file
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

#include "Comp2D/Headers/Time/Timer.h"

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Time/TimeManager.h"

Comp2D::Time::Timer::Timer( Uint32 timeOnStartInMilliseconds )
	:
	m_paused( false ),
	m_started( false ),
	m_timeOnPausedInMilliseconds( 0 ),
    m_timeOnStartInMilliseconds( timeOnStartInMilliseconds ),
	m_timeOnPausedInSeconds( 0.0f ),
	m_timeOnStartInSeconds( static_cast<float>( timeOnStartInMilliseconds ) / 1000.0f )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer Constructor body End\n" );
	#endif
}

Comp2D::Time::Timer::~Timer()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer Destroying\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer Destroyed\n" );
	#endif
}

void Comp2D::Time::Timer::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer pause\n" );
	#endif

    if( m_started && !m_paused )
    {
    	m_timeOnPausedInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() - m_timeOnStartInMilliseconds;
    	m_timeOnPausedInSeconds = static_cast<float>( m_timeOnPausedInMilliseconds ) / 1000.0f;

        m_paused = true;

        m_timeOnStartInMilliseconds = 0;
        m_timeOnStartInSeconds = 0.0f;
    }
}

void Comp2D::Time::Timer::setTimeOnStart( Uint32 timeOnStartInMilliseconds )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer setTimeOnStart: timeOnStartInMilliseconds = %u\n", timeOnStartInMilliseconds );
	#endif

	m_timeOnStartInMilliseconds = timeOnStartInMilliseconds;
	m_timeOnStartInSeconds = static_cast<float>( m_timeOnStartInMilliseconds ) / 1000.0f;
}

void Comp2D::Time::Timer::start()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer start\n" );
	#endif

	start( Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() );
}

void Comp2D::Time::Timer::start( Uint32 timeOnStartInMilliseconds )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer start: timeOnStartInMilliseconds = %u\n", timeOnStartInMilliseconds );
	#endif

	m_paused = false;
	m_started = true;

	m_timeOnPausedInMilliseconds = 0;
	m_timeOnPausedInSeconds = 0.0f;
	setTimeOnStart( timeOnStartInMilliseconds );
}

void Comp2D::Time::Timer::stop()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer stop\n" );
	#endif

    m_paused = false;
    m_started = false;

    m_timeOnPausedInMilliseconds = 0;
    m_timeOnPausedInSeconds = 0.0f;
	m_timeOnStartInMilliseconds = 0;
	m_timeOnStartInSeconds = 0.0f;
}

void Comp2D::Time::Timer::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer unpause\n" );
	#endif

    if( m_started && m_paused )
    {
        m_paused = false;

        m_timeOnStartInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() - m_timeOnPausedInMilliseconds;
        m_timeOnStartInSeconds = static_cast<float>( m_timeOnStartInMilliseconds ) / 1000.0f;

        m_timeOnPausedInMilliseconds = 0;
        m_timeOnPausedInSeconds = 0.0f;
    }
}

bool Comp2D::Time::Timer::hasStarted() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer isStarted\n" );
	#endif

    return m_started;
}

bool Comp2D::Time::Timer::isPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer isPaused\n" );
	#endif

    return m_paused && m_started;
}

Uint32 Comp2D::Time::Timer::getElapsedTimeInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getElapsedTimeInMilliseconds\n" );
	#endif

    Uint32 elapsedTime = 0;

    if( m_started )
    {
        if( m_paused )
        {
            elapsedTime = m_timeOnPausedInMilliseconds;
        }
        else
        {
            elapsedTime = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() - m_timeOnStartInMilliseconds;
        }
    }

    return elapsedTime;
}

Uint32 Comp2D::Time::Timer::getTimeOnPausedInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getTimeOnPausedInMilliseconds\n" );
	#endif

	return m_timeOnPausedInMilliseconds;
}

Uint32 Comp2D::Time::Timer::getTimeOnStartInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getTimeOnStartInMilliseconds\n" );
	#endif

	return m_timeOnStartInMilliseconds;
}

float Comp2D::Time::Timer::getElapsedTimeInSeconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getElapsedTimeInSeconds\n" );
	#endif

	return static_cast<float>( getElapsedTimeInMilliseconds() ) / 1000.0f;
}

float Comp2D::Time::Timer::getTimeOnPausedInSeconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getTimeOnPausedInSeconds\n" );
	#endif

	return m_timeOnPausedInSeconds;
}

float Comp2D::Time::Timer::getTimeOnStartInSeconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timer getTimeOnStartInSeconds\n" );
	#endif

	return m_timeOnStartInSeconds;
}
