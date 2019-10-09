/* Vector2D.h -- 'Comp2D' Game Engine 'Vector2D' class header file
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

#ifndef Comp2D_HEADERS_UTILITIES_VECTOR2D_H_
#define Comp2D_HEADERS_UTILITIES_VECTOR2D_H_

#include "Comp2D/Headers/Utilities/Math.h"

namespace Comp2D
{
	namespace Utilities
	{
		template <typename T>
		class Vector2D
		{
		public:
			T x, y;

			Vector2D() = default;

			Vector2D( T x, T y )
				:
				x( x ),
				y( y )
			{}

			Vector2D( const Vector2D& vect )
				:
				Vector2D( vect.x, vect.y )
			{}

			template <typename T2>
			explicit operator Vector2D<T2>() const
			{
				return{ (T2)x, (T2)y };
			}

			Vector2D operator-() const
			{
				return Vector2D( -x, -y );
			}

			Vector2D& operator=( const Vector2D& otherVector2D )
			{
				x = otherVector2D.x;
				y = otherVector2D.y;

				return *this;
			}

			Vector2D& operator+=( const Vector2D& otherVector2D)
			{
				x += otherVector2D.x;
				y += otherVector2D.y;

				return *this;
			}

			Vector2D& operator-=( const Vector2D& otherVector2D)
			{
				x -= otherVector2D.x;
				y -= otherVector2D.y;

				return *this;
			}

			T operator*( const Vector2D& otherVector2D ) const
			{
				return x * otherVector2D.x + y * otherVector2D.y;
			}

			Vector2D operator+( const Vector2D& otherVector2D ) const
			{
				return Vector2D( *this ) += otherVector2D;
			}

			Vector2D operator-( const Vector2D& otherVector2D ) const
			{
				return Vector2D( *this ) -= otherVector2D;
			}

			Vector2D& operator*=( const T& otherVector2D )
			{
				x *= otherVector2D;
				y *= otherVector2D;
				return *this;
			}

			Vector2D operator*( const T& otherVector2D ) const
			{
				return Vector2D( *this ) *= otherVector2D;
			}

			Vector2D& operator/=( const T& otherVector2D )
			{
				x /= otherVector2D;
				y /= otherVector2D;
				return *this;
			}

			Vector2D operator/( const T& otherVector2D ) const
			{
				return Vector2D( *this ) /= otherVector2D;
			}

			bool operator==( const Vector2D& otherVector2D ) const
			{
				return x == otherVector2D.x && y == otherVector2D.y;
			}

			bool operator!=( const Vector2D& otherVector2D ) const
			{
				return !(*this == otherVector2D);
			}

			T squaredLength() const
			{
				return square( *this );
			}

			T length() const
			{
				return sqrt( squaredLength() );
			}

			Vector2D& normalize()
			{
				const T length = length();

				x /= length;
				y /= length;

				return *this;
			}

			Vector2D getNormalized() const
			{
				Vector2D normalized = *this;

				normalized.normalize();

				return normalized;
			}
		};
	}
}

#endif /* Comp2D_HEADERS_UTILITIES_VECTOR2D_H_ */
