/* GameObjectBehavior.cpp -- 'Comp2D' Game Engine 'GameObjectBehavior' class source file
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

#include "Comp2D/Headers/Components/GameObjectBehavior.h"

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Components::GameObjectBehavior::GameObjectBehavior
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject
)
	:
	Component( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::GameObjectBehavior::~GameObjectBehavior()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehavior::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::GameObjectBehavior::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}
void Comp2D::Components::GameObjectBehavior::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::onEvent( SDL_Event e )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onEvent with event of type %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			e.type
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::onRotated( float32 rotation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onRotated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::onTranslated( b2Vec2 translation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) onTranslated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::update()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) update\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::beginContact( b2Contact* contact, Comp2D::Objects::GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) beginContact: otherGameObject with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			otherGameObject->getID()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::endContact( b2Contact* contact, Comp2D::Objects::GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) endContact: otherGameObject with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			otherGameObject->getID()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::postSolve( b2Contact* contact, const b2ContactImpulse* impulse, Comp2D::Objects::GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) postSolve: otherGameObject with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			otherGameObject->getID()
		);
		*/
	#endif
}

void Comp2D::Components::GameObjectBehavior::preSolve( b2Contact* contact, const b2Manifold* oldManifold, Comp2D::Objects::GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObjectBehavior with ID %u (From GameObject with ID %u named %s) preSolve: otherGameObject with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			otherGameObject->getID()
		);
		*/
	#endif
}
