/* TextureResource.cpp -- 'Comp2D' Game Engine 'TextureResource' class source file
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

#include "Comp2D/Headers/Resources/TextureResource.h"

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Resources/FileResource.h"

Comp2D::Resources::TextureResource::TextureResource
(
	const std::string&  textureResourceName,
	const std::string&  textureFilePath
)
	:
	FileResource( textureResourceName, textureFilePath ),
	m_modColor{ 255, 255, 255, 255 }
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s Constructor body Start\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Resources::TextureResource::~TextureResource()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s Destroying\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s Destroyed\n", m_name.c_str() );
	#endif
}

void Comp2D::Resources::TextureResource::load()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s load\n", m_name.c_str() );
	#endif

	SDL_Surface* loadedSurface = IMG_Load( m_filePath.c_str() );

	if( loadedSurface )
	{
		m_width = loadedSurface->w;
		m_height = loadedSurface->h;

		SDL_SetSurfaceColorMod( loadedSurface, m_modColor.r, m_modColor.g, m_modColor.b );

		SDL_SetSurfaceBlendMode( loadedSurface, SDL_BLENDMODE_BLEND );

		m_texture = SDL_CreateTextureFromSurface( Comp2D::Game::renderer, loadedSurface );

		if( m_texture )
		{
			SDL_SetTextureBlendMode( m_texture, SDL_BLENDMODE_BLEND );

			m_loaded = true;
		}
		else
		{
			#ifdef DEBUG
				SDL_LogError
				(
					SDL_LOG_CATEGORY_APPLICATION,
					"Unable to create texture from %s! SDL Error: %s\n",
					m_filePath.c_str(),
					SDL_GetError()
				);
			#endif

			Comp2D::Game::reportError( "Fatal Error: 010", "Unable to create texture! SDL Error: ", SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}
	else
	{
		#ifdef DEBUG
			SDL_LogError
			(
				SDL_LOG_CATEGORY_APPLICATION,
				"Unable to load image %s! SDL_image Error: %s\n",
				m_filePath.c_str(),
				IMG_GetError()
			);
		#endif

		Comp2D::Game::reportError( "Fatal Error: 009", "Unable to load image! SDL_image Error: ", IMG_GetError() );
	}
}

void Comp2D::Resources::TextureResource::free()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s free\n", m_name.c_str() );
	#endif

	SDL_DestroyTexture( m_texture );

	m_texture = nullptr;

	m_loaded = false;
}

void Comp2D::Resources::TextureResource::setModColor( Uint8 r, Uint8 g, Uint8 b )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s setModColor: r = %u; g = %u; b = %u\n", m_name.c_str(), r, g, b );
	#endif

	if
	(
		m_modColor.r != r ||
		m_modColor.g != g ||
		m_modColor.b != b
	)
	{
		m_modColor.r = r;
		m_modColor.g = g;
		m_modColor.b = b;

		if( isLoaded() )
		{
			free();
			load();
		}
	}
}

int Comp2D::Resources::TextureResource::getWidth() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s getWidth\n", m_name.c_str() );
	#endif

	return m_width;
}

int Comp2D::Resources::TextureResource::getHeight() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s getHeight\n", m_name.c_str() );
	#endif

	return m_height;
}

const SDL_Color& Comp2D::Resources::TextureResource::getModColor() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s getModColor\n", m_name.c_str() );
	#endif

	return m_modColor;
}

SDL_Texture* Comp2D::Resources::TextureResource::getTexture() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TextureResource named %s getTexture\n", m_name.c_str() );
	#endif

	return m_texture;
}
