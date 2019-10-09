/* GameStateBehavior.cpp -- 'Comp2D' Game Engine 'GameStateBehavior' class source file
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

#include "Comp2D/Headers/States/GameStateBehavior.h"

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameState.h"

Comp2D::States::GameStateBehavior::GameStateBehavior( unsigned int id )
	:
	m_enabled( false ),
	m_id( id ),
	gameState( nullptr )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u Constructor body Start\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u Constructor body End\n", m_id );
	#endif
}

Comp2D::States::GameStateBehavior::~GameStateBehavior()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u Destroying\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u Destroyed\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u debugLogComponentData\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::beginContact
(
	b2Contact* contact,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameStateBehavior with ID %u beginContact: gameObjectA with ID %u; gameObjectB with ID %u\n",
			m_id,
			gameObjectA->getID(),
			gameObjectB->getID()
		);
		*/
	#endif
}

void Comp2D::States::GameStateBehavior::endContact
(
	b2Contact* contact,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameStateBehavior with ID %u endContact: gameObjectA with ID %u; gameObjectB with ID %u\n",
			m_id,
			gameObjectA->getID(),
			gameObjectB->getID()
		);
		*/
	#endif
}

void Comp2D::States::GameStateBehavior::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onDelete\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onDisable\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onEnable\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onEvent( SDL_Event e )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onEvent with event of type %u\n", m_id, e.type );
	#endif
}

void Comp2D::States::GameStateBehavior::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onFinalizeState\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onInitializeState\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onInstantiated\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onPaused()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onPaused\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::onUnpaused()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u onUnpaused\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::postSolve
(
	b2Contact* contact,
	const b2ContactImpulse* impulse,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameStateBehavior with ID %u postSolve: gameObjectA with ID %u; gameObjectB with ID %u\n",
			m_id,
			gameObjectA->getID(),
			gameObjectB->getID()
		);
		*/
	#endif
}

void Comp2D::States::GameStateBehavior::preSolve
(
	b2Contact* contact,
	const b2Manifold* oldManifold,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameStateBehavior with ID %u preSolve: gameObjectA with ID %u; gameObjectB with ID %u\n",
			m_id,
			gameObjectA->getID(),
			gameObjectB->getID()
		);
		*/
	#endif
}

void Comp2D::States::GameStateBehavior::update()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u update\n", m_id );
	#endif
}

void Comp2D::States::GameStateBehavior::setEnabled( bool enabled )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u setEnabled: enabled = %i\n", m_id, enabled );
	#endif

	if( !m_enabled && enabled )
	{
		onEnable();
		m_enabled = enabled;
	}
	else if( m_enabled && !enabled )
	{
		onDisable();
		m_enabled = enabled;
	}
}

bool Comp2D::States::GameStateBehavior::isEnabled() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u isEnabled\n", m_id );
	#endif

	return m_enabled;
}

unsigned int Comp2D::States::GameStateBehavior::getID() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameStateBehavior with ID %u getID\n", m_id );
	#endif

	return m_id;
}
