/* AnimationKeyframe.h -- 'Comp2D' Game Engine 'AnimationKeyframe' class header file
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

#ifndef Comp2D_HEADERS_ANIMATIONS_ANIMATIONKEYFRAME_H_
#define Comp2D_HEADERS_ANIMATIONS_ANIMATIONKEYFRAME_H_

#include <SDL.h>

namespace Comp2D
{
	namespace Animations
	{
		class AnimationKeyframe
		{
		private:
			Uint32 m_durationInMilliseconds;

			SDL_Rect m_spriteRect;

		public:
			AnimationKeyframe
			(
				SDL_Rect spriteRect = { 0, 0, 0, 0 },
				Uint32 durationInMilliseconds = 200
			);

			~AnimationKeyframe();

			void setDurationInMilliseconds( Uint32 durationInMilliseconds );
			void setSpriteRect( int x, int y, int w, int h );

			Uint32 getDurationInMilliseconds() const;

			const SDL_Rect& getSpriteRect() const;
		};
	}
}

#endif /* Comp2D_HEADERS_ANIMATIONS_ANIMATIONKEYFRAME_H_ */
