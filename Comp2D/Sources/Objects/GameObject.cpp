/* GameObject.cpp -- 'Comp2D' Game Engine 'GameObject' class source file
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

#include "Comp2D/Headers/Objects/GameObject.h"

#include <iterator>
#include <list>
#include <string>
#include <vector>

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/GameObjectBehavior.h"
#include "Comp2D/Headers/Components/PhysicsTransformComponent.h"
#include "Comp2D/Headers/Components/ScreenSpaceTransformComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"
#include "Comp2D/Headers/States/GameState.h"

Comp2D::Objects::GameObject::GameObject
(
	bool active,
	bool activeInHierarchy,
	unsigned int id,
	const std::string& name,
	Comp2D::States::GameState* gameState,
	EGameObjectTag tag
)
	:
	m_active( active ),
	m_activeInHierarchy( activeInHierarchy ),
	m_id( id ),
	m_name( name ),
	m_tag( tag ),
	gameState( gameState )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s Constructor body Start\n",
			m_id,
			m_name.c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s Constructor body End\n",
			m_id,
			m_name.c_str()
		);
	#endif
}

Comp2D::Objects::GameObject::~GameObject()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s Destroying\n",
			m_id,
			m_name.c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s Destroyed\n",
			m_id,
			m_name.c_str()
		);
	#endif
}

void Comp2D::Objects::GameObject::setComponentActiveInHierarchy( Comp2D::Components::Component* component, bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setComponentActiveInHierarchy: component with ID %u; activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			component->getID(),
			activeInHierarchy
		);
	#endif

	if( component->isActiveInHierarchy() && !activeInHierarchy )
	{
		component->setActiveInHierarchy( activeInHierarchy );
		//activeInHierarchyComponents.remove( component );
	}
	else if( !component->isActiveInHierarchy() && activeInHierarchy )
	{
		component->setActiveInHierarchy( activeInHierarchy );
		//activeInHierarchyComponents.push_back( component );
	}
}

void Comp2D::Objects::GameObject::setSelfActiveInHierarchy( bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setSelfActiveInHierarchy: activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			activeInHierarchy
		);
	#endif

	m_activeInHierarchy = activeInHierarchy;

	if( transform )
	{
		transform->setActiveInHierarchy( activeInHierarchy );
	}

	for
	(
		std::list<Comp2D::Components::Component*>::iterator it = enabledComponents.begin();
		it != enabledComponents.end();
		++it
	)
	{
		setComponentActiveInHierarchy( *it, activeInHierarchy );
	}

	for
	(
		std::list<GameObject*>::iterator it = activeChildGameObjects.begin();
		it != activeChildGameObjects.end();
		++it
	)
	{
		setChildGameObjectActiveInHierarchy( *it, activeInHierarchy );
	}
}

bool Comp2D::Objects::GameObject::operator==( const GameObject& rhs ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s operator==: rhs with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			rhs.m_id,
			rhs.m_name.c_str()
		);
	#endif

	return m_id == rhs.m_id;
}

bool Comp2D::Objects::GameObject::operator!=( const GameObject& rhs ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s operator!=: rhs with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			rhs.m_id,
			rhs.m_name.c_str()
		);
	#endif

	return !(*this == rhs);
}

void Comp2D::Objects::GameObject::setActive( bool active )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setActive: active = %i\n",
			m_id,
			m_name.c_str(),
			active
		);
	#endif

	m_active = active;
}

void Comp2D::Objects::GameObject::setActiveInHierarchy( bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setActiveInHierarchy: activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			activeInHierarchy
		);
	#endif

	if( (m_activeInHierarchy && !activeInHierarchy) || (!m_activeInHierarchy && activeInHierarchy)  )
	{
		if( parentGameObject )
		{
			parentGameObject->setChildGameObjectActiveInHierarchy( this, activeInHierarchy );
		}
		else
		{
			setSelfActiveInHierarchy( activeInHierarchy );
		}
	}
}

void Comp2D::Objects::GameObject::setChildGameObjectActive( unsigned int id, bool active )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActive: id = %u; active = %i\n",
			m_id,
			m_name.c_str(),
			id,
			active
		);
	#endif

	setChildGameObjectActive( getChildGameObject( id ), active );
}

void Comp2D::Objects::GameObject::setChildGameObjectActive( const std::string& name, bool active )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActive: name = %s; active = %i\n",
			m_id,
			m_name.c_str(),
			name.c_str(),
			active
		);
	#endif

	setChildGameObjectActive( getChildGameObject( name ), active );
}

void Comp2D::Objects::GameObject::setChildGameObjectActive( GameObject* childGameObject, bool active )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActive: childGameObject with ID %u named %s; active = %i\n",
			m_id,
			m_name.c_str(),
			childGameObject->m_id,
			childGameObject->m_name.c_str(),
			active
		);
	#endif

	if( childGameObject->isActive() && !active )
	{
		childGameObject->setActive( active );
		activeChildGameObjects.remove( childGameObject );
	}
	else if( !childGameObject->isActive() && active )
	{
		childGameObject->setActive( active );
		activeChildGameObjects.push_back( childGameObject );
	}
}

void Comp2D::Objects::GameObject::setChildGameObjectActiveInHierarchy( unsigned int id, bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActiveInHierarchy: id = %u; activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			id,
			activeInHierarchy
		);
	#endif

	setChildGameObjectActiveInHierarchy( getChildGameObject( id ), activeInHierarchy );
}

void Comp2D::Objects::GameObject::setChildGameObjectActiveInHierarchy( const std::string& name, bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActiveInHierarchy: name = %s; activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			name.c_str(),
			activeInHierarchy
		);
	#endif

	setChildGameObjectActiveInHierarchy( getChildGameObject( name ), activeInHierarchy );
}

void Comp2D::Objects::GameObject::setChildGameObjectActiveInHierarchy( GameObject* childGameObject, bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setChildGameObjectActiveInHierarchy: childGameObject with ID %u named %s; activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			childGameObject->m_id,
			childGameObject->m_name.c_str(),
			activeInHierarchy
		);
	#endif

	if( childGameObject->m_activeInHierarchy && !activeInHierarchy )
	{
		childGameObject->setSelfActiveInHierarchy( activeInHierarchy );
		//activeInHierarchyChildGameObjects.remove( childGameObject );
	}
	else if( !childGameObject->m_activeInHierarchy && activeInHierarchy )
	{
		childGameObject->setSelfActiveInHierarchy( activeInHierarchy );
		//activeInHierarchyChildGameObjects.push_back( childGameObject );
	}
}

void Comp2D::Objects::GameObject::setComponentEnabled( Comp2D::Components::Component* component, bool enabled )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s setComponentEnabled: component with ID %u; enabled = %i\n",
			m_id,
			m_name.c_str(),
			component->getID(),
			enabled
		);
	#endif

	if( component->isEnabled() && !enabled )
	{
		component->setEnabled( enabled );
		enabledComponents.remove( component );
	}
	else if( !component->isEnabled() && enabled )
	{
		if( !component->isActiveInHierarchy() && m_activeInHierarchy )
		{
			setComponentActiveInHierarchy( component, m_activeInHierarchy );
		}
		component->setEnabled( enabled );
		enabledComponents.push_back( component );
	}
}

void Comp2D::Objects::GameObject::onRotated( float32 rotation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s onRotated: rotation = %f\n",
			m_id,
			m_name.c_str(),
			rotation
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->onRotated( rotation );
			}
		}
	}

	for
	(
		//std::list<GameObject*>::iterator it = activeInHierarchyChildGameObjects.begin();
		//it != activeInHierarchyChildGameObjects.end();
		std::vector<GameObject*>::iterator it = childGameObjects.begin();
		it != childGameObjects.end();
		++it
	)
	{
		GameObject* currentChildGameObject = (*it);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->onRotated( rotation );
		}
	}
}

void Comp2D::Objects::GameObject::onTranslated( b2Vec2 translation )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s onTranslated: translation = ( %f, %f )\n",
			m_id,
			m_name.c_str(),
			translation.x,
			translation.y
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->onTranslated( translation );
			}
		}
	}

	for
	(
		//std::list<GameObject*>::iterator it = activeInHierarchyChildGameObjects.begin();
		//it != activeInHierarchyChildGameObjects.end();
		std::vector<GameObject*>::iterator it = childGameObjects.begin();
		it != childGameObjects.end();
		++it
	)
	{
		GameObject* currentChildGameObject = (*it);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->onTranslated( translation );
		}
	}
}

void Comp2D::Objects::GameObject::beginContact( b2Contact* contact, GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s beginContact: otherGameObject with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			otherGameObject->m_id,
			otherGameObject->m_name.c_str()
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->beginContact( contact, otherGameObject );
			}
		}
	}

	for
	(
		//std::list<GameObject*>::iterator childGameObjectIt = activeInHierarchyChildGameObjects.begin();
		//childGameObjectIt != activeInHierarchyChildGameObjects.end();
		std::vector<GameObject*>::iterator childGameObjectIt = childGameObjects.begin();
		childGameObjectIt != childGameObjects.end();
		++childGameObjectIt
	)
	{
		GameObject* currentChildGameObject = (*childGameObjectIt);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->beginContact( contact, otherGameObject );
		}
	}
}

void Comp2D::Objects::GameObject::endContact( b2Contact* contact, GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s endContact: otherGameObject with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			otherGameObject->m_id,
			otherGameObject->m_name.c_str()
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->endContact( contact, otherGameObject );
			}
		}
	}

	for
	(
		//std::list<GameObject*>::iterator childGameObjectIt = activeInHierarchyChildGameObjects.begin();
		//childGameObjectIt != activeInHierarchyChildGameObjects.end();
		std::vector<GameObject*>::iterator childGameObjectIt = childGameObjects.begin();
		childGameObjectIt != childGameObjects.end();
		++childGameObjectIt
	)
	{
		GameObject* currentChildGameObject = (*childGameObjectIt);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->endContact( contact, otherGameObject );
		}
	}
}

void Comp2D::Objects::GameObject::postSolve( b2Contact* contact, const b2ContactImpulse* impulse, GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s postSolve: otherGameObject with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			otherGameObject->m_id,
			otherGameObject->m_name.c_str()
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->postSolve( contact, impulse, otherGameObject );
			}
		}
	}

	for
	(
		//std::list<GameObject*>::iterator childGameObjectIt = activeInHierarchyChildGameObjects.begin();
		//childGameObjectIt != activeInHierarchyChildGameObjects.end();
		std::vector<GameObject*>::iterator childGameObjectIt = childGameObjects.begin();
		childGameObjectIt != childGameObjects.end();
		++childGameObjectIt
	)
	{
		GameObject* currentChildGameObject = (*childGameObjectIt);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->postSolve( contact, impulse, otherGameObject );
		}
	}
}

void Comp2D::Objects::GameObject::preSolve( b2Contact* contact, const b2Manifold* oldManifold, GameObject* otherGameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s preSolve: otherGameObject with ID %u named %s\n",
			m_id,
			m_name.c_str(),
			otherGameObject->m_id,
			otherGameObject->m_name.c_str()
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;
	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = activeInHierarchyComponents.begin();
		//it != activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = components.begin();
		it != components.end();
		++it
	)
	{
		Comp2D::Components::Component* currentComponent = *it;

		if
		(
			currentComponent->isEnabled() &&
			currentComponent->isActiveInHierarchy()
		)
		{
			currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

			if( currentBehavior )
			{
				currentBehavior->preSolve( contact, oldManifold, otherGameObject );
			}
		}
	}

	for
	(
		std::vector<GameObject*>::iterator childGameObjectIt = childGameObjects.begin();
		childGameObjectIt != childGameObjects.end();
		++childGameObjectIt
	)
	{
		GameObject* currentChildGameObject = (*childGameObjectIt);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			currentChildGameObject->preSolve( contact, oldManifold, otherGameObject );
		}
	}
}

bool Comp2D::Objects::GameObject::isActive() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s isActive\n",
			m_id,
			m_name.c_str()
		);
		*/
	#endif

	return m_active;
}

