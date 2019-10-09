/* PhysicsTransformComponent.cpp -- 'Comp2D' Game Engine 'PhysicsTransformComponent' class source file
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

#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"

#include <cfloat>
#include <cmath>
#include <iterator>
#include <list>
#include <vector>

#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/Joints/b2Joint.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/FixtureDefComponent.h"
#include "Comp2D/Headers/Components/ScreenSpaceTransformComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/PhysicsGameState.h"
#include "Comp2D/Headers/Utilities/Math.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::PhysicsTransformComponent::PhysicsTransformComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2World* world,
	b2BodyDef def
)
	:
	TransformComponent( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body = world->CreateBody( &def );
	m_body->SetUserData( gameObject );

	m_localRotation = m_body->GetAngle() * Comp2D::Utilities::RAD_IN_DEGREES;
	m_worldRotation = m_localRotation;

	m_localPosition = m_body->GetPosition();
	m_localScale = b2Vec2( 1.0f, 1.0f );
	m_worldPosition = m_localPosition;
	m_worldScale = b2Vec2( 1.0f, 1.0f );

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::PhysicsTransformComponent::PhysicsTransformComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2World* world,
	b2BodyType type,
	b2Vec2 position,
	float32 angle,
	b2Vec2 linearVelocity,
	float32 angularVelocity,
	float32 linearDamping,
	float32 angularDamping,
	bool allowSleep,
	bool awake,
	bool fixedRotation,
	bool bullet,
	float32 gravityScale
)
	:
	TransformComponent( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor 2 body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	b2BodyDef bodyDef;

	bodyDef.type = type;
	bodyDef.position = position;
	bodyDef.angle = angle;
	bodyDef.linearVelocity = linearVelocity;
	bodyDef.angularVelocity = angularVelocity;
	bodyDef.linearDamping = linearDamping;
	bodyDef.angularDamping = angularDamping;
	bodyDef.allowSleep = allowSleep;
	bodyDef.awake = awake;
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.bullet = bullet;
	bodyDef.active = false;
	bodyDef.userData = gameObject;
	bodyDef.gravityScale = gravityScale;

	m_body = world->CreateBody( &bodyDef );

	m_localRotation = m_body->GetAngle() * Comp2D::Utilities::RAD_IN_DEGREES;
	m_worldRotation = m_localRotation;

	m_localPosition = m_body->GetPosition();
	m_localScale = b2Vec2( 1.0f, 1.0f );
	m_worldPosition = m_localPosition;
	m_worldScale = b2Vec2( 1.0f, 1.0f );

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor 2 body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::PhysicsTransformComponent::~PhysicsTransformComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body = nullptr;

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::updateTransform()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) updateTransform\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	/*
	PhysicsTransformComponent* parentGameObjectPhysicsTransform = nullptr;

	Comp2D::Components::ScreenSpaceTransformComponent* parentGameObjectScreenSpaceTransform = nullptr;

	if( gameObject->parentGameObject )
	{
		parentGameObjectPhysicsTransform = dynamic_cast<Comp2D::Components::PhysicsTransformComponent*>
		(
			gameObject->parentGameObject->transform
		);

		parentGameObjectScreenSpaceTransform = dynamic_cast<Comp2D::Components::ScreenSpaceTransformComponent*>
		(
			gameObject->parentGameObject->transform
		);
	}

	if
	(
		gameObject->parentGameObject != nullptr &&
		(
			parentGameObjectPhysicsTransform != nullptr ||
			parentGameObjectScreenSpaceTransform != nullptr
		)
	)
	{
		float32 cosParentGameObjectWorldRotationAngle = 0.0f;
		float32 sinParentGameObjectWorldRotationAngle = 0.0f;
		float32 updatedLocalRotation = 0.0f;

		b2Vec2 updatedLocalPosition;
		b2Vec2 parentGameObjectWorldPosition;

		if( parentGameObjectPhysicsTransform )
		{
			parentGameObjectWorldPosition =  parentGameObjectPhysicsTransform->m_worldPosition;

			updatedLocalPosition = getPosition() - parentGameObjectWorldPosition;
			if
			(
				abs( m_localPosition.x - updatedLocalPosition.x ) > FLT_EPSILON ||
				abs( m_localPosition.y - updatedLocalPosition.y ) > FLT_EPSILON
			)
			{
				m_localPosition = updatedLocalPosition;
			}
			//m_worldPosition = parentGameObjectWorldPosition + m_localPosition;

			updatedLocalPosition = b2Vec2
			(
				m_localPosition.x * parentGameObjectPhysicsTransform->m_worldScale.x,
				m_localPosition.y * parentGameObjectPhysicsTransform->m_worldScale.y
			);

			float32 parentGameObjectWorldRotation = parentGameObjectPhysicsTransform->m_worldRotation;
			updatedLocalRotation = getAngle() - parentGameObjectWorldRotation;
			if(	abs( m_localRotation - updatedLocalRotation ) > FLT_EPSILON )
			{
				m_localRotation = updatedLocalRotation;
			}
			m_worldRotation = parentGameObjectWorldRotation + m_localRotation;

			float32 parentGameObjectWorldRotationInRadians = parentGameObjectWorldRotation * Comp2D::Utilities::DEGREE_IN_RAD;
			cosParentGameObjectWorldRotationAngle = static_cast<float>
			(
				cos( parentGameObjectWorldRotationInRadians )
			);
			sinParentGameObjectWorldRotationAngle = static_cast<float>
			(
				sin( parentGameObjectWorldRotationInRadians )
			);
		}
		else
		{
			parentGameObjectWorldPosition =  parentGameObjectScreenSpaceTransform->getPhysicsWorldPosition();

			updatedLocalPosition = getPosition() - parentGameObjectWorldPosition;
			if
			(
				abs( m_localPosition.x - updatedLocalPosition.x ) > FLT_EPSILON ||
				abs( m_localPosition.y - updatedLocalPosition.y ) > FLT_EPSILON
			)
			{
				m_localPosition = updatedLocalPosition;
			}
			//m_worldPosition = parentGameObjectWorldPosition + m_localPosition;

			b2Vec2 parentGameObjectWorldScale = parentGameObjectScreenSpaceTransform->getWorldScale();
			updatedLocalPosition = b2Vec2
			(
				m_localPosition.x * parentGameObjectWorldScale.x,
				m_localPosition.y * parentGameObjectWorldScale.y
			);

			float32 parentGameObjectWorldRotation = parentGameObjectScreenSpaceTransform->getWorldRotation();
			updatedLocalRotation = getAngle() - parentGameObjectWorldRotation;
			if(	abs( m_localRotation - updatedLocalRotation ) > FLT_EPSILON )
			{
				m_localRotation = updatedLocalRotation;
			}
			m_worldRotation = parentGameObjectWorldRotation + m_localRotation;

			float32 parentGameObjectWorldRotationInRadians = parentGameObjectWorldRotation * Comp2D::Utilities::DEGREE_IN_RAD;
			cosParentGameObjectWorldRotationAngle = static_cast<float>
			(
				cos( parentGameObjectWorldRotationInRadians )
			);
			sinParentGameObjectWorldRotationAngle = static_cast<float>
			(
				sin( parentGameObjectWorldRotationInRadians )
			);

			//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u reached\n", m_id );
		}

		b2Mat22 rotationMatrix = b2Mat22
		(
			cosParentGameObjectWorldRotationAngle,
			-sinParentGameObjectWorldRotationAngle,
			sinParentGameObjectWorldRotationAngle,
			cosParentGameObjectWorldRotationAngle
		);
		updatedLocalPosition = b2Mul( rotationMatrix, updatedLocalPosition );

		//setTransform( parentGameObjectWorldPosition + updatedLocalPosition, getAngleInRadians() );
		//setTransform( m_worldPosition, getWorldRotationInRadians() );

		m_localPosition = updatedLocalPosition;
		m_localRotation = updatedLocalRotation;
		m_worldPosition = parentGameObjectWorldPosition + updatedLocalPosition;
	}
	else
	{
		m_worldPosition = getPosition();
		m_worldRotation = getAngle();

		m_localPosition = m_worldPosition;
		m_localRotation = m_worldRotation;

		//setTransform( m_worldPosition, getWorldRotationInRadians() );
	}

	setTransform( m_worldPosition, getWorldRotationInRadians() );
	*/

	if
	(
		gameObject->parentGameObject != nullptr &&
		gameObject->parentGameObject->transform != nullptr
	)
	{
		/*
		float32 cosParentGameObjectWorldRotationAngle = 0.0f;
		float32 sinParentGameObjectWorldRotationAngle = 0.0f;
		float32 updatedLocalRotation = 0.0f;

		b2Vec2 updatedLocalPosition;
		b2Vec2 parentGameObjectWorldPosition;

		parentGameObjectWorldPosition =  gameObject->parentGameObject->transform->getPhysicsWorldPosition();

		updatedLocalPosition = getPosition() - parentGameObjectWorldPosition;
		if
		(
			abs( m_localPosition.x - updatedLocalPosition.x ) > FLT_EPSILON ||
			abs( m_localPosition.y - updatedLocalPosition.y ) > FLT_EPSILON
		)
		{
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u updateLocalPosition EPSILON\n", m_id );

			m_localPosition = updatedLocalPosition;
		}
		//m_worldPosition = parentGameObjectWorldPosition + m_localPosition;

		b2Vec2 parentGameObjectWorldScale = gameObject->parentGameObject->transform->getWorldScale();
		updatedLocalPosition = b2Vec2
		(
			m_localPosition.x * parentGameObjectWorldScale.x,
			m_localPosition.y * parentGameObjectWorldScale.y
		);

		float32 parentGameObjectWorldRotation = gameObject->parentGameObject->transform->getWorldRotation();
		updatedLocalRotation = getAngle() - parentGameObjectWorldRotation;
		if(	abs( m_localRotation - updatedLocalRotation ) > FLT_EPSILON )
		{
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u updateLocalRotation EPSILON\n", m_id );

			m_localRotation = updatedLocalRotation;
		}
		m_worldRotation = parentGameObjectWorldRotation + m_localRotation;

		float32 parentGameObjectWorldRotationInRadians = gameObject->parentGameObject->transform->getWorldRotationInRadians();
		cosParentGameObjectWorldRotationAngle = static_cast<float>
		(
			cos( parentGameObjectWorldRotationInRadians )
		);
		sinParentGameObjectWorldRotationAngle = static_cast<float>
		(
			sin( parentGameObjectWorldRotationInRadians )
		);

		b2Mat22 rotationMatrix = b2Mat22
		(
			cosParentGameObjectWorldRotationAngle,
			-sinParentGameObjectWorldRotationAngle,
			sinParentGameObjectWorldRotationAngle,
			cosParentGameObjectWorldRotationAngle
		);
		updatedLocalPosition = b2Mul( rotationMatrix, updatedLocalPosition );

		//setTransform( parentGameObjectWorldPosition + updatedLocalPosition, getAngleInRadians() );
		//setTransform( m_worldPosition, getWorldRotationInRadians() );

		m_localPosition = updatedLocalPosition;
		m_localRotation = updatedLocalRotation;
		m_worldPosition = parentGameObjectWorldPosition + updatedLocalPosition;
		*/

		// SOLUÇÃO TEMPORÁRIA
		m_worldPosition = getPosition();
		m_worldRotation = getAngle();

		m_localPosition = getWorldPosition();
		m_localRotation = getWorldRotation();
	}
	else
	{
		m_worldPosition = getPosition();
		m_worldRotation = getAngle();

		m_localPosition = getWorldPosition();
		m_localRotation = getWorldRotation();

		//setTransform( m_worldPosition, getWorldRotationInRadians() );
	}

	setTransform( m_worldPosition, getWorldRotationInRadians() );
}

