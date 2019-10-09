/* TimelinesControllerComponent.cpp -- 'Comp2D' Game Engine 'TimelinesControllerComponent' class source file
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

#include "Comp2D/Headers/Components/TimelinesControllerComponent.h"

#include <SDL.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Timelines/Timeline.h"
#include "Comp2D/Headers/Timelines/TimelinesController.h"

Comp2D::Components::TimelinesControllerComponent::TimelinesControllerComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	Comp2D::Resources::GenericResource<Comp2D::Timelines::TimelinesController>* timelinesControllerResource,
	bool playStartingTimelineOnInitializeState,
	bool pausable
)
	:
	Component( id, gameObject ),
	m_pausable( pausable ),
	m_timelinesControllerResource( timelinesControllerResource ),
	playStartingTimelineOnInitializeState( playStartingTimelineOnInitializeState )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::TimelinesControllerComponent::~TimelinesControllerComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TimelinesControllerComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	getTimelinesController()->setCurrentTimeline( getTimelinesController()->getCurrentTimelineIndex() );

	if( playStartingTimelineOnInitializeState )
	{
		getTimelinesController()->getCurrentTimeline()->start( gameObject );

		if( m_pausable && Comp2D::Game::isPaused() )
		{
			getTimelinesController()->getCurrentTimeline()->pause();
		}
	}
}

void Comp2D::Components::TimelinesControllerComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::TimelinesControllerComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_pausable )
	{
		getTimelinesController()->getCurrentTimeline()->pause();
	}
}

void Comp2D::Components::TimelinesControllerComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( m_pausable )
	{
		getTimelinesController()->getCurrentTimeline()->unpause();
	}
}

void Comp2D::Components::TimelinesControllerComponent::setTimelinesControllerResource( Comp2D::Resources::GenericResource<Comp2D::Timelines::TimelinesController>* timelinesControllerResource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) setTimelinesControllerResource: timelinesControllerResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			timelinesControllerResource->getName().c_str()
		);
		*/
	#endif

	m_timelinesControllerResource = timelinesControllerResource;
}

void Comp2D::Components::TimelinesControllerComponent::setPausable( bool pausable )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) setPausable: pausable = %i\n",
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
			getTimelinesController()->getCurrentTimeline()->pause();
		}
	}
	else
	{
		if( !m_pausable )
		{
			getTimelinesController()->getCurrentTimeline()->unpause();
		}
	}
}

void Comp2D::Components::TimelinesControllerComponent::update( Uint32 currentTime )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) update: currentTime = %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			currentTime
		);
		*/
	#endif

	getTimelinesController()->getCurrentTimeline()->update( currentTime, gameObject );
}

bool Comp2D::Components::TimelinesControllerComponent::isPausable() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) isPausable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_pausable;
}

Comp2D::Timelines::TimelinesController* Comp2D::Components::TimelinesControllerComponent::getTimelinesController() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) getTimelinesController\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return getTimelinesControllerResource()->getGenericResource();
}

Comp2D::Resources::GenericResource<Comp2D::Timelines::TimelinesController>* Comp2D::Components::TimelinesControllerComponent::getTimelinesControllerResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TimelinesControllerComponent with ID %u (From GameObject with ID %u named %s) getTimelinesControllerResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_timelinesControllerResource;
}
