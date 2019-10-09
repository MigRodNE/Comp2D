/* TileSetComponent.cpp -- 'Comp2D' Game Engine 'TileSetComponent' class source file
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

#include "Comp2D/Headers/Components/TileSetComponent.h"

#include <SDL.h>

#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/TextureResource.h"

Comp2D::Components::TileSetComponent::TileSetComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	unsigned int columnCount,
	unsigned int lineCount,
	int tileSize,
	Comp2D::Resources::TextureResource* resource
)
	:
	ResourceComponent( id, gameObject ),
	m_columnCount( columnCount ),
	m_lineCount( lineCount ),
	m_tileSize( tileSize )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_tileRect.w = tileSize;
	m_tileRect.h = tileSize;

	m_tileScreenRect.w = tileSize;
	m_tileScreenRect.h = tileSize;

	setResource( resource );

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::TileSetComponent::~TileSetComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileSetComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_texture = getResource()->getTexture();
}

void Comp2D::Components::TileSetComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::TileSetComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TileSetComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TileSetComponent::setResource( Comp2D::Resources::Resource* resource )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) setResource named %s\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			resource->getName().c_str()
		);
		*/
	#endif

	Comp2D::Resources::TextureResource* textureResource = dynamic_cast<Comp2D::Resources::TextureResource*>( resource );

	if( textureResource )
	{
		m_resource = textureResource;

		if( m_texture )
		{
			m_texture = getResource()->getTexture();
		}
	}
	else
	{
		// TODO: Lançar exceção
	}
}

void Comp2D::Components::TileSetComponent::renderTile
(
	unsigned int tileIndex,
	int tilePositionX,
	int tilePositionY,
	int tileScaledSize
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) renderTile: tileIndex = %u; tilePositionX = %i; tilePositionY = %i\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str(),
			tileIndex,
			tilePositionX,
			tilePositionY
		);
		*/
	#endif

	unsigned int columnIndex = tileIndex % m_columnCount;
	unsigned int lineIndex = tileIndex / m_columnCount;

	m_tileRect.x = static_cast<int>( m_tileSize * columnIndex );
	m_tileRect.y = static_cast<int>( m_tileSize * lineIndex );

	m_tileScreenRect.x = tilePositionX;
	m_tileScreenRect.y = tilePositionY;
	m_tileScreenRect.w = tileScaledSize;
	m_tileScreenRect.h = tileScaledSize;

	SDL_RenderCopy
	(
		Comp2D::Game::renderer,
		m_texture,
		&m_tileRect,
		&m_tileScreenRect
	);
}

unsigned int Comp2D::Components::TileSetComponent::getColumnCount() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) getColumnCount\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_columnCount;
}

unsigned int Comp2D::Components::TileSetComponent::getLineCount() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) getLineCount\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_lineCount;
}

int Comp2D::Components::TileSetComponent::getTileSize() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) getTileSize\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return m_tileSize;
}

Comp2D::Resources::TextureResource* Comp2D::Components::TileSetComponent::getResource() const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileSetComponent with ID %u (From GameObject with ID %u named %s) getResource\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	return static_cast<Comp2D::Resources::TextureResource*>( m_resource );
}
