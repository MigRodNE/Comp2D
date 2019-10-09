/* Animation.cpp -- 'Comp2D' Game Engine 'Animation' class source file
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

#include "Comp2D/Headers/Animations/Animation.h"

#include <string>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Animations/AnimationKeyframe.h"
#include "Comp2D/Headers/Time/TimeManager.h"

Comp2D::Animations::Animation::Animation
(
	//const std::string& name,
	unsigned int animationKeyframeCount,
	bool looping
)
	:
	m_looping( looping ),
	m_paused( false ),
	m_playing( false ),
	m_started( false ),
	m_animationKeyframeCount( animationKeyframeCount ),
	m_nextFrameTimeSinceSDLInitializationInMilliseconds( 0 ),
	m_timeSinceSDLInitializationInMillisecondsOnPaused( 0 ),
	m_timeSinceSDLInitializationInMillisecondsOnStarted( 0 )/*,
	m_name( name )*/
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s Constructor body Start\n", m_name.c_str() );
	#endif

	m_animationKeyframes = new AnimationKeyframe[m_animationKeyframeCount];

	m_lastAnimationKeyframeIndex = m_animationKeyframeCount - 1;

	setCurrentAnimationKeyframe( 0 );

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Animations::Animation::~Animation()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s Destroying\n", m_name.c_str() );
	#endif

	delete[] m_animationKeyframes;

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s Destroyed\n", m_name.c_str() );
	#endif
}

void Comp2D::Animations::Animation::advanceToNextAnimationKeyframe()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s advanceToNextAnimationKeyframe\n", m_name.c_str() );
	#endif

	++m_currentAnimationKeyframeIndex;
}

void Comp2D::Animations::Animation::setCurrentAnimationKeyframe( int animationKeyframeIndex )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s setCurrentAnimationKeyframe: animationKeyframeIndex = %i\n", m_name.c_str(), animationKeyframeIndex );
	#endif

	m_currentAnimationKeyframeIndex = animationKeyframeIndex;
}

void Comp2D::Animations::Animation::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s pause\n", m_name.c_str() );
	#endif

	if( isPlaying() )
	{
		m_paused = true;
		m_playing = false;

		m_timeSinceSDLInitializationInMillisecondsOnPaused = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();
	}
}

void Comp2D::Animations::Animation::setLooping( bool looping )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s setLooping: looping = %i\n", m_name.c_str(), looping );
	#endif

	m_looping = looping;
}

void Comp2D::Animations::Animation::start( int startingAnimationKeyframeIndex )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s start: startingAnimationKeyframeIndex = %i\n", m_name.c_str(), startingAnimationKeyframeIndex );
	#endif

	m_paused = false;
	m_playing = true;
	m_started = true;

	setCurrentAnimationKeyframe( startingAnimationKeyframeIndex );

	m_timeSinceSDLInitializationInMillisecondsOnStarted = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

	m_nextFrameTimeSinceSDLInitializationInMilliseconds = getTimeSinceSDLInitializationInMillisecondsOnStarted() +
														  getCurrentAnimationKeyframe().getDurationInMilliseconds();
}

void Comp2D::Animations::Animation::stop()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s stop\n", m_name.c_str() );
	#endif

	m_paused = false;
	m_playing = false;
	m_started = false;
}

void Comp2D::Animations::Animation::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s unpause\n", m_name.c_str() );
	#endif

	if( hasStarted() && isPaused() )
	{
		m_paused = false;
		m_playing = true;

		Uint32 timeLeftToNextFrameInMilliseconds = getNextFrameTimeSinceSDLInitializationInMilliseconds() -
												   getTimeSinceSDLInitializationInMillisecondsOnPaused();

		m_nextFrameTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() +
															  timeLeftToNextFrameInMilliseconds;
	}
}

void Comp2D::Animations::Animation::update( Uint32 currentTime )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s update: currentTime = %u\n", m_name.c_str(), currentTime );

		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s isPlaying() = %i\n", m_name.c_str(), isPlaying() );
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s SDL_TICKS_PASSED() = %i\n", m_name.c_str(), SDL_TICKS_PASSED( currentTime, getNextFrameTimeSinceSDLInitializationInMilliseconds() ) );
	#endif

	if
	(
		isPlaying() &&
		SDL_TICKS_PASSED( currentTime, getNextFrameTimeSinceSDLInitializationInMilliseconds() )
	)
	{
		if( getCurrentAnimationKeyframeIndex() < getLastAnimationKeyframeIndex() )
		{
			advanceToNextAnimationKeyframe();

			m_nextFrameTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() +
																  getCurrentAnimationKeyframe().getDurationInMilliseconds();
		}
		else if( isLooping() )
		{
			setCurrentAnimationKeyframe( 0 );

			m_timeSinceSDLInitializationInMillisecondsOnStarted = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

			m_nextFrameTimeSinceSDLInitializationInMilliseconds = getTimeSinceSDLInitializationInMillisecondsOnStarted() +
																  getCurrentAnimationKeyframe().getDurationInMilliseconds();
		}
		else
		{
			stop();
		}
	}
}

bool Comp2D::Animations::Animation::hasStarted() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s hasStarted\n", m_name.c_str() );
	#endif

	return m_started;
}

bool Comp2D::Animations::Animation::isLooping() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s isLooping\n", m_name.c_str() );
	#endif

	return m_looping;
}

bool Comp2D::Animations::Animation::isPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s isPaused\n", m_name.c_str() );
	#endif

	return m_paused;
}

bool Comp2D::Animations::Animation::isPlaying() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s isPlaying\n", m_name.c_str() );
	#endif

	return m_playing;
}

unsigned int Comp2D::Animations::Animation::getAnimationKeyframeCount() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getKeyframeCount\n", m_name.c_str() );
	#endif

	return m_animationKeyframeCount;
}

int Comp2D::Animations::Animation::getCurrentAnimationKeyframeIndex() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getCurrentAnimationKeyframeIndex\n", m_name.c_str() );
	#endif

	return m_currentAnimationKeyframeIndex;
}

int Comp2D::Animations::Animation::getLastAnimationKeyframeIndex() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getLastAnimationKeyframeIndex\n", m_name.c_str() );
	#endif

	return m_lastAnimationKeyframeIndex;
}

Uint32 Comp2D::Animations::Animation::getNextFrameTimeSinceSDLInitializationInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getNextFrameTimeSinceSDLInitializationInMilliseconds\n", m_name.c_str() );
	#endif

	return m_nextFrameTimeSinceSDLInitializationInMilliseconds;
}

Uint32 Comp2D::Animations::Animation::getTimeSinceSDLInitializationInMillisecondsOnPaused() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getTimeSinceSDLInitializationInMillisecondsOnPaused\n", m_name.c_str() );
	#endif

	return m_timeSinceSDLInitializationInMillisecondsOnPaused;
}

Uint32 Comp2D::Animations::Animation::getTimeSinceSDLInitializationInMillisecondsOnStarted() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getTimeSinceSDLInitializationInMillisecondsOnStarted\n", m_name.c_str() );
	#endif

	return m_timeSinceSDLInitializationInMillisecondsOnStarted;
}

const std::string& Comp2D::Animations::Animation::getName() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getName\n", m_name.c_str() );
	#endif

	return m_name;
}

const Comp2D::Animations::AnimationKeyframe& Comp2D::Animations::Animation::getCurrentAnimationKeyframe() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Animation named %s getCurrentAnimationKeyframe\n", m_name.c_str() );
	#endif

	return m_animationKeyframes[m_currentAnimationKeyframeIndex];
}