bool Comp2D::Objects::GameObject::isActiveInHierarchy() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s isActiveInHierarchy\n",
			m_id,
			m_name.c_str()
		);
		*/
	#endif

	return m_activeInHierarchy;
}

unsigned int  Comp2D::Objects::GameObject::getID() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getID\n",
			m_id,
			m_name.c_str()
		);
		*/
	#endif

	return m_id;
}

const std::string& Comp2D::Objects::GameObject::getName() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getName\n",
			m_id,
			m_name.c_str()
		);
		*/
	#endif

	return m_name;
}

Comp2D::Objects::EGameObjectTag Comp2D::Objects::GameObject::getTag() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getTag\n",
			m_id,
			m_name.c_str()
		);
		*/
	#endif

	return m_tag;
}

Comp2D::Components::Component* Comp2D::Objects::GameObject::addComponent( Comp2D::Components::Component* component, /*bool active,*/ bool enabled )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s addComponent: component with ID %u; m_activeInHierarchy = %i; enabled = %i\n",
			m_id,
			m_name.c_str(),
			component->getID(),
			m_activeInHierarchy,
			enabled
		);
	#endif

	if( !component->executedOnInstantiated() )
	{
		component->onInstantiated();
	}

	components.push_back( component );

	if( m_activeInHierarchy )
	{
		component->setActiveInHierarchy( m_activeInHierarchy );
		//activeInHierarchyComponents.push_back( component );
	}

	if( enabled )
	{
		component->setEnabled( enabled );
		enabledComponents.push_back( component );
	}

	return component;
}