void Comp2D::Components::PhysicsTransformComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_active = %i\n", m_id, m_activeInHierarchy );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_enabled = %i\n", m_id, m_enabled );

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u gameObject Address = %p\n", m_id, gameObject );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u gameObject->getID() = %u\n", m_id, gameObject->getID() );

		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_localPosition = ( %f, %f )\n",
			m_id,
			m_localPosition.x,
			m_localPosition.y
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_localRotation = %f degrees\n",
			m_id,
			m_localRotation
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_localScale = ( %f, %f )\n",
			m_id,
			m_localScale.x,
			m_localScale.y
		);

		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_worldPosition = ( %f, %f )\n",
			m_id,
			m_worldPosition.x,
			m_worldPosition.y
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_worldRotation = %f degrees\n",
			m_id,
			m_worldRotation
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_worldScale = ( %f, %f )\n",
			m_id,
			m_worldScale.x,
			m_worldScale.y
		);

		Comp2D::Utilities::Vector2D<int> screenPosition = getScreenPosition();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u screenPosition = ( %i, %i )\n",
			m_id,
			screenPosition.x,
			screenPosition.y
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body Address = %p\n", m_id, m_body );

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetAngle() = %f radians\n", m_id, m_body->GetAngle() );

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetGravityScale() = %f\n", m_id, m_body->GetGravityScale() );

		b2Vec2 linearVelocity = m_body->GetLinearVelocity();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetLinearVelocity() = ( %f, %f )\n",
			m_id,
			linearVelocity.x,
			linearVelocity.y
		);

		b2Vec2 localCenter = m_body->GetLocalCenter();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetLocalCenter() = ( %f, %f )\n",
			m_id,
			localCenter.x,
			localCenter.y
		);

		b2MassData massData;
		m_body->GetMassData( &massData );
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetMassData(): mass = %f; center = ( %f, %f ); I = %f\n",
			m_id,
			massData.mass,
			massData.center.x,
			massData.center.y,
			massData.I
		);

		b2Vec2 position = m_body->GetPosition();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetPosition() = ( %f, %f )\n",
			m_id,
			position.x,
			position.y
		);

		b2Transform transform = m_body->GetTransform();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetTransform(): p = ( %f, %f ); q.s = %f; q.c = %f; q.getAngle() = %f radians\n",
			m_id,
			transform.p.x,
			transform.p.y,
			transform.q.s,
			transform.q.c,
			transform.q.GetAngle()
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetType() = %i\n", m_id, static_cast<int>( m_body->GetType() ) );

		Comp2D::Objects::GameObject* userData = reinterpret_cast<Comp2D::Objects::GameObject*>( m_body->GetUserData() );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetUserData() Address = %p\n", m_id, userData );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetUserData()->getID() = %u\n", m_id, userData->getID() );

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->GetWorld() Address = %p\n", m_id, m_body->GetWorld() );

		b2Vec2 worldCenter = m_body->GetWorldCenter();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u m_body->GetWorldCenter() = ( %f, %f )\n",
			m_id,
			worldCenter.x,
			worldCenter.y
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "PhysicsTransformComponent with ID %u m_body->IsActive() = %i\n", m_id, m_body->IsActive() );
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->SetActive( true );
}

