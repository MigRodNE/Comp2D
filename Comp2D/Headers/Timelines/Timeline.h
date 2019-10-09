/* Timeline.h -- 'Comp2D' Game Engine 'Timeline' class header file
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

#ifndef Comp2D_HEADERS_TIMELINES_TIMELINE_H_
#define Comp2D_HEADERS_TIMELINES_TIMELINE_H_

#include <string>

#include <SDL.h>

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Timelines/TimelineEvent.h"

namespace Comp2D
{
	namespace Timelines
	{
		class Timeline
		{
		protected:
			bool m_looping;
			bool m_paused;
			bool m_playing;
			bool m_started;

			unsigned int m_timelineEventCount;

			int m_currentTimelineEventIndex;
			int m_lastTimelineEventIndex;

			Uint32 m_nextEventTimeSinceSDLInitializationInMilliseconds;
			Uint32 m_timeSinceSDLInitializationInMillisecondsOnPaused;
			Uint32 m_timeSinceSDLInitializationInMillisecondsOnStarted;

			std::string m_name;

			TimelineEvent* m_timelineEvents;

			/*
			Timeline
			(
				//const std::string& name,
				unsigned int timelineEventCount = 1,
				bool looping = false
			);
			*/

			void advanceToNextTimelineEvent();
			void setCurrentTimelineEvent( int timelineEventIndex );

		public:
			Timeline
			(
				//const std::string& name,
				unsigned int timelineEventCount = 1,
				bool looping = false
			);

			virtual ~Timeline();

			void pause();
			void setLooping( bool looping );
			void start( Comp2D::Objects::GameObject* timelinesControllerComponentGameObject, int startingTimelineEventIndex = 0 );
			void stop();
			void unpause();
			void update( Uint32 currentTime, Comp2D::Objects::GameObject* timelinesControllerComponentGameObject );

			bool hasStarted() const;
			bool isLooping() const;
			bool isPaused() const;
			bool isPlaying() const;

			unsigned int getTimelineEventCount() const;

			int getCurrentTimelineEventIndex() const;
			int getLastTimelineEventIndex() const;

			Uint32 getNextEventTimeSinceSDLInitializationInMilliseconds() const;
			Uint32 getTimeSinceSDLInitializationInMillisecondsOnPaused() const;
			Uint32 getTimeSinceSDLInitializationInMillisecondsOnStarted() const;

			const std::string& getName() const;

			const TimelineEvent& getCurrentTimelineEvent() const;
		};
	}
}

#endif /* Comp2D_HEADERS_TIMELINES_TIMELINE_H_ */
