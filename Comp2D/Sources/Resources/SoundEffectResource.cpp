/* SoundEffectResource.cpp -- 'Comp2D' Game Engine 'SoundEffectResource' class source file
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

#include "Comp2D/Headers/Resources/SoundEffectResource.h"

#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Resources/Resource.h"

Comp2D::Resources::SoundEffectResource::SoundEffectResource
(
	const std::string&  soundEffectResourceName,
	const std::string&  soundEffectFilePath
)
	:
	FileResource( soundEffectResourceName, soundEffectFilePath )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s Constructor body Start\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Resources::SoundEffectResource::~SoundEffectResource()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s Destroying\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s Destroyed\n", m_name.c_str() );
	#endif
}

void Comp2D::Resources::SoundEffectResource::load()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s load\n", m_name.c_str() );
	#endif

	m_soundEffect = Mix_LoadWAV( m_filePath.c_str() );

	if( m_soundEffect )
	{
		m_loaded = true;
	}
	else
	{
		#ifdef DEBUG
			SDL_LogError
			(
				SDL_LOG_CATEGORY_APPLICATION,
				"Failed to load sound effect resource: %s! SDL_mixer Error: %s\n",
				m_name.c_str(),
				Mix_GetError()
			);
		#endif

		Comp2D::Game::reportError( "Fatal Error: 008", "Failed to load sound effect resource! SDL_mixer Error: ", Mix_GetError() );
	}
}

void Comp2D::Resources::SoundEffectResource::free()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s free\n", m_name.c_str() );
	#endif

	Mix_FreeChunk( m_soundEffect );
	m_soundEffect = nullptr;
	m_loaded = false;
}

Mix_Chunk* Comp2D::Resources::SoundEffectResource::getSoundEffect() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "SoundEffectResource named %s getSoundEffect\n", m_name.c_str() );
	#endif

	return m_soundEffect;
}