void Comp2D::Components::PhysicsTransformComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->SetActive( false );
}

void Comp2D::Components::PhysicsTransformComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->SetActive( false );
}

void Comp2D::Components::PhysicsTransformComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->SetActive( true );
}

void Comp2D::Components::PhysicsTransformComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::PhysicsTransformComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::PhysicsTransformComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getPhysicsWorldPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getPhysicsWorldPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_worldPosition;
}

Comp2D::Utilities::Vector2D<int> Comp2D::Components::PhysicsTransformComponent::getScreenPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getScreenPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	//return Comp2D::Components::TransformComponent::getScreenPosition( m_body->GetPosition() );
	return Comp2D::Components::TransformComponent::getScreenPosition( m_worldPosition );
}

void Comp2D::Components::PhysicsTransformComponent::applyAngularImpulse( float32 impulse, bool wake )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyAngularImpulse: impulse = %f; wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			impulse,
			wake
		);
	#endif

	m_body->ApplyAngularImpulse( impulse, wake );
}

void Comp2D::Components::PhysicsTransformComponent::applyForce( const b2Vec2& force, const b2Vec2& point, bool wake )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyForce: force = ( %f, %f ); point = ( %f, %f ); wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			force.x,
			force.y,
			point.x,
			point.y,
			wake
		);
		*/
	#endif

	m_body->ApplyForce( force, point, wake );
}

