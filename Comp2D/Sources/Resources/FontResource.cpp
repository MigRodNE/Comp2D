/* FontResource.cpp -- 'Comp2D' Game Engine 'FontResource' class source file
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

#include "Comp2D/Headers/Resources/FontResource.h"

#include <string>

#include <SDL_ttf.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Resources/FileResource.h"

Comp2D::Resources::FontResource::FontResource
(
	const std::string&  fontResourceName,
	const std::string&  fontFilePath,
	int pointSize
)
	:
	FileResource( fontResourceName, fontFilePath ),
	m_pointSize{ pointSize }
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s Constructor body Start\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Resources::FontResource::~FontResource()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s Destroying\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s Destroyed\n", m_name.c_str() );
	#endif
}

void Comp2D::Resources::FontResource::load()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s load\n", m_name.c_str() );
	#endif

	m_font = TTF_OpenFont( m_filePath.c_str(), m_pointSize );

	if( m_font )
	{
		m_loaded = true;
	}
	else
	{
		#ifdef DEBUG
			SDL_LogError
			(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load font resource: %s! SDL_ttf Error: %s\n",
				m_name.c_str(),
				TTF_GetError()
			);
		#endif

		Comp2D::Game::reportError( "Fatal Error: 006", "Failed to load font resource! SDL_ttf Error: ", TTF_GetError() );
	}
}

void Comp2D::Resources::FontResource::free()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s free\n", m_name.c_str() );
	#endif

	TTF_CloseFont( m_font );
	m_font = nullptr;
	m_loaded = false;
}

void Comp2D::Resources::FontResource::setPointSize( int pointSize )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s setPointSize: pointSize = %i\n", m_name.c_str(), pointSize );
	#endif

	m_pointSize = pointSize;

	if( m_loaded )
	{
		free();
		load();
	}
}

TTF_Font* Comp2D::Resources::FontResource::getFont() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "FontResource named %s getFont\n", m_name.c_str() );
	#endif

	return m_font;
}
