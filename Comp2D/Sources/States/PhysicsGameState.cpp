/* PhysicsGameState.cpp -- 'Comp2D' Game Engine 'PhysicsGameState' class source file
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

#include "Comp2D/Headers/States/PhysicsGameState.h"

#include <iterator>
#include <list>

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameState.h"
#include "Comp2D/Headers/States/GameStateBehavior.h"
#include "Comp2D/Headers/States/BeginContactPhysicsEvent.h"
#include "Comp2D/Headers/States/EndContactPhysicsEvent.h"
#include "Comp2D/Headers/States/PhysicsEvent.h"
#include "Comp2D/Headers/States/PostSolvePhysicsEvent.h"
#include "Comp2D/Headers/States/PreSolvePhysicsEvent.h"
#include "Comp2D/Headers/Time/TimeManager.h"

float32 Comp2D::States::PhysicsGameState::scaleFactor = 0.01f;

Comp2D::States::PhysicsGameState::PhysicsGameState
(
	Uint32 stateID,
	b2Vec2 gravity,
	int32 velocityIterations,
	int32 positionIterations,
	float32 timeStep
)
	:
	Comp2D::States::GameState( stateID ),
	b2ContactListener(),
	m_velocityIterations{ velocityIterations },
	m_positionIterations{ positionIterations },
	m_timeStep{ timeStep },
	m_gravity( gravity )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u Constructor body Start\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u Constructor body End\n", m_id );
	#endif
}

Comp2D::States::PhysicsGameState::~PhysicsGameState()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u Destroying\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u Destroyed\n", m_id );
	#endif
}

void Comp2D::States::PhysicsGameState::beforeSetup()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u beforeSetup\n", m_id );
	#endif

	initializePhysicsWorld();
}

void Comp2D::States::PhysicsGameState::finalize()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u finalize\n", m_id );
	#endif

	finalizeGameStateTimerFunctions();
	finalizeGameStateTimedProcedures();
	finalizeGameSeparateThreadsFunctions();
	finalizeComponents();
	finalizeGameStateBehaviors();
	deleteComponents();
	deleteGameStateBehaviors();
	freeResourcesFromResourceComponents();
	deleteGameObjects();
	finalizePhysicsWorld();
}

void Comp2D::States::PhysicsGameState::update()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u update\n", m_stateID );
	#endif

	Uint32 currentTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

	world->Step
	(
		m_timeStep * Comp2D::Game::timeManager->getTimeScale(),
		m_velocityIterations,
		m_positionIterations
	);

	triggerPhysicsEvents();

	updateGameStateBehaviors();

	// updateGameObjects()
	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		if( currentGameObject->isActive() && currentGameObject->isActiveInHierarchy() )
		{
			// updateGameObject( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds )
			updateGameObjectAnimationsControllerComponent( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds );

			updateGameObjectTimelinesControllerComponent( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds );

			if( currentGameObject->parentGameObject == nullptr )
			{
				updateGameObjectTransformComponent( currentGameObject );
			}

			updateGameObjectBehaviors( currentGameObject );
		}
	}
}

void Comp2D::States::PhysicsGameState::finalizePhysicsWorld()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u finalizePhysicsWorld\n", m_id );
	#endif

	delete world;
	world = nullptr;
}

void Comp2D::States::PhysicsGameState::initializePhysicsWorld()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u initializePhysicsWorld\n", m_id );
	#endif

	world = new b2World( m_gravity );
	world->SetContactListener( this );
}

void Comp2D::States::PhysicsGameState::triggerPhysicsEvents()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsGameState with ID %u triggerPhysicsEvents\n",
			m_id
		);
		*/
	#endif

	for
	(
		std::list<PhysicsEvent*>::iterator physicsEventIt = m_physicsEvents.begin();
		physicsEventIt != m_physicsEvents.end();
		++physicsEventIt
	)
	{
		PhysicsEvent* currentPhysicsEvent = (*physicsEventIt);

		currentPhysicsEvent->triggerEvent();

		delete currentPhysicsEvent;
	}

	m_physicsEvents.clear();
}

void Comp2D::States::PhysicsGameState::setup()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u setup\n", m_id );
	#endif
}

void Comp2D::States::PhysicsGameState::BeginContact( b2Contact* contact )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u BeginContact\n", m_stateID );
	#endif

	Comp2D::Objects::GameObject* gameObjectA = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureA()->GetUserData() );
	Comp2D::Objects::GameObject* gameObjectB = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureB()->GetUserData() );

	m_physicsEvents.push_back
	(
		new BeginContactPhysicsEvent
		(
			&m_gameStateBehaviors,
			gameObjectA,
			gameObjectB,
			contact
		)
	);
}

void Comp2D::States::PhysicsGameState::EndContact( b2Contact* contact )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u EndContact\n", m_stateID );
	#endif

	Comp2D::Objects::GameObject* gameObjectA = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureA()->GetUserData() );
	Comp2D::Objects::GameObject* gameObjectB = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureB()->GetUserData() );

	m_physicsEvents.push_back
	(
		new EndContactPhysicsEvent
		(
			&m_gameStateBehaviors,
			gameObjectA,
			gameObjectB,
			contact
		)
	);
}

void Comp2D::States::PhysicsGameState::PostSolve( b2Contact* contact, const b2ContactImpulse* impulse )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u PostSolve\n", m_stateID );
	#endif

	Comp2D::Objects::GameObject* gameObjectA = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureA()->GetUserData() );
	Comp2D::Objects::GameObject* gameObjectB = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureB()->GetUserData() );

	m_physicsEvents.push_back
	(
		new PostSolvePhysicsEvent
		(
			&m_gameStateBehaviors,
			gameObjectA,
			gameObjectB,
			contact,
			impulse
		)
	);
}

void Comp2D::States::PhysicsGameState::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsGameState with ID %u PreSolve\n", m_stateID );
	#endif

	Comp2D::Objects::GameObject* gameObjectA = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureA()->GetUserData() );
	Comp2D::Objects::GameObject* gameObjectB = reinterpret_cast<Comp2D::Objects::GameObject*>( contact->GetFixtureB()->GetUserData() );

	m_physicsEvents.push_back
	(
		new PreSolvePhysicsEvent
		(
			&m_gameStateBehaviors,
			gameObjectA,
			gameObjectB,
			contact,
			oldManifold
		)
	);
}