void Comp2D::Components::PhysicsTransformComponent::applyForceToCenter( const b2Vec2& force, bool wake )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyForceToCenter: force = ( %f, %f ); wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			force.x,
			force.y,
			wake
		);
		*/
	#endif

	m_body->ApplyForceToCenter( force, wake );
}

void Comp2D::Components::PhysicsTransformComponent::applyLinearImpulse( const b2Vec2& impulse, const b2Vec2& point, bool wake )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyLinearImpulse: impulse = ( %f, %f ); point = ( %f, %f ); wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			impulse.x,
			impulse.y,
			point.x,
			point.y,
			wake
		);
	#endif

	m_body->ApplyLinearImpulse( impulse, point, wake );
}

void Comp2D::Components::PhysicsTransformComponent::applyLinearImpulseToCenter( const b2Vec2& impulse, bool wake )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyLinearImpulseToCenter: impulse = ( %f, %f ); wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			impulse.x,
			impulse.y,
			wake
		);
	#endif

	m_body->ApplyLinearImpulseToCenter( impulse, wake );
}

void Comp2D::Components::PhysicsTransformComponent::applyTorque( float32 torque, bool wake )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) applyTorque: torque = %f; wake = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			torque,
			wake
		);
	#endif

	m_body->ApplyTorque( torque, wake );
}

