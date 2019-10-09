/* ScreenSpaceTransformComponent.cpp -- 'Comp2D' Game Engine 'ScreenSpaceTransformComponent' class source file
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

#include "Comp2D/Headers/Components/ScreenSpaceTransformComponent.h"

#include <SDL.h>

#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"

#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Utilities/Math.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::ScreenSpaceTransformComponent::ScreenSpaceTransformComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2Vec2 localPosition,
	float32 localRotation,
	b2Vec2 localScale
)
	:
	TransformComponent( id, gameObject, localPosition, localRotation, localScale )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u localPosition = ( %f, %f )\n", m_id, localPosition.x, localPosition.y );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u localRotation = %f\n", m_id, localRotation );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u localScale = ( %f, %f )\n", m_id, localScale.x, localScale.y );
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::ScreenSpaceTransformComponent::~ScreenSpaceTransformComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::updateTransform()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) updateTransform\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if
	(
		gameObject->parentGameObject != nullptr &&
		gameObject->parentGameObject->transform != nullptr
	)
	{
		float32 cosWorldRotationAngle = 0.0f;
		float32 sinWorldRotationAngle = 0.0f;

		b2Vec2 newLocalPosition;
		b2Vec2 parentGameObjectWorldPosition;

		m_worldRotation = gameObject->parentGameObject->transform->getWorldRotation() + m_localRotation;

		b2Vec2 parentGameObjectWorldScale = gameObject->parentGameObject->transform->getWorldScale();
		m_worldScale.x = parentGameObjectWorldScale.x * m_localScale.x;
		m_worldScale.y = parentGameObjectWorldScale.y * m_localScale.y;

		newLocalPosition = b2Vec2
		(
			m_localPosition.x * parentGameObjectWorldScale.x,
			m_localPosition.y * parentGameObjectWorldScale.y
		);

		Comp2D::Utilities::Vector2D<int> parentGameObjectScreenPos = gameObject->parentGameObject->transform->getScreenPosition();
		parentGameObjectWorldPosition = b2Vec2( static_cast<float32>( parentGameObjectScreenPos.x ), static_cast<float32>( parentGameObjectScreenPos.y ) );

		float32 parentGameObjectWorldRotationInRadians = gameObject->parentGameObject->transform->getWorldRotationInRadians();
		cosWorldRotationAngle = static_cast<float32>
		(
			cos( parentGameObjectWorldRotationInRadians )
		);
		sinWorldRotationAngle = static_cast<float32>
		(
			sin( parentGameObjectWorldRotationInRadians )
		);

		b2Mat22 inverseRotationMatrix = b2Mat22
		(
			cosWorldRotationAngle,
			sinWorldRotationAngle,
			-sinWorldRotationAngle,
			cosWorldRotationAngle
		);
		newLocalPosition = b2Mul( inverseRotationMatrix, newLocalPosition );

		m_worldPosition = parentGameObjectWorldPosition + newLocalPosition;
	}
	else
	{
		m_worldPosition = m_localPosition;
		m_worldRotation = m_localRotation;
		m_worldScale = m_localScale;
	}
}

void Comp2D::Components::ScreenSpaceTransformComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u m_active = %i\n", m_id, m_activeInHierarchy );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u m_enabled = %i\n", m_id, m_enabled );

		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u gameObject Address = %p\n", m_id, gameObject );
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ScreenSpaceTransformComponent with ID %u gameObject with ID %u\n", m_id, gameObject->getID() );

		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_localPosition = ( %f, %f )\n",
			m_id,
			m_localPosition.x,
			m_localPosition.y
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_localRotation = %f degrees\n",
			m_id,
			m_localRotation
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_localScale = ( %f, %f )\n",
			m_id,
			m_localScale.x,
			m_localScale.y
		);

		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_worldPosition = ( %f, %f )\n",
			m_id,
			m_worldPosition.x,
			m_worldPosition.y
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_worldRotation = %f degrees\n",
			m_id,
			m_worldRotation
		);
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u m_worldScale = ( %f, %f )\n",
			m_id,
			m_worldScale.x,
			m_worldScale.y
		);

		Comp2D::Utilities::Vector2D<int> screenPosition = getScreenPosition();
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u screenPosition = ( %i, %i )\n",
			m_id,
			screenPosition.x,
			screenPosition.y
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::ScreenSpaceTransformComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::ScreenSpaceTransformComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

b2Vec2 Comp2D::Components::ScreenSpaceTransformComponent::getPhysicsWorldPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) getPhysicsWorldPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return Comp2D::Components::TransformComponent::getPhysicsWorldPosition( m_worldPosition );
}

Comp2D::Utilities::Vector2D<int> Comp2D::Components::ScreenSpaceTransformComponent::getScreenPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ScreenSpaceTransformComponent with ID %u (From GameObject with ID %u named %s) getScreenPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	int screenX = static_cast<int>( round( m_worldPosition.x - Comp2D::Game::getCameraPositionX() ) );
	int screenY = static_cast<int>( round( m_worldPosition.y - Comp2D::Game::getCameraPositionY() ) );

	return Comp2D::Utilities::Vector2D<int>( screenX, screenY );
}
