/* GraphicsSettings.h -- 'Comp2D' Game Engine 'GraphicsSettings' class header file
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

#ifndef Comp2D_HEADERS_SETTINGS_GRAPHICSSETTINGS_H_
#define Comp2D_HEADERS_SETTINGS_GRAPHICSSETTINGS_H_

#include <SDL.h>

// TODO: Alterar tamanho da janela em outra classe, que altera o
//		 Game::GraphicsSettings antes de redimensionar a tela

#define DEFAULT_SCREEN_WIDTH 720
#define DEFAULT_SCREEN_HEIGHT 480

namespace Comp2D
{
	namespace Settings
	{
		class GraphicsSettings
		{
		private:
			int m_screenWidth;
			int m_screenHeight;
			int m_screenHalfWidth;
			int m_screenHalfHeight;
			int m_screenHalfHeightPlusOne;
			int m_screenMiddleWidth;
			int m_screenMiddleHeight;

			Uint32 m_rendererFlags;

		public:
			GraphicsSettings();

			~GraphicsSettings();

			void setScreenWidth( int width );
			void setScreenHeight( int height );
			void setScreenDimensions( int width, int height );

			int getScreenWidth() const;
			int getScreenHeight() const;
			int getScreenHalfWidth() const;
			int getScreenHalfHeight() const;
			int getScreenHalfHeightPlusOne() const;
			int getScreenMiddleWidth() const;
			int getScreenMiddleHeight() const;

			Uint32 getRendererFlags() const;
		};
	}
}

#endif /* Comp2D_HEADERS_SETTINGS_GRAPHICSSETTINGS_H_ */