void Comp2D::Components::PhysicsTransformComponent::destroyFixture( b2Fixture* fixture )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) destroyFixture\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->DestroyFixture( fixture );
}

void Comp2D::Components::PhysicsTransformComponent::dump()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) dump\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->Dump();
}

void Comp2D::Components::PhysicsTransformComponent::getMassData( b2MassData* data ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getMassData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	m_body->GetMassData( data );
}

void Comp2D::Components::PhysicsTransformComponent::resetMassData()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) resetMassData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_body->ResetMassData();
}

void Comp2D::Components::PhysicsTransformComponent::setAngularDamping( float32 angularDamping )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setAngularDamping: angularDamping = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			angularDamping
		);
	#endif

	m_body->SetAngularDamping( angularDamping );
}

void Comp2D::Components::PhysicsTransformComponent::setAngularVelocity( float32 omega )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setAngularVelocity: omega = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			omega
		);
	#endif

	m_body->SetAngularVelocity( omega );
}

void Comp2D::Components::PhysicsTransformComponent::setAwake( bool flag )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setAwake: flag = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			flag
		);
	#endif

	m_body->SetAwake( flag );
}

void Comp2D::Components::PhysicsTransformComponent::setBullet( bool flag )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setBullet: flag = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			flag
		);
	#endif

	m_body->SetBullet( flag );
}

void Comp2D::Components::PhysicsTransformComponent::setFixedRotation( bool flag )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setFixedRotation: flag = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			flag
		);
	#endif

	m_body->SetFixedRotation( flag );
}

void Comp2D::Components::PhysicsTransformComponent::setFixtureDefComponentActive( FixtureDefComponent* fixtureDefComponent, bool active )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setFixtureDefComponentActive: fixtureDefComponent with ID %u; active = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			fixtureDefComponent->getID(),
			active
		);
	#endif

	if( fixtureDefComponent->isActiveInHierarchy() && !active )
	{
		if( fixtureDefComponent->getFixture() != nullptr )
		{
			m_body->DestroyFixture( fixtureDefComponent->getFixture() );
		}

		fixtureDefComponent->setFixture( nullptr );
	}
	else if( !fixtureDefComponent->isActiveInHierarchy() && active )
	{
		if( fixtureDefComponent->getFixture() == nullptr )
		{
			fixtureDefComponent->setFixture( m_body->CreateFixture( fixtureDefComponent->getFixtureDef() ) );
		}
	}
}

void Comp2D::Components::PhysicsTransformComponent::setFixtureDefComponentEnabled( FixtureDefComponent* fixtureDefComponent, bool enabled )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setFixtureDefComponentEnabled: fixtureDefComponent with ID %u; enabled = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			fixtureDefComponent->getID(),
			enabled
		);
	#endif

	if( fixtureDefComponent->isEnabled() && !enabled )
	{
		if( fixtureDefComponent->getFixture() != nullptr )
		{
			m_body->DestroyFixture( fixtureDefComponent->getFixture() );
		}

		fixtureDefComponent->setFixture( nullptr );
	}
	else if( !fixtureDefComponent->isEnabled() && enabled )
	{
		if( fixtureDefComponent->getFixture() == nullptr )
		{
			fixtureDefComponent->setFixture( m_body->CreateFixture( fixtureDefComponent->getFixtureDef() ) );
		}
	}
}

