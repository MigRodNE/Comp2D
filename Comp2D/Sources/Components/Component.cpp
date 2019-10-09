/* Component.cpp -- 'Comp2D' Game Engine 'Component' class source file
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

#include "Comp2D/Headers/Components/Component.h"

#include <SDL.h>

Comp2D::Components::Component::Component
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject
)
	:
	m_activeInHierarchy( false ),
	m_enabled( false ),
	m_executedOnInstantiated( false ),
	m_id( id ),
	gameObject( gameObject )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::Component::~Component()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

bool Comp2D::Components::Component::operator==( const Component& rhs ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) operator==: rhs with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			rhs.m_id
		);
	#endif

	return m_id == rhs.m_id;
}

bool Comp2D::Components::Component::operator!=( const Component& rhs ) const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) operator!=: rhs with ID %u\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			rhs.m_id
		);
	#endif

	return !(*this == rhs);
}

void Comp2D::Components::Component::setActiveInHierarchy( bool activeInHierarchy )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) setActiveInHierarchy: activeInHierarchy = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			activeInHierarchy
		);
		*/
	#endif

	if( !m_activeInHierarchy && activeInHierarchy )
	{
		onActivateInHierarchy();
		m_activeInHierarchy = activeInHierarchy;
	}
	else if( m_activeInHierarchy && !activeInHierarchy )
	{
		onDeactivateInHierarchy();
		m_activeInHierarchy = activeInHierarchy;
	}
}

void Comp2D::Components::Component::setEnabled( bool enabled )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) setEnabled: enabled = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			enabled
		);
		*/
	#endif

	if( !m_enabled && enabled )
	{
		onEnable();
		m_enabled = enabled;
	}
	else if( m_enabled && !enabled )
	{
		onDisable();
		m_enabled = enabled;
	}
}

bool Comp2D::Components::Component::executedOnInstantiated() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) executedOnInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_executedOnInstantiated;
}

bool Comp2D::Components::Component::isActiveInHierarchy() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) isActiveInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_activeInHierarchy;
}

bool Comp2D::Components::Component::isEnabled() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) isEnabled\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_enabled;
}

unsigned int Comp2D::Components::Component::getID() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Component with ID %u (From GameObject with ID %u named %s) getID\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_id;
}
