/* SpriteComponent.h -- 'Comp2D' Game Engine 'SpriteComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_SPRITECOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_SPRITECOMPONENT_H_

#include <SDL.h>

#include "Comp2D/Headers/Components/GraphicsComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/TextureResource.h"

// TODO: Criar atributos para Sort Group e Sort Order
//		 - Criar enum público ESortGroup em que o valor enumerico determina a ordem
//		 (menor renderiza antes)
//		 - Criar int para Sort Order (menor valor renderiza antes)
//		 - getters para ambos
// TODO: Lidar com ativação/desativação de SpriteComponent
// TODO: Lidar com enable/disable de SpriteComponent

namespace Comp2D
{
	namespace Components
	{
		class SpriteComponent : public GraphicsComponent
		{
		private:
			SDL_RendererFlip m_flipState;

			SDL_Point m_pivot;

			SDL_Rect m_spriteRect;

			SDL_Texture* m_texture;

		public:
			SpriteComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				SDL_RendererFlip flipState = SDL_FLIP_NONE,
				SDL_Point pivot = { 0, 0 },
				SDL_Rect spriteRect = { 0, 0, 0, 0 },
				Comp2D::Resources::TextureResource* resource = nullptr
			);

			~SpriteComponent();

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

			void render() override;

			Comp2D::Resources::TextureResource* getResource() const override;

			void setFlipState( SDL_RendererFlip flipState );
			void setModColor( Uint8 r, Uint8 g, Uint8 b );
			void setPivot( SDL_Point pivot );
			void setPivotToCenter();
			void setSpriteRect( SDL_Rect spriteRect );

			SDL_RendererFlip getFlipState() const;

			SDL_Point getPivot() const;

			SDL_Rect getSpriteRect() const;

			const SDL_Color& getModColor() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_SPRITECOMPONENT_H_ */