void Comp2D::Components::PhysicsTransformComponent::setGravityScale( float32 scale )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setGravityScale: scale = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			scale
		);
	#endif

	m_body->SetGravityScale( scale );
}

void Comp2D::Components::PhysicsTransformComponent::setMassData( const b2MassData* data )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setMassData: data->mass = %f; data->center = ( %f, %f ); data->I = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			data->mass,
			data->center.x,
			data->center.y,
			data->I
		);
	#endif

	m_body->SetMassData( data );
}

void Comp2D::Components::PhysicsTransformComponent::setLinearDamping( float32 linearDamping )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setLinearDamping: linearDamping = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			linearDamping
		);
	#endif

	m_body->SetLinearDamping( linearDamping );
}

void Comp2D::Components::PhysicsTransformComponent::setLinearVelocity( const b2Vec2& v )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setLinearVelocity: v = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			v.x,
			v.y
		);
		*/
	#endif

	m_body->SetLinearVelocity( v );
}

void Comp2D::Components::PhysicsTransformComponent::setLocalPosition( b2Vec2 position )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setLocalPosition: position = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			position.x,
			position.y
		);
		*/
	#endif

	m_localPosition = position;

	if
	(
		gameObject->parentGameObject != nullptr &&
		gameObject->parentGameObject->transform != nullptr
	)
	{
		m_worldPosition = gameObject->parentGameObject->transform->getPhysicsWorldPosition() + m_localPosition;
	}
	else
	{
		m_worldPosition = m_localPosition;
	}

	m_worldRotation = getAngle();

	setTransform( m_worldPosition, getWorldRotationInRadians() );

	//updateWorldPosition();
}

void Comp2D::Components::PhysicsTransformComponent::setSleepingAllowed( bool flag )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setSleepingAllowed: flag = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			flag
		);
	#endif

	m_body->SetSleepingAllowed( flag );
}

void Comp2D::Components::PhysicsTransformComponent::setTransform( const b2Vec2& position, float32 angle )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setTransform: position = ( %f, %f ); angle = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			position.x,
			position.y,
			angle
		);
		*/
	#endif

	m_body->SetTransform( position, angle );
}

void Comp2D::Components::PhysicsTransformComponent::setType( b2BodyType type )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) setType: type = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			static_cast<int>( type )
		);
	#endif

	m_body->SetType( type );
}

bool Comp2D::Components::PhysicsTransformComponent::isAwake() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) isAwake\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->IsAwake();
}

bool Comp2D::Components::PhysicsTransformComponent::isBodyActive() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) isBodyActive\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->IsActive();
}

bool Comp2D::Components::PhysicsTransformComponent::isBullet() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) isBullet\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->IsBullet();
}

bool Comp2D::Components::PhysicsTransformComponent::isFixedRotation() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) isFixedRotation\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->IsFixedRotation();
}

bool Comp2D::Components::PhysicsTransformComponent::isSleepingAllowed() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) isSleepingAllowed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->IsSleepingAllowed();
}

float32 Comp2D::Components::PhysicsTransformComponent::getAngle() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getAngle\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return Comp2D::Utilities::RAD_IN_DEGREES * getAngleInRadians();
}

float32 Comp2D::Components::PhysicsTransformComponent::getAngleInRadians() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getAngleInRadians\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetAngle();
}

float32 Comp2D::Components::PhysicsTransformComponent::getAngularDamping() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getAngularDamping\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetAngularDamping();
}

float32 Comp2D::Components::PhysicsTransformComponent::getAngularVelocity() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getAngularVelocity\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetAngularVelocity();
}

float32 Comp2D::Components::PhysicsTransformComponent::getGravityScale() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getGravityScale\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetGravityScale();
}

float32 Comp2D::Components::PhysicsTransformComponent::getInertia() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getInertia\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetInertia();
}

