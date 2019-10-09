/* GameSettings.cpp -- 'Comp2D' Game Engine 'GameSettings' class source file
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

#include "Comp2D/Headers/Settings/GameSettings.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Comp2D/Headers/Settings/AudioSettings.h"
#include "Comp2D/Headers/Settings/GraphicsSettings.h"

Comp2D::Settings::GameSettings::GameSettings()
	:
	m_imageLoadingFlags{ IMG_INIT_PNG },
	m_windowInitXPos{ SDL_WINDOWPOS_UNDEFINED },
	m_windowInitYPos{ SDL_WINDOWPOS_UNDEFINED },
	m_windowFlags{ SDL_WINDOW_SHOWN },
	m_windowTitle{ "Comp2D Game" }
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings Constructor body End\n" );
	#endif
}

Comp2D::Settings::GameSettings::~GameSettings()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings Destroyed\n" );
	#endif
}

int Comp2D::Settings::GameSettings::getImageLoadingFlags() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings getImageLoadingFlags\n" );
	#endif

	return m_imageLoadingFlags;
}

int Comp2D::Settings::GameSettings::getWindowInitXPos() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings getWindowInitXPos\n" );
	#endif

	return m_windowInitXPos;
}

int Comp2D::Settings::GameSettings::getWindowInitYPos() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings getWindowInitYPos\n" );
	#endif

	return m_windowInitYPos;
}

Uint32 Comp2D::Settings::GameSettings::getWindowFlags() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings getWindowFlags\n" );
	#endif

	return m_windowFlags;
}

const std::string& Comp2D::Settings::GameSettings::getWindowTitle() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameSettings getWindowTitle\n" );
	#endif

	return m_windowTitle;
}
