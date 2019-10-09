/* AnimationsController.cpp -- 'Comp2D' Game Engine 'AnimationsController' class source file
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

#include "Comp2D/Headers/Animations/AnimationsController.h"

#include <iterator>
#include <list>
#include <string>
#include <vector>

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Animations/Animation.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/ResourcesManager.h"

Comp2D::Animations::AnimationsController::AnimationsController( int startingAnimationIndex )
	:
	m_currentAnimationIndex( startingAnimationIndex ),
	m_currentAnimation( nullptr )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController Constructor body End\n" );
	#endif
}

Comp2D::Animations::AnimationsController::~AnimationsController()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController Destroying\n" );
	#endif

	m_animationsResourcesNames.clear();

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController Destroyed\n" );
	#endif
}

void Comp2D::Animations::AnimationsController::setCurrentAnimation( int animationIndex )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController setCurrentAnimation: animationIndex = %i\n", animationIndex );
	#endif

	m_currentAnimationIndex = animationIndex;

	m_currentAnimation = static_cast<Comp2D::Resources::GenericResource<Comp2D::Animations::Animation>*>
	(
		Comp2D::Game::resourcesManager->getResource( m_animationsResourcesNames[m_currentAnimationIndex] )
	)->getGenericResource();

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController m_currentAnimation = %p\n", m_currentAnimation );
	#endif
}

void Comp2D::Animations::AnimationsController::setCurrentAnimation( const std::string& animationResourceName )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController setCurrentAnimation: animationName = %s\n", animationResourceName.c_str() );
	#endif

	for( unsigned int i = 0; i < m_animationsResourcesNames.size(); ++i )
	{
		if( m_animationsResourcesNames[i].compare( animationResourceName ) == 0 )
		{
			setCurrentAnimation( i );
		}
	}
}

void Comp2D::Animations::AnimationsController::setCurrentAnimation( const Comp2D::Animations::Animation& animation )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController setCurrentAnimation: animation named %s\n", animation.getName().c_str() );
	#endif

	setCurrentAnimation( animation.getName() );
}

void Comp2D::Animations::AnimationsController::update( Uint32 currentTime )
{
	SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController update: currentTime = %u\n", currentTime );

	m_currentAnimation->update( currentTime );
}

int Comp2D::Animations::AnimationsController::getCurrentAnimationIndex() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController getCurrentAnimationIndex\n" );
	#endif

	return m_currentAnimationIndex;
}

std::list<Comp2D::Animations::Animation> Comp2D::Animations::AnimationsController::getAnimations() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController getAnimations\n" );
	#endif

	std::list<Comp2D::Animations::Animation> animations;

	for
	(
		std::vector<std::string>::const_iterator animationResourceNameIt = m_animationsResourcesNames.cbegin();
		animationResourceNameIt != m_animationsResourcesNames.cend();
		++animationResourceNameIt
	)
	{
		animations.push_back
		(
			*static_cast<Comp2D::Resources::GenericResource<Comp2D::Animations::Animation>*>
			(
				Comp2D::Game::resourcesManager->getResource( *animationResourceNameIt )
			)->getGenericResource()
		);
	}

	return animations;
}

Comp2D::Animations::Animation* Comp2D::Animations::AnimationsController::getCurrentAnimation() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController getCurrentAnimation\n" );
	#endif

	return m_currentAnimation;
}

const std::vector<std::string>& Comp2D::Animations::AnimationsController::getAnimationsResourcesNames() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AnimationsController getAnimationsResourcesNames\n" );
	#endif

	return m_animationsResourcesNames;
}