float32 Comp2D::Components::PhysicsTransformComponent::getLinearDamping() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLinearDamping\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetLinearDamping();
}

float32 Comp2D::Components::PhysicsTransformComponent::getMass() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getMass\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetMass();
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getLinearVelocityFromLocalPoint( const b2Vec2& localPoint ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLinearVelocityFromLocalPoint: localPoint = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			localPoint.x,
			localPoint.y
		);
		*/
	#endif

	return m_body->GetLinearVelocityFromLocalPoint( localPoint );
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getLinearVelocityFromWorldPoint( const b2Vec2& worldPoint ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLinearVelocityFromWorldPoint: worldPoint = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			worldPoint.x,
			worldPoint.y
		);
		*/
	#endif

	return m_body->GetLinearVelocityFromWorldPoint( worldPoint );
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getLocalPoint( const b2Vec2& worldPoint ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLocalPoint: worldPoint = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			worldPoint.x,
			worldPoint.y
		);
		*/
	#endif

	return m_body->GetLocalPoint( worldPoint );
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getLocalVector( const b2Vec2& worldVector ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLocalVector: worldVector = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			worldVector.x,
			worldVector.y
		);
		*/
	#endif

	return m_body->GetLocalVector( worldVector );
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getWorldPoint( const b2Vec2& localPoint ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getWorldPoint: localPoint = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			localPoint.x,
			localPoint.y
		);
		*/
	#endif

	return m_body->GetWorldPoint( localPoint );
}

b2Vec2 Comp2D::Components::PhysicsTransformComponent::getWorldVector( const b2Vec2& localVector ) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getWorldVector: localVector = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			localVector.x,
			localVector.y
		);
		*/
	#endif

	return m_body->GetWorldVector( localVector );
}

const b2Vec2& Comp2D::Components::PhysicsTransformComponent::getLocalCenter() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLocalCenter\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetLocalCenter();
}

const b2Vec2& Comp2D::Components::PhysicsTransformComponent::getLinearVelocity() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getLinearVelocity\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetLinearVelocity();
}

const b2Vec2& Comp2D::Components::PhysicsTransformComponent::getPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetPosition();
}

const b2Vec2& Comp2D::Components::PhysicsTransformComponent::getWorldCenter() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getWorldCenter\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetWorldCenter();
}

b2Fixture* Comp2D::Components::PhysicsTransformComponent::createFixture( const b2FixtureDef* def )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) createFixture: def\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return m_body->CreateFixture( def );
}

b2Fixture* Comp2D::Components::PhysicsTransformComponent::createFixture( const b2Shape* shape, float32 density )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) createFixture: shape; density = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			density
		);
	#endif

	return m_body->CreateFixture( shape, density );
}

b2Fixture* Comp2D::Components::PhysicsTransformComponent::getFixtureList()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getFixtureList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetFixtureList();
}

const b2Fixture* Comp2D::Components::PhysicsTransformComponent::getFixtureList() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getFixtureList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetFixtureList();
}

const b2Transform& Comp2D::Components::PhysicsTransformComponent::getTransform() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getTransform\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetTransform();
}

b2BodyType Comp2D::Components::PhysicsTransformComponent::getType() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getType\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetType();
}

b2JointEdge* Comp2D::Components::PhysicsTransformComponent::getJointList()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getJointList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetJointList();
}

const b2JointEdge* Comp2D::Components::PhysicsTransformComponent::getJointList() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getJointList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetJointList();
}

b2ContactEdge* Comp2D::Components::PhysicsTransformComponent::getContactList()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getContactList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetContactList();
}

const b2ContactEdge* Comp2D::Components::PhysicsTransformComponent::getContactList() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getContactList\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetContactList();
}

b2Body* Comp2D::Components::PhysicsTransformComponent::getNext()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getNext\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetNext();
}

const b2Body* Comp2D::Components::PhysicsTransformComponent::getNext() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getNext\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetNext();
}

b2World* Comp2D::Components::PhysicsTransformComponent::getWorld()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) getWorld\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetWorld();
}

const b2World* Comp2D::Components::PhysicsTransformComponent::getWorld() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"PhysicsTransformComponent with ID %u (From GameObject with ID %u named %s) const getWorld\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_body->GetWorld();
}
