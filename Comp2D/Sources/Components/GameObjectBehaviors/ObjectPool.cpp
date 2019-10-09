/* ObjectPool.cpp -- 'Comp2D' Game Engine 'ObjectPool' class source file
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

#include "Comp2D/Headers/Components/GameObjectBehaviors/ObjectPool.h"

#include <iterator>
#include <vector>

#include <SDL.h>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/Components/GameObjectBehavior.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"

Comp2D::Components::GameObjectBehaviors::ObjectPool::ObjectPool
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject
)
	:
	GameObjectBehavior( id, gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::GameObjectBehaviors::ObjectPool::~ObjectPool()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::GameObjectBehaviors::ObjectPool::updateGameObjectTransformComponent( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) updateGameObjectTransformComponent: gameObject with ID %u named %s\n",
			m_id,
			this->gameObject->getID(),
			this->gameObject->getName().c_str(),
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	if( gameObject->transform )
	{
		gameObject->transform->updateTransform();
	}

	Comp2D::Objects::GameObject* currentChildGameObject = nullptr;

	for
	(
		std::vector<Comp2D::Objects::GameObject*>::iterator gameObjectIt = gameObject->childGameObjects.begin();
		gameObjectIt != gameObject->childGameObjects.end();
		++gameObjectIt
	)
	{
		currentChildGameObject = (*gameObjectIt);

		if(	currentChildGameObject->isActive() )
		{
			updateGameObjectTransformComponent( currentChildGameObject );
		}
	}
}

Comp2D::Objects::GameObject* Comp2D::Components::GameObjectBehaviors::ObjectPool::getNextAvailable( b2Vec2 position )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"ObjectPool with ID %u (From GameObject with ID %u named %s) getNextAvailable: position = ( %f, %f )\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			position.x,
			position.y
		);
	#endif

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator poolObjectIt = poolObjects.begin();
		poolObjectIt != poolObjects.end();
		++poolObjectIt
	)
	{
		Comp2D::Objects::GameObject* currentPoolGameObject = (*poolObjectIt);

		if( !currentPoolGameObject->isActiveInHierarchy() )
		{
			currentPoolGameObject->setActiveInHierarchy( true );

			currentPoolGameObject->transform->setLocalPosition( position );

			updateGameObjectTransformComponent( currentPoolGameObject );

			return currentPoolGameObject;
		}
	}

	return nullptr;
}
