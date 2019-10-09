/* TileMapRenderer.cpp -- 'Comp2D' Game Engine 'TileMapRenderer' class source file
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

#include "Comp2D/Headers/Objects/TileMapRenderer.h"

#include <string>

#include <SDL.h>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Components/ScreenSpaceTransformComponent.h"
#include "Comp2D/Headers/Components/TileIndexMapComponent.h"
#include "Comp2D/Headers/Components/TileMapRendererComponent.h"
#include "Comp2D/Headers/Components/TileSetComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Resources/ResourcesManager.h"
#include "Comp2D/Headers/Resources/TextureResource.h"
#include "Comp2D/Headers/States/GameState.h"
#include "Comp2D/Headers/Tiling/TileIndexMap.h"

Comp2D::Objects::TileMapRenderer::TileMapRenderer
(
	bool active,
	bool activeInHierarchy,
	unsigned int id,
	const std::string& name,
	Comp2D::States::GameState* gameState,
	unsigned int& componentID,
	const std::string& tileIndexMapResourceName,
	const std::string& tileSetTextureResourceName,
	unsigned int tileSetColumnCount,
	unsigned int tileSetLineCount,
	int tileSetTileSize,
	const b2Vec2& localPosition
)
	:
	GameObject( active, activeInHierarchy, id, name, gameState )
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRenderer with ID %u named %s Constructor body Start\n",
			m_id,
			m_name.c_str()
		);
	#endif

	transform = gameState->createTransformComponent
	(
		new Comp2D::Components::ScreenSpaceTransformComponent
		(
			componentID++,
			this,
			localPosition
		)
	);

	Comp2D::Components::TileIndexMapComponent* tileIndexMapComponent = static_cast<Comp2D::Components::TileIndexMapComponent*>
	(
		gameState->createComponent
		(
			new Comp2D::Components::TileIndexMapComponent
			(
				componentID++,
				this,
				static_cast<Comp2D::Resources::GenericResource<Comp2D::Tiling::TileIndexMap>*>
				(
					Game::resourcesManager->getResource( tileIndexMapResourceName )
				)
			)
		)
	);

	Comp2D::Components::TileSetComponent* tileSetComponent = static_cast<Comp2D::Components::TileSetComponent*>
	(
		gameState->createComponent
		(
			new Comp2D::Components::TileSetComponent
			(
				componentID++,
				this,
				tileSetColumnCount,
				tileSetLineCount,
				tileSetTileSize,
				static_cast<Comp2D::Resources::TextureResource*>( Comp2D::Game::resourcesManager->getResource( tileSetTextureResourceName ) )
			)
		)
	);

	gameState->createComponent
	(
		new Comp2D::Components::TileMapRendererComponent
		(
			componentID++,
			this,
			tileIndexMapComponent,
			tileSetComponent
		)
	);

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRenderer with ID %u named %s Constructor body End\n",
			m_id,
			m_name.c_str()
		);
	#endif
}

Comp2D::Objects::TileMapRenderer::~TileMapRenderer()
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRenderer with ID %u named %s Destroying\n",
			m_id,
			m_name.c_str()
		);
	#endif

	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileMapRenderer with ID %u named %s Destroyed\n",
			m_id,
			m_name.c_str()
		);
	#endif
}