Comp2D::Components::Component* Comp2D::Objects::GameObject::getComponent( unsigned int id ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getComponent: id = %u\n",
			m_id,
			m_name.c_str(),
			id
		);
	#endif

	Comp2D::Components::Component* currentComponent = nullptr;

	for( unsigned int i = 0; i < components.size(); ++i )
	{
		currentComponent = components[i];

		if( currentComponent->getID() == id )
		{
			return currentComponent;
		}
	}

	return nullptr;
}

Comp2D::Components::Component* Comp2D::Objects::GameObject::removeComponent( unsigned int id )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s removeComponent: id = %u\n",
			m_id,
			m_name.c_str(),
			id
		);
	#endif

	Comp2D::Components::Component* removedComponent = nullptr;

	for( unsigned int i = 0; i < components.size(); ++i )
	{
		if( components[i]->getID() == id )
		{
			removedComponent = components[i];

			components.erase( components.begin() + i );

			if( removedComponent->isActiveInHierarchy() )
			{
				//activeInHierarchyComponents.remove( removedComponent );
			}

			if( removedComponent->isEnabled() )
			{
				enabledComponents.remove( removedComponent );
			}

			// TODO: ADICIONAR CÓDIGO PARA DELEÇÃO ADEQUADA
			delete removedComponent;
		}
	}

	return removedComponent;
}

