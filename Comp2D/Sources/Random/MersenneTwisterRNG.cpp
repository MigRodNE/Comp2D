/* MersenneTwisterRNG.cpp -- 'Comp2D' Game Engine 'MersenneTwisterRNG' class source file
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

#include "Comp2D/Headers/Random/MersenneTwisterRNG.h"

#include <limits>
#include <random>

#include <SDL.h>

#include "Comp2D/Headers/Random/RandomNumberGenerator.h"

Comp2D::Random::MersenneTwisterRNG::MersenneTwisterRNG()
	:
	RandomNumberGenerator()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG Constructor body Start\n" );
	#endif

	std::random_device randomDevice;
	mersenne = std::mt19937( randomDevice() );

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG Constructor body End\n" );
	#endif
}

Comp2D::Random::MersenneTwisterRNG::~MersenneTwisterRNG()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG Destroyed\n" );
	#endif
}

bool Comp2D::Random::MersenneTwisterRNG::getRandomBoolean()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomBoolean\n" );
	#endif

	return getRandomUnsignedInteger( 0, 1 ) == 1 ? true : false;
}

int Comp2D::Random::MersenneTwisterRNG::getRandomInteger()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomInteger\n" );
	#endif

	return getRandomInteger( std::numeric_limits<int>::min(), std::numeric_limits<int>::max() );
}

int Comp2D::Random::MersenneTwisterRNG::getRandomInteger( int minimumValue, int maximumValue )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomInteger: minimumValue = %i; maximumValue = %i\n", minimumValue, maximumValue );
	#endif

	std::uniform_int_distribution<int> integerDistributionWithBounds( minimumValue, maximumValue );

	return integerDistributionWithBounds( mersenne );
}

unsigned int Comp2D::Random::MersenneTwisterRNG::getRandomUnsignedInteger()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomUnsignedInteger\n" );
	#endif

	return getRandomUnsignedInteger( std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max() );
}

unsigned int Comp2D::Random::MersenneTwisterRNG::getRandomUnsignedInteger( unsigned int minimumValue, unsigned int maximumValue )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomUnsignedInteger: minimumValue = %u; maximumValue = %u\n", minimumValue, maximumValue );
	#endif

	std::uniform_int_distribution<unsigned int> unsignedIntegerDistributionWithBounds( minimumValue, maximumValue );

	return unsignedIntegerDistributionWithBounds( mersenne );
}

float Comp2D::Random::MersenneTwisterRNG::getRandomFloat()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomFloat\n" );
	#endif

	return getRandomFloat( std::numeric_limits<float>::min(), std::numeric_limits<float>::max() );
}

float Comp2D::Random::MersenneTwisterRNG::getRandomFloat( float minimumValue, float maximumValue )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomFloat: minimumValue = %f; maximumValue = %f\n", minimumValue, maximumValue );
	#endif

	std::uniform_real_distribution<float> floatDistributionWithBounds( minimumValue, maximumValue );

	return floatDistributionWithBounds( mersenne );
}

double Comp2D::Random::MersenneTwisterRNG::getRandomDouble()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomDouble\n" );
	#endif

	return getRandomDouble( std::numeric_limits<double>::min(), std::numeric_limits<double>::max() );
}

double Comp2D::Random::MersenneTwisterRNG::getRandomDouble( double minimumValue, double maximumValue )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "MersenneTwisterRNG getRandomDouble: minimumValue = %f; maximumValue = %f\n", minimumValue, maximumValue );
	#endif

	std::uniform_real_distribution<double> doubleDistributionWithBounds( minimumValue, maximumValue );

	return doubleDistributionWithBounds( mersenne );
}
