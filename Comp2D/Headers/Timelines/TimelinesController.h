/* TimelinesController.h -- 'Comp2D' Game Engine 'TimelinesController' class header file
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

#ifndef Comp2D_HEADERS_TIMELINES_TIMELINESCONTROLLER_H_
#define Comp2D_HEADERS_TIMELINES_TIMELINESCONTROLLER_H_

#include <list>
#include <string>
#include <vector>

#include <SDL.h>

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Timelines/Timeline.h"

// TODO: Realizar binary search no método setCurrentTimeline e overloads

namespace Comp2D
{
	namespace Timelines
	{
		class TimelinesController
		{
		protected:
			int m_currentTimelineIndex;

			std::vector<std::string> m_timelinesResourcesNames;

			Timeline* m_currentTimeline;

		public:
			TimelinesController( int startingTimelineIndex = 0 );

			virtual ~TimelinesController();

			void setCurrentTimeline( int timelineIndex );
			void setCurrentTimeline( const std::string& timelineResourceName );
			void setCurrentTimeline( const Comp2D::Timelines::Timeline& timeline );
			void update( Uint32 currentTime, Comp2D::Objects::GameObject* timelinesControllerComponentGameObject );

			int getCurrentTimelineIndex() const;

			std::list<Comp2D::Timelines::Timeline> getTimelines() const;

			Comp2D::Timelines::Timeline* getCurrentTimeline() const;

			const std::vector<std::string>& getTimelinesResourcesNames() const;
		};
	}
}

#endif /* Comp2D_HEADERS_TIMELINES_TIMELINESCONTROLLER_H_ */
