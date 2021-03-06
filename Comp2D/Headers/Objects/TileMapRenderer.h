/* TileMapRenderer.h -- 'Comp2D' Game Engine 'TileMapRenderer' class header file
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

#ifndef Comp2D_HEADERS_OBJECTS_TILEMAPRENDERER_H_
#define Comp2D_HEADERS_OBJECTS_TILEMAPRENDERER_H_

#include <string>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameState.h"

namespace Comp2D
{
	namespace Objects
	{
		class TileMapRenderer : public GameObject
		{
		public:
			TileMapRenderer
			(
				bool active,
				bool activeInHierarchy,
				unsigned int id,
				const std::string& name,
				Comp2D::States::GameState* gameState,
				unsigned int& componentID,
				const std::string& tileIndexMapResourceName,
				const std::string& tileSetTextureResourceName,
				unsigned int tileSetColumnCount = 1,
				unsigned int tileSetLineCount = 1,
				int tileSetTileSize = 16,
				const b2Vec2& localPosition = { 0.0f, 0.0f }
			);

			~TileMapRenderer();
		};
	}
}

#endif /* Comp2D_HEADERS_OBJECTS_TILEMAPRENDERER_H_ */
