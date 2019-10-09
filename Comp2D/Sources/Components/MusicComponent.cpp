/* MusicComponent.cpp -- 'Comp2D' Game Engine 'MusicComponent' class source file
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

#include "Comp2D/Headers/Components/MusicComponent.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/MusicResource.h"
#include "Comp2D/Headers/Resources/Resource.h"

Comp2D::Components::MusicComponent::MusicComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	Comp2D::Resources::MusicResource* resource,
	bool pauseMusicOnGamePaused,
	bool playOnInitializeState,
	int loopsOnPlay
)
	:
	ResourceComponent( id, gameObject ),
	m_playing( false ),
	m_paused( false ),
	pauseMusicOnGamePaused( pauseMusicOnGamePaused ),
	playOnInitializeState{ playOnInitializeState },
	loopsOnPlay( loopsOnPlay )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
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
			"MusicComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::MusicComponent::~MusicComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::MusicComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( m_paused )
	{
		resume();
	}

	stop();
}

void Comp2D::Components::MusicComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( playOnInitializeState )
	{
		play();

		if( pauseMusicOnGamePaused && Comp2D::Game::isPaused() )
		{
			pause();
		}
	}
}

void Comp2D::Components::MusicComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::MusicComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( pauseMusicOnGamePaused )
	{
		pause();
	}
}

void Comp2D::Components::MusicComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( pauseMusicOnGamePaused )
	{
		resume();
	}
}

void Comp2D::Components::MusicComponent::setResource( Comp2D::Resources::Resource* resource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) setResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			resource->getName().c_str()
		);
		*/

		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) typeid( resource ).name %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			typeid( resource ).name()
		);
		*/
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) typeid( Comp2D::Resources::MusicResource* ).name %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			typeid( Comp2D::Resources::MusicResource* ).name()
		);
		*/
	#endif

	Comp2D::Resources::MusicResource* musicResource = dynamic_cast<Comp2D::Resources::MusicResource*>( resource );

	if( musicResource )
	{
		m_resource = musicResource;
		// POSSÍVEL NECESSIDADE DE LIBERAÇÃO/CARREGAMENTO DE RECURSO
	}
	else
	{
		// TODO: Lançar exceção
	}
}

Comp2D::Resources::MusicResource* Comp2D::Components::MusicComponent::getResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) getResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return static_cast<Comp2D::Resources::MusicResource*>( m_resource );
}

void Comp2D::Components::MusicComponent::pause()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) pause\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( m_playing && Mix_PlayingMusic() )
	{
		Mix_PauseMusic();

		m_playing = false;
		m_paused = true;
	}
}

void Comp2D::Components::MusicComponent::play()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) play\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( !Mix_PlayingMusic() && !Mix_PausedMusic() )
	{
		if( Mix_PlayMusic( getResource()->getMusic(), loopsOnPlay ) == -1 )
		{
			#ifdef DEBUG
				SDL_LogError( SDL_LOG_CATEGORY_AUDIO, "Mix_PlayMusic: %s\n", Mix_GetError() );
			#endif

			Comp2D::Game::reportError( "Fatal Error: 011", "Unable to play music! SDL_mixer Error: ", Mix_GetError() );
		}

		m_playing = true;
		m_paused = false;
	}
}

void Comp2D::Components::MusicComponent::resume()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) resume\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( m_paused )
	{
		Mix_ResumeMusic();

		m_playing = true;
		m_paused = false;
	}
}

void Comp2D::Components::MusicComponent::stop()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"MusicComponent with ID %u (From GameObject with ID %u named %s) stop\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( m_playing && Mix_PlayingMusic() )
	{
		Mix_HaltMusic();

		m_playing = false;
		m_paused = false;
	}
}
