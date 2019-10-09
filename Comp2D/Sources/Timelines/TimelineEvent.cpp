/* TimelineEvent.cpp -- 'Comp2D' Game Engine 'TimelineEvent' class source file
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

#include "Comp2D/Headers/Timelines/TimelineEvent.h"

#include <functional>

#include <SDL.h>

#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Timelines::TimelineEvent::TimelineEvent
(
	std::function<void( Comp2D::Objects::GameObject*, void* )> timelineEventProcedure,
	void* timelineEventProcedureParameter,
	Uint32 durationInMilliseconds
)
	:
	m_durationInMilliseconds( durationInMilliseconds ),
	m_timelineEventProcedureParameter( timelineEventProcedureParameter ),
	m_timelineEventProcedure( timelineEventProcedure )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent timelineEventProcedure = %p\n", timelineEventProcedure );

		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent timelineEventProcedureParameter = %p\n", timelineEventProcedureParameter );

		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent durationInMilliseconds = %u\n", durationInMilliseconds );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent Constructor body End\n" );
	#endif
}

Comp2D::Timelines::TimelineEvent::~TimelineEvent()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent Destroying\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent Destroyed\n" );
	#endif
}

void Comp2D::Timelines::TimelineEvent::callTimelineEventProcedure( Comp2D::Objects::GameObject* timelinesControllerComponentGameObject )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent callTimelineEventProcedure\n" );
	#endif

	m_timelineEventProcedure( timelinesControllerComponentGameObject, m_timelineEventProcedureParameter );
}

void Comp2D::Timelines::TimelineEvent::setDurationInMilliseconds( Uint32 durationInMilliseconds )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent setDurationInMilliseconds: durationInMilliseconds = %u\n", durationInMilliseconds );
	#endif

	m_durationInMilliseconds = durationInMilliseconds;
}

void Comp2D::Timelines::TimelineEvent::setTimelineEventProcedure( std::function<void( Comp2D::Objects::GameObject*, void* )> timelineEventProcedure )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent setTimelineEventProcedure: timelineEventProcedure = %p\n", timelineEventProcedure );
	#endif

	m_timelineEventProcedure = timelineEventProcedure;
}

void Comp2D::Timelines::TimelineEvent::setTimelineEventProcedureParameter( void* timelineEventProcedureParameter )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent setTimelineEventProcedureParameter: timelineEventProcedureParameter = %p\n", timelineEventProcedureParameter );
	#endif

	m_timelineEventProcedureParameter = timelineEventProcedureParameter;
}

Uint32 Comp2D::Timelines::TimelineEvent::getDurationInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent getDurationInMilliseconds\n" );
	#endif

	return m_durationInMilliseconds;
}

const std::function<void( Comp2D::Objects::GameObject*, void* )>& Comp2D::Timelines::TimelineEvent::getTimelineEventProcedure() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TimelineEvent getTimelineEventProcedure\n" );
	#endif

	return m_timelineEventProcedure;
}
