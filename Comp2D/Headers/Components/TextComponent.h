/* TextComponent.h -- 'Comp2D' Game Engine 'TextComponent' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_TEXTCOMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_TEXTCOMPONENT_H_

#include <string>

#include <SDL.h>

#include "Comp2D/Headers/Components/GraphicsComponent.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Resources/FontResource.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

// TODO: Lidar com ativação/desativação de TextComponent
// TODO: Lidar com enable/disable de TextComponent
// TODO: (OPCIONAL) Incluir Flipstate e Pivot point
// TODO: (OPCIONAL) Incluir Alignment
// TODO: (OPCIONAL) Incluir Style (Bold, Italic)

namespace Comp2D
{
	namespace Components
	{
		class TextComponent : public GraphicsComponent
		{
		private:
			std::string m_text;

			Comp2D::Utilities::Vector2D<int> m_screenPositionOffset;

			SDL_Rect m_renderedTextRect;

			SDL_Color m_color;

			SDL_Surface* m_renderedTextSurface = nullptr;

			SDL_Texture* m_renderedTextTexture = nullptr;

			void renderTextTexture();

		public:
			TextComponent
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject,
				const std::string& text,
				SDL_Color color = { 255, 255, 255, 255 },
				Comp2D::Resources::FontResource* resource = nullptr
			);

			~TextComponent();

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

			Comp2D::Resources::FontResource* getResource() const override;

			void setColor( SDL_Color color );
			void setFontPointSize( int pointSize );
			void setScreenPositionOffset( Comp2D::Utilities::Vector2D<int> screenPositionOffset );
			void setText( const std::string& text );

			std::string getText() const;

			Comp2D::Utilities::Vector2D<int> getScreenPositionOffset() const;

			SDL_Rect getRenderedTextRect() const;

			SDL_Color getColor() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_TEXTCOMPONENT_H_ */
