/* TileSetComponent.h -- 'Comp2D' Game Engine 'TileSetComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_TILESETCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_TILESETCOMPONENT_H_

#include <SDL.h>

#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/TextureResource.h"

namespace Comp2D
{
	namespace Components
	{
		class TileSetComponent : public ResourceComponent
		{
		private:
			unsigned int m_columnCount;
			unsigned int m_lineCount;

			int m_tileSize;

			SDL_Rect m_tileRect;
			SDL_Rect m_tileScreenRect;

			SDL_Texture* m_texture;

		public:
			TileSetComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				unsigned int columnCount = 1,
				unsigned int lineCount = 1,
				int tileSize = 16,
				Comp2D::Resources::TextureResource* resource = nullptr
			);

			~TileSetComponent();

			void debugLogComponentData() const override;

			void onActivateInHierarchy() override;
			void onDeactivateInHierarchy() override;
			void onDelete() override;
			void onDisable() override;
			void onEnable() override;
			void onFinalizeState() override;
			void onInitializeState() override;
			void onInstantiated() override;
			void onPaused() override;
			void onUnpaused() override;

			void setResource( Comp2D::Resources::Resource* resource ) override;

			void renderTile
			(
				unsigned int tileIndex,
				int tilePositionX,
				int tilePositionY,
				int tileScaledSize
			);

			unsigned int getColumnCount() const;
			unsigned int getLineCount() const;

			int getTileSize() const;

			Comp2D::Resources::TextureResource* getResource() const override;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_TILESETCOMPONENT_H_ */
