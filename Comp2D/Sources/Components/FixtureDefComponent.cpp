/* FixtureDefComponent.cpp -- 'Comp2D' Game Engine 'FixtureDefComponent' class source file
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

#include "Comp2D/Headers/Components/FixtureDefComponent.h"

#include <SDL.h>

#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Components::FixtureDefComponent::FixtureDefComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2FixtureDef* fixtureDef
)
	:
	Component( id, gameObject ),
	m_fixtureDef( fixtureDef )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif


	closestUpperPhysicsComponent = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>( gameObject->transform );
	if( closestUpperPhysicsComponent == nullptr && gameObject->parentGameObject != nullptr )
	{
		closestUpperPhysicsComponent = getClosestUpperPhysicsComponent( gameObject->parentGameObject );
	}

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::FixtureDefComponent::FixtureDefComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2Filter filter,
	b2Shape* shape,
	float32 friction,
	float32 restitution,
	float32 density,
	bool isSensor
)
	:
	Component( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor 2 body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_fixtureDef = new b2FixtureDef();

	m_fixtureDef->shape = shape;
	m_fixtureDef->userData = gameObject;
	m_fixtureDef->friction = friction;
	m_fixtureDef->restitution = restitution;
	m_fixtureDef->density = density;
	m_fixtureDef->isSensor = isSensor;
	m_fixtureDef->filter = filter;

	closestUpperPhysicsComponent = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>( gameObject->transform );
	if( closestUpperPhysicsComponent == nullptr && gameObject->parentGameObject != nullptr )
	{
		closestUpperPhysicsComponent = getClosestUpperPhysicsComponent( gameObject->parentGameObject );
	}

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor 2 body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::FixtureDefComponent::FixtureDefComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2Shape* shape,
	float32 friction,
	float32 restitution,
	float32 density,
	bool isSensor,
	EFilterCategory filterCategory,
	EFilterGroup filterGroup
)
	:
	Component( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor 3 body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_fixtureDef = new b2FixtureDef();

	m_fixtureDef->shape = shape;
	m_fixtureDef->userData = gameObject;
	m_fixtureDef->friction = friction;
	m_fixtureDef->restitution = restitution;
	m_fixtureDef->density = density;
	m_fixtureDef->isSensor = isSensor;

	b2Filter filter;
	filter.categoryBits = static_cast<Uint16>( filterCategory );
	switch( filterCategory )
	{
		case EFilterCategory::Default:
			filter.maskBits = static_cast<Uint16>( EFilterMask::Default );
			break;
		case EFilterCategory::Player:
			filter.maskBits = static_cast<Uint16>( EFilterMask::Player );
			break;
		case EFilterCategory::ScenarioObject:
			filter.maskBits = static_cast<Uint16>( EFilterMask::ScenarioObject );
			break;
		case EFilterCategory::Ground:
			filter.maskBits = static_cast<Uint16>( EFilterMask::Ground );
			break;
		case EFilterCategory::PassthroughGround:
			filter.maskBits = static_cast<Uint16>( EFilterMask::PassthroughGround );
			break;
		case EFilterCategory::Wall:
			filter.maskBits = static_cast<Uint16>( EFilterMask::Wall );
			break;
		case EFilterCategory::PassthroughWall:
			filter.maskBits = static_cast<Uint16>( EFilterMask::PassthroughWall );
			break;
		default:
			filter.maskBits = 0x0000;
			break;
	}
	filter.groupIndex = static_cast<int>( filterGroup );
	m_fixtureDef->filter = filter;

	closestUpperPhysicsComponent = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>( gameObject->transform );
	if( closestUpperPhysicsComponent == nullptr && gameObject->parentGameObject != nullptr )
	{
		closestUpperPhysicsComponent = getClosestUpperPhysicsComponent( gameObject->parentGameObject );
	}

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Constructor 3 body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::FixtureDefComponent::~FixtureDefComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_fixture = nullptr;

	if( m_fixtureDef )
	{
		delete m_fixtureDef;
		m_fixtureDef = nullptr;
	}

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::PhysicsTransformComponent* Comp2D::Components::FixtureDefComponent::getClosestUpperPhysicsComponent( Comp2D::Objects::GameObject* parentGameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) getClosestUpperPhysicsComponent: parentGameObject with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			parentGameObject->getID()
		);
	#endif

	Comp2D::Components::PhysicsTransformComponent* parentGameObjectPhysicsTransformComponent = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>
	(
		parentGameObject->transform
	);

	if( parentGameObjectPhysicsTransformComponent )
	{
		return parentGameObjectPhysicsTransformComponent;
	}
	else if( parentGameObject->parentGameObject )
	{
		return getClosestUpperPhysicsComponent( parentGameObject->parentGameObject );
	}

	return nullptr;
}

void Comp2D::Components::FixtureDefComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "gameObject Address = %p\n", gameObject );
		if( gameObject )
		{
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "gameObject->getID() = %u\n", gameObject->getID() );
		}

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef Address = %p\n", m_fixtureDef );
		if( m_fixtureDef )
		{
			Comp2D::Objects::GameObject* fixtureDefUserData = reinterpret_cast<Comp2D::Objects::GameObject*>( m_fixtureDef->userData );

			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->shape->GetType() = %i\n", static_cast<int>( m_fixtureDef->shape->GetType() ) );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->userData Address = %p\n", fixtureDefUserData );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->userData->getID() = %u\n", fixtureDefUserData->getID() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->friction = %f\n", m_fixtureDef->friction );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->restitution = %f\n", m_fixtureDef->restitution );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->density = %f\n", m_fixtureDef->density );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->isSensor = %i\n", m_fixtureDef->isSensor );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->filter.categoryBits = %X\n", m_fixtureDef->filter.categoryBits );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->filter.maskBits = %X\n", m_fixtureDef->filter.maskBits );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixtureDef->filter.groupIndex = %i\n", m_fixtureDef->filter.groupIndex );
		}

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture Address = %p\n", m_fixture );
		if( m_fixture )
		{
			Comp2D::Objects::GameObject* fixtureUserData = reinterpret_cast<Comp2D::Objects::GameObject*>( m_fixture->GetUserData() );

			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetType() = %i\n", static_cast<int>( m_fixture->GetType() ) );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetUserData() Address = %p\n", fixtureUserData );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetUserData()->getID() = %u\n", fixtureUserData->getID() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetFriction() = %f\n", m_fixture->GetFriction() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetRestitution() = %f\n", m_fixture->GetRestitution() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetDensity() = %f\n", m_fixture->GetDensity() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->IsSensor() = %i\n", m_fixture->IsSensor() );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetFilterData().categoryBits = %X\n", m_fixture->GetFilterData().categoryBits );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetFilterData().maskBits = %X\n", m_fixture->GetFilterData().maskBits );
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "m_fixture->GetFilterData().groupIndex = %i\n", m_fixture->GetFilterData().groupIndex );
		}

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "closestUpperPhysicsComponent Address = %p\n", closestUpperPhysicsComponent );
		if( closestUpperPhysicsComponent )
		{
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "closestUpperPhysicsComponent->getID() = %u\n", closestUpperPhysicsComponent->getID() );
		}
	#endif
}

void Comp2D::Components::FixtureDefComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( closestUpperPhysicsComponent )
	{
		closestUpperPhysicsComponent->setFixtureDefComponentActive( this, true );
	}
}

void Comp2D::Components::FixtureDefComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	/*
	if( closestUpperPhysicsComponent )
	{
		closestUpperPhysicsComponent->setFixtureDefComponentActive( this, false );
	}
	*/
}

void Comp2D::Components::FixtureDefComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::FixtureDefComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	/*
	if( closestUpperPhysicsComponent )
	{
		closestUpperPhysicsComponent->setFixtureDefComponentEnabled( this, false );
	}
	*/
}

void Comp2D::Components::FixtureDefComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	if( closestUpperPhysicsComponent )
	{
		closestUpperPhysicsComponent->setFixtureDefComponentEnabled( this, true );
	}
}

void Comp2D::Components::FixtureDefComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::FixtureDefComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::FixtureDefComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::FixtureDefComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::FixtureDefComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::FixtureDefComponent::setFixture( b2Fixture* fixture )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) setFixture\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_fixture = fixture;
}

const b2FixtureDef* Comp2D::Components::FixtureDefComponent::getFixtureDef() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) getFixtureDef\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_fixtureDef;
}

b2Fixture* Comp2D::Components::FixtureDefComponent::getFixture() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"FixtureDefComponent with ID %u (From GameObject with ID %u named %s) getFixture\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_fixture;
}
