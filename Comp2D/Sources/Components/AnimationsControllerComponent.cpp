/* AnimationsControllerComponent.cpp -- 'Comp2D' Game Engine 'AnimationsControllerComponent' class source file
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

#include "Comp2D/Headers/Components/AnimationsControllerComponent.h"

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Animations/Animation.h"
#include "Comp2D/Headers/Animations/AnimationsController.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/SpriteComponent.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Components::AnimationsControllerComponent::AnimationsControllerComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* animationsControllerResource,
	bool playStartingAnimationOnInitializeState,
	bool pausable
)
	:
	Component( id, gameObject ),
	m_pausable( pausable ),
	m_animationsSpriteComponent( nullptr ),
	m_animationsControllerResource( animationsControllerResource ),
	playStartingAnimationOnInitializeState( playStartingAnimationOnInitializeState )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::AnimationsControllerComponent::~AnimationsControllerComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::AnimationsControllerComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	getAnimationsController()->setCurrentAnimation( getAnimationsController()->getCurrentAnimationIndex() );

	if( playStartingAnimationOnInitializeState )
	{
		getAnimationsController()->getCurrentAnimation()->start();

		if( m_pausable && Comp2D::Game::isPaused() )
		{
			getAnimationsController()->getCurrentAnimation()->pause();
		}
	}
}

void Comp2D::Components::AnimationsControllerComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::AnimationsControllerComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_pausable )
	{
		getAnimationsController()->getCurrentAnimation()->pause();
	}
}

void Comp2D::Components::AnimationsControllerComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_pausable )
	{
		getAnimationsController()->getCurrentAnimation()->unpause();
	}
}

void Comp2D::Components::AnimationsControllerComponent::setAnimationsControllerResource( Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* animationsControllerResource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) setAnimationsControllerResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			animationsControllerResource->getName().c_str()
		);
		*/

		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) typeid( animationsControllerResource ).name %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			typeid( animationsControllerResource ).name()
		);
		*/
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) typeid( Comp2D::Resources::MusicResource* ).name %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			typeid( Comp2D::Resources::MusicResource* ).name()
		);
		*/
	#endif

	m_animationsControllerResource = animationsControllerResource;
}

void Comp2D::Components::AnimationsControllerComponent::setAnimationsSpriteComponent( Comp2D::Components::SpriteComponent* animationsSpriteComponent )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) setAnimationsSpriteComponent: animationsSpriteComponent with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			animationsSpriteComponent->getID()
		);
		*/
	#endif

	m_animationsSpriteComponent = animationsSpriteComponent;
}

void Comp2D::Components::AnimationsControllerComponent::setPausable( bool pausable )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) setPausable: pausable = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			pausable
		);
	#endif

	m_pausable = pausable;

	if( Comp2D::Game::isPaused() )
	{
		if( m_pausable )
		{
			getAnimationsController()->getCurrentAnimation()->pause();
		}
	}
	else
	{
		if( !m_pausable )
		{
			getAnimationsController()->getCurrentAnimation()->unpause();
		}
	}
}

void Comp2D::Components::AnimationsControllerComponent::update( Uint32 currentTime )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) update: currentTime = %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			currentTime
		);
		*/
	#endif

	Comp2D::Animations::Animation* currentAnimation = getAnimationsController()->getCurrentAnimation();

	currentAnimation->update( currentTime );

	m_animationsSpriteComponent->setSpriteRect( currentAnimation->getCurrentAnimationKeyframe().getSpriteRect() );
}

bool Comp2D::Components::AnimationsControllerComponent::isPausable() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) isPausable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_pausable;
}

Comp2D::Animations::AnimationsController* Comp2D::Components::AnimationsControllerComponent::getAnimationsController() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) getAnimationsController\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return getAnimationsControllerResource()->getGenericResource();
}

Comp2D::Resources::GenericResource<Comp2D::Animations::AnimationsController>* Comp2D::Components::AnimationsControllerComponent::getAnimationsControllerResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) getAnimationsControllerResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_animationsControllerResource;
}

const Comp2D::Components::SpriteComponent& Comp2D::Components::AnimationsControllerComponent::getAnimationsSpriteComponent() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"AnimationsControllerComponent with ID %u (From GameObject with ID %u named %s) getAnimationsSpriteComponent\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return *m_animationsSpriteComponent;
}
