/* TransformComponent.cpp -- 'Comp2D' Game Engine 'TransformComponent' class source file
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

#include "Comp2D/Headers/Components/TransformComponent.h"

#include <cmath>

#include <SDL.h>

#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Settings/GameSettings.h"
#include "Comp2D/Headers/Settings/GraphicsSettings.h"
#include "Comp2D/Headers/States/PhysicsGameState.h"
#include "Comp2D/Headers/Utilities/Math.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::TransformComponent::TransformComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	b2Vec2 localPosition,
	float32 localRotation,
	b2Vec2 localScale
)
	:
	Component( id, gameObject ),
	m_localRotation( localRotation ),
	m_worldRotation( localRotation ),
	m_localPosition( localPosition ),
	m_localScale( localScale ),
	m_worldPosition( localPosition ),
	m_worldScale( localScale )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::TransformComponent::~TransformComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

b2Vec2 Comp2D::Components::TransformComponent::getPhysicsWorldPosition( const b2Vec2& screenPosition )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent static getPhysicsWorldPosition: transformPosition = ( %f, %f )\n",
			transformPosition.x,
			transformPosition.y
		);
		*/
	#endif

	float32 b2WorldX = Comp2D::States::PhysicsGameState::scaleFactor *
					   ( screenPosition.x - Comp2D::Game::gameSettings->graphicsSettings.getScreenMiddleWidth() );
	float32 b2WorldY =
	-(
		Comp2D::States::PhysicsGameState::scaleFactor *
		(
			screenPosition.y -
			Comp2D::Game::gameSettings->graphicsSettings.getScreenHeight() +
			Comp2D::Game::gameSettings->graphicsSettings.getScreenHalfHeightPlusOne()
		)
	);

	return b2Vec2( b2WorldX, b2WorldY );
}

Comp2D::Utilities::Vector2D<int> Comp2D::Components::TransformComponent::getScreenPosition( const b2Vec2& physicsWorldPosition )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent static getScreenPosition: worldPosition = ( %f, %f )\n",
			worldPosition.x,
			worldPosition.y
		);
		*/
	#endif

	int screenX = Comp2D::Game::gameSettings->graphicsSettings.getScreenMiddleWidth() +
				  static_cast<int>( round( ( physicsWorldPosition.x / Comp2D::States::PhysicsGameState::scaleFactor ) - Comp2D::Game::getCameraPositionX() ) );
	int screenY = Comp2D::Game::gameSettings->graphicsSettings.getScreenHeight() -
				  Comp2D::Game::gameSettings->graphicsSettings.getScreenHalfHeightPlusOne() -
				  static_cast<int>( round( ( physicsWorldPosition.y / Comp2D::States::PhysicsGameState::scaleFactor ) - Comp2D::Game::getCameraPositionY() ) );

	return Comp2D::Utilities::Vector2D<int>( screenX, screenY );
}

void Comp2D::Components::TransformComponent::setLocalPosition( b2Vec2 position )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setLocalPosition: position = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			position.x,
			position.y
		);
		*/
	#endif

	m_localPosition = position;
	//updateWorldPosition();
}

void Comp2D::Components::TransformComponent::setLocalRotation( float32 rotation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setLocalRotation: rotation = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			rotation
		);
		*/
	#endif

	m_localRotation = rotation /*% 360*/;
	//updateWorldRotation();
}

void Comp2D::Components::TransformComponent::setLocalScale( b2Vec2 scale )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setLocalScale: scale = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			scale.x,
			scale.y
		);
		*/
	#endif

	m_localScale = scale;
	//updateWorldScale();
}

void Comp2D::Components::TransformComponent::setWorldPosition( b2Vec2 position )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setWorldPosition: position = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			position.x,
			position.y
		);
		*/
	#endif

	m_worldPosition = position;
	//updateLocalPosition();
}

void Comp2D::Components::TransformComponent::setWorldRotation( float32 rotation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setWorldRotation: rotation = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			rotation
		);
		*/
	#endif

	m_worldRotation = rotation;
	//updateLocalRotation();
}

void Comp2D::Components::TransformComponent::setWorldScale( b2Vec2 scale )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setWorldScale: scale = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			scale.x,
			scale.y
		);
		*/
	#endif

	m_worldScale = scale;
	//updateLocalScale();
}

void Comp2D::Components::TransformComponent::rotate( float32 rotation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) rotate: rotation = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			rotation
		);
		*/
	#endif

	setLocalRotation( m_localRotation + rotation );

	gameObject->onRotated( rotation );
}

void Comp2D::Components::TransformComponent::setLocalPosition( float32 x, float32 y )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setLocalPosition: x = %f; y = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			x,
			y
		);
		*/
	#endif

	setLocalPosition( b2Vec2( x, y ) );
}

void Comp2D::Components::TransformComponent::setLocalScale( float32 x, float32 y )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setLocalScale: x = %f; y = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			x,
			y
		);
		*/
	#endif

	setLocalScale( b2Vec2( x, y ) );
}

void Comp2D::Components::TransformComponent::setWorldPosition( float32 x, float32 y )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setWorldPosition: x = %f; y = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			x,
			y
		);
		*/
	#endif

	setWorldPosition( b2Vec2( x, y ) );
}

void Comp2D::Components::TransformComponent::setWorldScale( float32 x, float32 y )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) setWorldScale: x = %f; y = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			x,
			y
		);
		*/
	#endif

	setWorldScale( b2Vec2( x, y ) );
}

void Comp2D::Components::TransformComponent::translate( b2Vec2 translation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) translate: translation = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			translation.x,
			translation.y
		);
		*/
	#endif

	setLocalPosition( m_localPosition + translation );

	gameObject->onTranslated( translation );
}

void Comp2D::Components::TransformComponent::translate( float32 x, float32 y )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) translate: x = %f; y = %f\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			x,
			y
		);
		*/
	#endif

	translate( b2Vec2( x, y ) );
}

float32 Comp2D::Components::TransformComponent::getLocalRotation() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getLocalRotation\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_localRotation;
}

float32 Comp2D::Components::TransformComponent::getLocalRotationInRadians() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getLocalRotationInRadians\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return getLocalRotation() * Comp2D::Utilities::DEGREE_IN_RAD;
}

/*
float32 Comp2D::Components::TransformComponent::getLocalRotationUpTo360() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getLocalRotationUpTo360\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return getLocalRotation() % 360;
}
*/

float32 Comp2D::Components::TransformComponent::getWorldRotation() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getWorldRotation\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_worldRotation;
}

float32 Comp2D::Components::TransformComponent::getWorldRotationInRadians() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getWorldRotationInRadians\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return getWorldRotation() * Comp2D::Utilities::DEGREE_IN_RAD;
}

/*
float32 Comp2D::Components::TransformComponent::getWorldRotationUpTo360() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getWorldRotationUpTo360\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	return getWorldRotation() % 360;
}
*/

b2Vec2 Comp2D::Components::TransformComponent::getLocalPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getLocalPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_localPosition;
}

b2Vec2 Comp2D::Components::TransformComponent::getLocalScale() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getLocalScale\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_localScale;
}

b2Vec2 Comp2D::Components::TransformComponent::getWorldPosition() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getWorldPosition\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_worldPosition;
}

b2Vec2 Comp2D::Components::TransformComponent::getWorldScale() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TransformComponent with ID %u (From GameObject with ID %u named %s) getWorldScale\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_worldScale;
}