Comp2D::Components::Component* Comp2D::Objects::GameObject::removeComponent( Comp2D::Components::Component* component )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s removeComponent: component with ID %u\n",
			m_id,
			m_name.c_str(),
			component->getID()
		);
	#endif

	for( unsigned int i = 0; i < components.size(); ++i )
	{
		if( components[i]->getID() == component->getID() )
		{
			Comp2D::Components::Component* removedComponent = components[i];

			components.erase( components.begin() + i );

			if( removedComponent->isActiveInHierarchy() )
			{
				//activeInHierarchyComponents.remove( removedComponent );
			}

			if( removedComponent->isEnabled() )
			{
				enabledComponents.remove( removedComponent );
			}

			// TODO: ADICIONAR CÓDIGO PARA DELEÇÃO ADEQUADA
			delete removedComponent;
		}
	}

	return component;
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::addChildGameObject( GameObject* childGameObject, bool active, bool activeInHierarchy )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s addChildGameObject: childGameObject with ID %u named %s; active = %i; activeInHierarchy = %i\n",
			m_id,
			m_name.c_str(),
			childGameObject->m_id,
			childGameObject->m_name.c_str(),
			active,
			activeInHierarchy
		);
	#endif

	childGameObject->parentGameObject = this;
	childGameObjects.push_back( childGameObject );

	childGameObject->setActive( active );
	if( active )
	{
		activeChildGameObjects.push_back( childGameObject );
	}

	childGameObject->setSelfActiveInHierarchy( activeInHierarchy );
	/*
	if( activeInHierarchy )
	{
		activeInHierarchyChildGameObjects.push_back( childGameObject );
	}
	*/

	return childGameObject;
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::getChildGameObject( unsigned int id ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getChildGameObject: id = %u\n",
			m_id,
			m_name.c_str(),
			id
		);
	#endif

	GameObject* currentGameObject = nullptr;

	for( unsigned int i = 0; i < childGameObjects.size(); ++i )
	{
		currentGameObject = childGameObjects[i];

		if( currentGameObject->m_id == id )
		{
			return currentGameObject;
		}
	}

	return nullptr;
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::getChildGameObject( const std::string& name ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s getChildGameObject: name = %s\n",
			m_id,
			m_name.c_str(),
			name.c_str()
		);
	#endif

	GameObject* currentGameObject = nullptr;

	for( unsigned int i = 0; i < childGameObjects.size(); ++i )
	{
		currentGameObject = childGameObjects[i];

		if(  currentGameObject->m_name.compare( name ) == 0 )
		{
			return currentGameObject;
		}
	}

	return nullptr;
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::removeChildGameObject( unsigned int id, bool deleteChildGameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s removeChildGameObject: id = %u; deleteChildGameObject = %i\n",
			m_id,
			m_name.c_str(),
			id,
			deleteChildGameObject
		);
	#endif

	return removeChildGameObject( getChildGameObject( id ), deleteChildGameObject );
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::removeChildGameObject( const std::string& name, bool deleteChildGameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s removeChildGameObject: name = %s; deleteChildGameObject = %i\n",
			m_id,
			m_name.c_str(),
			name.c_str(),
			deleteChildGameObject
		);
	#endif

	return removeChildGameObject( getChildGameObject( name ), deleteChildGameObject );
}

Comp2D::Objects::GameObject* Comp2D::Objects::GameObject::removeChildGameObject( GameObject* childGameObject, bool deleteChildGameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameObject with ID %u named %s removeChildGameObject: childGameObject with ID %u named %s; deleteChildGameObject = %i\n",
			m_id,
			m_name.c_str(),
			childGameObject->getID(),
			childGameObject->m_name.c_str(),
			deleteChildGameObject
		);
	#endif

	return childGameObject;
}
