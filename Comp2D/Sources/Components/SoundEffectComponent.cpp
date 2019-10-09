/* SoundEffectComponent.cpp -- 'Comp2D' Game Engine 'SoundEffectComponent' class source file
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

#include "Comp2D/Headers/Components/SoundEffectComponent.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/SoundEffectResource.h"

Comp2D::Components::SoundEffectComponent::SoundEffectComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	Comp2D::Resources::SoundEffectResource* resource,
	bool pauseSoundEffectOnGamePaused,
	int channelToPlay,
	int loopsOnPlay
)
	:
	ResourceComponent( id, gameObject ),
	pauseSoundEffectOnGamePaused( pauseSoundEffectOnGamePaused ),
	channelToPlay( channelToPlay ),
	loopsOnPlay( loopsOnPlay )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	setResource( resource );

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::SoundEffectComponent::~SoundEffectComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( Mix_Playing( -1 ) > 0 )
	{
		Mix_HaltChannel( -1 );
	}
}

void Comp2D::Components::SoundEffectComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::SoundEffectComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::SoundEffectComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( pauseSoundEffectOnGamePaused )
	{
		Mix_Pause( channelToPlay );
	}
}

void Comp2D::Components::SoundEffectComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( pauseSoundEffectOnGamePaused )
	{
		Mix_Resume( channelToPlay );
	}
}

void Comp2D::Components::SoundEffectComponent::setResource( Comp2D::Resources::Resource* resource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) setResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			resource->getName().c_str()
		);
		*/
	#endif

	Comp2D::Resources::SoundEffectResource* soundEffectResource = dynamic_cast<Comp2D::Resources::SoundEffectResource*>( resource );

	if( soundEffectResource )
	{
		m_resource = soundEffectResource;

		// POSSÍVEL NECESSIDADE DE LIBERAÇÃO/CARREGAMENTO DE RECURSO
	}
	else
	{
		// TODO: Lançar exceção
	}
}

Comp2D::Resources::SoundEffectResource* Comp2D::Components::SoundEffectComponent::getResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) getResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return static_cast<Comp2D::Resources::SoundEffectResource*>( m_resource );
}

void Comp2D::Components::SoundEffectComponent::play()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"SoundEffectComponent with ID %u (From GameObject with ID %u named %s) play\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( Mix_PlayChannel( channelToPlay, getResource()->getSoundEffect(), loopsOnPlay ) == -1 )
	{
		#ifdef DEBUG
			SDL_LogError( SDL_LOG_CATEGORY_AUDIO, "Mix_PlayChannel: %s\n", Mix_GetError() );
		#endif

		Comp2D::Game::reportError( "Fatal Error: 012", "Unable to play sound effect! SDL_mixer Error: ", Mix_GetError() );
	}
}
