/* AnimationKeyframe.cpp -- 'Comp2D' Game Engine 'AnimationKeyframe' class source file
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

#include "Comp2D/Headers/Animations/AnimationKeyframe.h"

#include <SDL.h>

Comp2D::Animations::AnimationKeyframe::AnimationKeyframe
(
	SDL_Rect spriteRect,
	Uint32 durationInMilliseconds
)
	:
	m_durationInMilliseconds( durationInMilliseconds ),
	m_spriteRect( spriteRect )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationKeyframe spriteRect: ( x = %i, y = %i, w = %i, h = %i )\n",
			spriteRect.x,
			spriteRect.y,
			spriteRect.w,
			spriteRect.h
		);
		*/
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe durationInMilliseconds = %u\n", durationInMilliseconds );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe Constructor body End\n" );
	#endif
}

Comp2D::Animations::AnimationKeyframe::~AnimationKeyframe()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe Destroying\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe Destroyed\n" );
	#endif
}

void Comp2D::Animations::AnimationKeyframe::setDurationInMilliseconds( Uint32 durationInMilliseconds )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe setDurationInMilliseconds: durationInMilliseconds = %u\n", durationInMilliseconds );
	#endif

	m_durationInMilliseconds = durationInMilliseconds;
}

void Comp2D::Animations::AnimationKeyframe::setSpriteRect( int x, int y, int w, int h )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe setSpriteRect: x = %i; y = %i; w = %i; h = %i\n", x, y, w, h );
	#endif

	m_spriteRect.x = x;
	m_spriteRect.y = y;
	m_spriteRect.w = w;
	m_spriteRect.h = h;
}

Uint32 Comp2D::Animations::AnimationKeyframe::getDurationInMilliseconds() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe getDurationInMilliseconds\n" );
	#endif

	return m_durationInMilliseconds;
}

const SDL_Rect& Comp2D::Animations::AnimationKeyframe::getSpriteRect() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationKeyframe getSpriteRect\n" );
	#endif

	return m_spriteRect;
}
