/* Timeline.cpp -- 'Comp2D' Game Engine 'Timeline' class source file
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

#include "Comp2D/Headers/Timelines/Timeline.h"

#include <string>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Timelines/TimelineEvent.h"
#include "Comp2D/Headers/Time/TimeManager.h"

Comp2D::Timelines::Timeline::Timeline
(
	//const std::string& name,
	unsigned int timelineEventCount,
	bool looping
)
	:
	m_looping( looping ),
	m_paused( false ),
	m_playing( false ),
	m_started( false ),
	m_timelineEventCount( timelineEventCount ),
	m_nextEventTimeSinceSDLInitializationInMilliseconds( 0 ),
	m_timeSinceSDLInitializationInMillisecondsOnPaused( 0 ),
	m_timeSinceSDLInitializationInMillisecondsOnStarted( 0 )/*,
	m_name( name )*/
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s Constructor body Start\n", m_name.c_str() );
	#endif

	m_timelineEvents = new TimelineEvent[m_timelineEventCount];

	m_lastTimelineEventIndex = m_timelineEventCount - 1;

	setCurrentTimelineEvent( 0 );

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Timelines::Timeline::~Timeline()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s Destroying\n", m_name.c_str() );
	#endif

	delete[] m_timelineEvents;

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s Destroyed\n", m_name.c_str() );
	#endif
}

void Comp2D::Timelines::Timeline::advanceToNextTimelineEvent()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s advanceToNextTimelineEvent\n", m_name.c_str() );
	#endif

	++m_currentTimelineEventIndex;
}

void Comp2D::Timelines::Timeline::setCurrentTimelineEvent( int timelineEventIndex )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s setCurrentTimelineEvent: timelineEventIndex = %i\n", m_name.c_str(), timelineEventIndex );
	#endif

	m_currentTimelineEventIndex = timelineEventIndex;
}

void Comp2D::Timelines::Timeline::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s pause\n", m_name.c_str() );
	#endif

	if( isPlaying() )
	{
		m_paused = true;
		m_playing = false;

		m_timeSinceSDLInitializationInMillisecondsOnPaused = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();
	}
}

void Comp2D::Timelines::Timeline::setLooping( bool looping )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s setLooping: looping = %i\n", m_name.c_str(), looping );
	#endif

	m_looping = looping;
}

void Comp2D::Timelines::Timeline::start( Comp2D::Objects::GameObject* timelinesControllerComponentGameObject, int startingTimelineEventIndex )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s start: startingTimelineEventIndex = %i\n", m_name.c_str(), startingTimelineEventIndex );
	#endif

	m_paused = false;
	m_playing = true;
	m_started = true;

	setCurrentTimelineEvent( startingTimelineEventIndex );

	m_timelineEvents[m_currentTimelineEventIndex].callTimelineEventProcedure( timelinesControllerComponentGameObject );

	m_timeSinceSDLInitializationInMillisecondsOnStarted = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

	m_nextEventTimeSinceSDLInitializationInMilliseconds = getTimeSinceSDLInitializationInMillisecondsOnStarted() +
														  getCurrentTimelineEvent().getDurationInMilliseconds();
}

void Comp2D::Timelines::Timeline::stop()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s stop\n", m_name.c_str() );
	#endif

	m_paused = false;
	m_playing = false;
	m_started = false;
}

void Comp2D::Timelines::Timeline::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s unpause\n", m_name.c_str() );
	#endif

	if( hasStarted() && isPaused() )
	{
		m_paused = false;
		m_playing = true;

		Uint32 timeLeftToNextEventInMilliseconds = getNextEventTimeSinceSDLInitializationInMilliseconds() -
												   getTimeSinceSDLInitializationInMillisecondsOnPaused();

		m_nextEventTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() +
															  timeLeftToNextEventInMilliseconds;
	}
}

void Comp2D::Timelines::Timeline::update( Uint32 currentTime, Comp2D::Objects::GameObject* timelinesControllerComponentGameObject )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s update: currentTime = %u; timelinesControllerComponentGameObject with ID %u\n", m_name.c_str(), currentTime, timelinesControllerComponentGameObject->getID() );
	#endif

	if
	(
		isPlaying() &&
		SDL_TICKS_PASSED( currentTime, getNextEventTimeSinceSDLInitializationInMilliseconds() )
	)
	{
		if( getCurrentTimelineEventIndex() < getLastTimelineEventIndex() )
		{
			advanceToNextTimelineEvent();

			m_nextEventTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() +
																  getCurrentTimelineEvent().getDurationInMilliseconds();
		}
		else if( isLooping() )
		{
			setCurrentTimelineEvent( 0 );

			m_timeSinceSDLInitializationInMillisecondsOnStarted = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

			m_nextEventTimeSinceSDLInitializationInMilliseconds = getTimeSinceSDLInitializationInMillisecondsOnStarted() +
																  getCurrentTimelineEvent().getDurationInMilliseconds();
		}
		else
		{
			stop();
		}

		m_timelineEvents[m_currentTimelineEventIndex].callTimelineEventProcedure( timelinesControllerComponentGameObject );
	}
}

bool Comp2D::Timelines::Timeline::hasStarted() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s hasStarted\n", m_name.c_str() );
	#endif

	return m_started;
}

bool Comp2D::Timelines::Timeline::isLooping() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s isLooping\n", m_name.c_str() );
	#endif

	return m_looping;
}

bool Comp2D::Timelines::Timeline::isPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s isPaused\n", m_name.c_str() );
	#endif

	return m_paused;
}

bool Comp2D::Timelines::Timeline::isPlaying() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s isPlaying\n", m_name.c_str() );
	#endif

	return m_playing;
}

unsigned int Comp2D::Timelines::Timeline::getTimelineEventCount() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getTimelineEventCount\n", m_name.c_str() );
	#endif

	return m_timelineEventCount;
}

int Comp2D::Timelines::Timeline::getCurrentTimelineEventIndex() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getCurrentTimelineEventIndex\n", m_name.c_str() );
	#endif

	return m_currentTimelineEventIndex;
}

int Comp2D::Timelines::Timeline::getLastTimelineEventIndex() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getLastTimelineEventIndex\n", m_name.c_str() );
	#endif

	return m_lastTimelineEventIndex;
}

Uint32 Comp2D::Timelines::Timeline::getNextEventTimeSinceSDLInitializationInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getNextEventTimeSinceSDLInitializationInMilliseconds\n", m_name.c_str() );
	#endif

	return m_nextEventTimeSinceSDLInitializationInMilliseconds;
}

Uint32 Comp2D::Timelines::Timeline::getTimeSinceSDLInitializationInMillisecondsOnPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getTimeSinceSDLInitializationInMillisecondsOnPaused\n", m_name.c_str() );
	#endif

	return m_timeSinceSDLInitializationInMillisecondsOnPaused;
}

Uint32 Comp2D::Timelines::Timeline::getTimeSinceSDLInitializationInMillisecondsOnStarted() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getTimeSinceSDLInitializationInMillisecondsOnStarted\n", m_name.c_str() );
	#endif

	return m_timeSinceSDLInitializationInMillisecondsOnStarted;
}

const std::string& Comp2D::Timelines::Timeline::getName() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getName\n", m_name.c_str() );
	#endif

	return m_name;
}

const Comp2D::Timelines::TimelineEvent& Comp2D::Timelines::Timeline::getCurrentTimelineEvent() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Timeline named %s getCurrentTimelineEvent\n", m_name.c_str() );
	#endif

	return m_timelineEvents[m_currentTimelineEventIndex];
}
