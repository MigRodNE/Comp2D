/* TileMapRendererComponent.cpp -- 'Comp2D' Game Engine 'TileMapRendererComponent' class source file
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

#include "Comp2D/Headers/Components/TileMapRendererComponent.h"

#include <cmath>

#include <SDL.h>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/Renderable.h"
#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Components/TileIndexMapComponent.h"
#include "Comp2D/Headers/Components/TileSetComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Settings/GameSettings.h"
#include "Comp2D/Headers/Settings/GraphicsSettings.h"
#include "Comp2D/Headers/Tiling/TileIndexMap.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

Comp2D::Components::TileMapRendererComponent::TileMapRendererComponent
(
	unsigned int id,
	Comp2D::Objects::GameObject* gameObject,
	TileIndexMapComponent* tileIndexMapComponent,
	TileSetComponent* tileSetComponent
)
	:
	Component( id, gameObject ),
	Renderable(),
	m_tileIndexesLineCount( 0 ),
	m_tileIndexesColumnCount( 0 ),
	m_tileIndexesCount( 0 ),
	m_tileSize( 0 ),
	m_tileIndexes( nullptr ),
	m_tileSetComponent( tileSetComponent ),
	m_tileIndexMapComponent( tileIndexMapComponent )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) Constructor body Start\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) Constructor body End\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

Comp2D::Components::TileMapRendererComponent::~TileMapRendererComponent()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) Destroying\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) Destroyed\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::debugLogComponentData() const
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) debugLogComponentData\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onActivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onActivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onDeactivateInHierarchy()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onDeactivateInHierarchy\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onDelete()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onDelete\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onDisable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onDisable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onEnable()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onEnable\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onFinalizeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onFinalizeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onInitializeState()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onInitializeState\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	Comp2D::Tiling::TileIndexMap* tileIndexMap = m_tileIndexMapComponent->getResource()->getGenericResource();

	m_tileIndexesLineCount = tileIndexMap->getLineCount();
	m_tileIndexesColumnCount = tileIndexMap->getColumnCount();
	m_tileIndexesCount = tileIndexMap->getTileIndexesCount();

	m_tileSize = m_tileSetComponent->getTileSize();

	m_tileIndexes = tileIndexMap->getTileIndexes();
}

void Comp2D::Components::TileMapRendererComponent::onInstantiated()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onInstantiated\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
	#endif

	m_executedOnInstantiated = true;
}

void Comp2D::Components::TileMapRendererComponent::onPaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onPaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TileMapRendererComponent::onUnpaused()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) onUnpaused\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif
}

void Comp2D::Components::TileMapRendererComponent::render()
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRendererComponent with ID %u (From GameObject with ID %u named %s) render\n",
			m_id,
			gameObject->getID(),
			gameObject->getName().c_str()
		);
		*/
	#endif

	Comp2D::Utilities::Vector2D<int> cameraScreenPosition = Comp2D::Game::getCameraScreenPosition();
	Comp2D::Utilities::Vector2D<int> tileMapScreenPosition = gameObject->transform->getScreenPosition();

	const int cameraBottomBoundaryPositionY = cameraScreenPosition.y + Comp2D::Game::gameSettings->graphicsSettings.getScreenHeight();
	const int cameraRightBoundaryPositionX = cameraScreenPosition.x + Comp2D::Game::gameSettings->graphicsSettings.getScreenWidth();

	int currentTileBottomBoundaryPositionY;
	int currentTileIndex;
	int currentTileRightBoundaryPositionX;
	int currentTileScreenPositionX;
	int currentTileScreenPositionY;
	int tileScaledSize = static_cast<int>( round( static_cast<float32>( m_tileSize ) * gameObject->transform->getLocalScale().x ) );

	for( unsigned int lineIndex = 0, tileIndex = 0; lineIndex < m_tileIndexesLineCount; ++lineIndex )
	{
		for( unsigned int columnIndex = 0; columnIndex < m_tileIndexesColumnCount; ++columnIndex, ++tileIndex )
		{
			currentTileIndex = m_tileIndexes[tileIndex];

			if( currentTileIndex != 0 )
			{
				currentTileScreenPositionX = tileMapScreenPosition.x + columnIndex * tileScaledSize;
				currentTileRightBoundaryPositionX = currentTileScreenPositionX + tileScaledSize;

				currentTileScreenPositionY = tileMapScreenPosition.y + lineIndex * tileScaledSize;
				currentTileBottomBoundaryPositionY = currentTileScreenPositionY + tileScaledSize;

				if
				(
					currentTileScreenPositionX <= cameraRightBoundaryPositionX &&
					currentTileRightBoundaryPositionX >= cameraScreenPosition.x &&
					currentTileScreenPositionY <= cameraBottomBoundaryPositionY &&
					currentTileBottomBoundaryPositionY >= cameraScreenPosition.y
				)
				{
					m_tileSetComponent->renderTile
					(
						currentTileIndex,
						currentTileScreenPositionX,
						currentTileScreenPositionY,
						tileScaledSize
					);
				}
			}
		}
	}
}
