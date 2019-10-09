/* PhysicsEvent.cpp -- 'Comp2D' Game Engine 'PhysicsEvent' class source file
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

#include "Comp2D/Headers/States/PhysicsEvent.h"

#include <list>

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::States::PhysicsEvent::PhysicsEvent
(
	std::list<Comp2D::States::GameStateBehavior*>* gameStateBehaviors,
	Comp2D::Objects::GameObject* gameObjectA,
	Comp2D::Objects::GameObject* gameObjectB,
	b2Contact* contact,
	const b2ContactImpulse* impulse,
	const b2Manifold* oldManifold
)
	:
	m_contact( contact ),
	m_impulse( impulse ),
	m_oldManifold( oldManifold ),
	m_gameObjectA( gameObjectA ),
	m_gameObjectB( gameObjectB ),
	m_gameStateBehaviors( gameStateBehaviors )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsEvent Constructor body Start\n"
		);
		*/
	#endif

	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsEvent Constructor body End\n"
		);
		*/
	#endif
}

Comp2D::States::PhysicsEvent::~PhysicsEvent()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsEvent Destroying\n"
		);
		*/
	#endif

	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsEvent Destroyed\n"
		);
		*/
	#endif
}
