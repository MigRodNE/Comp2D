/* EndContactPhysicsEvent.cpp -- 'Comp2D' Game Engine 'EndContactPhysicsEvent' class source file
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

#include "Comp2D/Headers/States/EndContactPhysicsEvent.h"

#include <iterator>
#include <list>

#include <SDL.h>

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameStateBehavior.h"
#include "Comp2D/Headers/States/PhysicsEvent.h"

Comp2D::States::EndContactPhysicsEvent::EndContactPhysicsEvent
(
	std::list<Comp2D::States::GameStateBehavior*>* gameStateBehaviors,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB,
	b2Contact* contact
)
	:
	PhysicsEvent( gameStateBehaviors, gameObjectA, gameObjectB, contact )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent Constructor body Start\n"
		);
		*/
	#endif

	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent Constructor body End\n"
		);
		*/
	#endif
}

Comp2D::States::EndContactPhysicsEvent::~EndContactPhysicsEvent()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent Destroying\n"
		);
		*/
	#endif

	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent Destroyed\n"
		);
		*/
	#endif
}

void Comp2D::States::EndContactPhysicsEvent::endContactGameStateBehaviors()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent endContactGameStateBehaviors: m_gameObjectA with ID %u named %s; m_gameObjectB with ID %u named %s\n",
			m_gameObjectA->getID(),
			m_gameObjectA->getName().c_str(),
			m_gameObjectB->getID(),
			m_gameObjectB->getName().c_str()
		);
		*/
	#endif

	Comp2D::States::GameStateBehavior* currentGameStateBehavior = nullptr;

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator gameStateBehaviorIt = m_gameStateBehaviors->begin();
		gameStateBehaviorIt != m_gameStateBehaviors->end();
		++gameStateBehaviorIt
	)
	{
		currentGameStateBehavior = (*gameStateBehaviorIt);

		if( currentGameStateBehavior->isEnabled() )
		{
			currentGameStateBehavior->endContact( m_contact, m_gameObjectA, m_gameObjectB );
		}
	}
}

void Comp2D::States::EndContactPhysicsEvent::triggerEvent()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"EndContactPhysicsEvent triggerEvent\n"
		);
		*/
	#endif

	endContactGameStateBehaviors();

	m_gameObjectA->endContact( m_contact, m_gameObjectB );
	m_gameObjectB->endContact( m_contact, m_gameObjectA );
}
