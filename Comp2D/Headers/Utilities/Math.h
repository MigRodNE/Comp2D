/* Math.h -- 'Comp2D' Game Engine Math Utilities data and functions file
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

#ifndef Comp2D_HEADERS_UTILITIES_MATH_H_
#define Comp2D_HEADERS_UTILITIES_MATH_H_

#include <cmath>

namespace Comp2D
{
	namespace Utilities
	{
		constexpr float DEGREE_IN_RAD = 0.017453293f;
		constexpr float PI = 3.14159265f;
		constexpr float RAD_IN_DEGREES = 57.295780f;

		constexpr double DEGREE_IN_RAD_D = 0.017453293; // CONSEGUIR O VALOR COMPLETO
		constexpr double PI_D = 3.1415926535897932;
		constexpr double RAD_IN_DEGREES_D = 57.295779513; // CONSEGUIR O VALOR COMPLETO

		template <typename T>
		inline auto square( const T& x )
		{
			return x * x;
		}

		template<typename T>
		inline T wrapAngle( T theta )
		{
			const T modded = fmod( theta,(T)2.0 * (T)PI_D );

			return (modded > (T)PI_D) ?
				   (modded - (T)2.0 * (T)PI_D) :
				   modded;
		}

		template<typename T>
		inline T interpolate( const T& src, const T& dst, float alpha )
		{
			return src + (dst - src) * alpha;
		}
	}
}

#endif /* Comp2D_HEADERS_UTILITIES_MATH_H_ */
