/* GraphicsSettings.cpp -- 'Comp2D' Game Engine 'GraphicsSettings' class source file
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

#include "Comp2D/Headers/Settings/GraphicsSettings.h"

#include <SDL.h>

Comp2D::Settings::GraphicsSettings::GraphicsSettings()
	:
	m_rendererFlags
	{
		SDL_RENDERER_ACCELERATED
		//| SDL_RENDERER_PRESENTVSYNC
	}
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings Constructor body Start\n" );
	#endif

	setScreenDimensions( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings Constructor body End\n" );
	#endif
}

Comp2D::Settings::GraphicsSettings::~GraphicsSettings()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings Destroyed\n" );
	#endif
}

void Comp2D::Settings::GraphicsSettings::setScreenWidth( int width )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings setScreenWidth: width = %i\n", width );
	#endif

	if( width > 0 )
	{
		m_screenWidth = width;
	}
	else
	{
		m_screenWidth = DEFAULT_SCREEN_WIDTH;
	}

	m_screenHalfWidth = m_screenWidth / 2;
	if( ( m_screenWidth % 2 ) == 0 )
	{
		m_screenMiddleWidth = m_screenHalfWidth - 1;
	}
	else
	{
		m_screenMiddleWidth = m_screenHalfWidth;
	}
}

void Comp2D::Settings::GraphicsSettings::setScreenHeight( int height )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings setScreenHeight: height = %i\n", height );
	#endif

	if( height > 0 )
	{
		m_screenHeight = height;
	}
	else
	{
		m_screenHeight = DEFAULT_SCREEN_HEIGHT;
	}

	m_screenHalfHeight = m_screenHeight / 2;
	m_screenHalfHeightPlusOne = m_screenHalfHeight + 1;
	if( ( m_screenHeight % 2 ) == 0 )
	{
		m_screenMiddleHeight = m_screenHalfHeight - 1;
	}
	else
	{
		m_screenMiddleHeight = m_screenHalfHeight;
	}
}

void Comp2D::Settings::GraphicsSettings::setScreenDimensions( int width, int height )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings setScreenDimensions: width = %i; height = %i\n", width, height );
	#endif

	setScreenWidth( width );
	setScreenHeight( height );
}

int Comp2D::Settings::GraphicsSettings::getScreenWidth() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenWidth\n" );
	#endif

	return m_screenWidth;
}

int Comp2D::Settings::GraphicsSettings::getScreenHeight() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenHeight\n" );
	#endif

	return m_screenHeight;
}

int Comp2D::Settings::GraphicsSettings::getScreenHalfWidth() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenHalfWidth\n" );
	#endif

	return m_screenHalfWidth;
}

int Comp2D::Settings::GraphicsSettings::getScreenHalfHeight() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenHalfHeight\n" );
	#endif

	return m_screenHalfHeight;
}

int Comp2D::Settings::GraphicsSettings::getScreenHalfHeightPlusOne() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenHalfHeightPlusOne\n" );
	#endif

	return m_screenHalfHeightPlusOne;
}

int Comp2D::Settings::GraphicsSettings::getScreenMiddleWidth() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenMiddleWidth\n" );
	#endif

	return m_screenMiddleWidth;
}

int Comp2D::Settings::GraphicsSettings::getScreenMiddleHeight() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getScreenMiddleHeight\n" );
	#endif

	return m_screenMiddleHeight;
}

Uint32 Comp2D::Settings::GraphicsSettings::getRendererFlags() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GraphicsSettings getRendererFlags\n" );
	#endif

	return m_rendererFlags;
}
