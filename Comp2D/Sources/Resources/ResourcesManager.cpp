/* ResourcesManager.cpp -- 'Comp2D' Game Engine 'ResourcesManager' class source file
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

#include "Comp2D/Headers/Resources/ResourcesManager.h"

#include <iterator>
#include <set>
#include <string>
#include <vector>

#include <SDL.h>

#include "Comp2D/Headers/Resources/FontResource.h"
#include "Comp2D/Headers/Resources/GenericResource.h"
#include "Comp2D/Headers/Resources/MusicResource.h"
#include "Comp2D/Headers/Resources/Resource.h"
#include "Comp2D/Headers/Resources/SoundEffectResource.h"
#include "Comp2D/Headers/Resources/TextureResource.h"

Comp2D::Resources::ResourcesManager::ResourcesManager()
	:
	m_resources
	{
		// Enter Resources HERE
		new FontResource( "Deja Vu Sans Mono Font 12", "Fonts/DejaVuSansMono.ttf", 12 )
	}
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager Constructor body End\n" );
	#endif
}

Comp2D::Resources::ResourcesManager::~ResourcesManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager Destroying\n" );
	#endif

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if( currentResource->isLoaded() )
		{
			currentResource->free();
		}
		delete currentResource;
		currentResource = nullptr;
	}

	m_resources.clear();

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager Destroyed\n" );
	#endif
}

void Comp2D::Resources::ResourcesManager::addResource( Resource* resource, bool loadOnAdd )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager addResource named %s; loadOnAdd = %i\n", resource->getName().c_str(), loadOnAdd );
	#endif

	m_resources.push_back( resource );
	if( loadOnAdd )
	{
		resource->load();
	}
}

Comp2D::Resources::Resource* Comp2D::Resources::ResourcesManager::loadResource
(
	const std::string& resourceName,
	bool appendWithLoaded
)
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager loadResource named %s; appendWithLoaded = %i\n", resourceName.c_str(), appendWithLoaded );
	#endif

	if( !appendWithLoaded )
	{
		freeAllResources();
	}

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if
		(
			!currentResource->isLoaded() &&
			resourceName.compare( currentResource->getName() ) == 0
		)
		{
			currentResource->load();
			return currentResource;
		}
	}

	return nullptr;
}

void Comp2D::Resources::ResourcesManager::loadResources
(
	const std::set<std::string>& resourcesNames,
	bool appendWithLoaded
)
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager loadResources: appendWithLoaded = %i\n", appendWithLoaded );
	#endif

	if( !appendWithLoaded )
	{
		freeAllResources();
	}

	for
	(
		std::set<std::string>::const_iterator resourceNameIt = resourcesNames.cbegin();
		resourceNameIt != resourcesNames.cend();
		++resourceNameIt
	)
	{
		Comp2D::Resources::Resource* currentResource = nullptr;

		for( unsigned int resourceIndex = 0; resourceIndex < m_resources.size(); ++resourceIndex )
		{
			currentResource = m_resources[resourceIndex];

			if
			(
				!currentResource->isLoaded() &&
				(*resourceNameIt).compare( currentResource->getName() ) == 0
			)
			{
				//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager Loading Resource named %s", (*resourceNameIt).c_str() );

				currentResource->load();
				break;
			}
		}
	}
}

void Comp2D::Resources::ResourcesManager::loadAllResources()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager loadAllResources\n" );
	#endif

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if( !currentResource->isLoaded() )
		{
			currentResource->load();
		}
	}
}

void Comp2D::Resources::ResourcesManager::freeResource( const std::string& resourceName )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager freeResource named %s\n", resourceName.c_str() );
	#endif

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if
		(
			currentResource->isLoaded() &&
			resourceName.compare( currentResource->getName() ) == 0
		)
		{
			currentResource->free();
			break;
		}
	}
}

void Comp2D::Resources::ResourcesManager::freeResources( const std::set<std::string>& resourcesNames )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager freeResources\n" );
	#endif

	for
	(
		std::set<std::string>::const_reverse_iterator resourceNameReverseIt = resourcesNames.crbegin();
		resourceNameReverseIt != resourcesNames.crend();
		++resourceNameReverseIt
	)
	{
		freeResource( *resourceNameReverseIt );
	}
}

void Comp2D::Resources::ResourcesManager::freeAllResources()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager freeAllResources\n" );
	#endif

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if( currentResource->isLoaded() )
		{
			currentResource->free();
		}
	}
}

Comp2D::Resources::Resource* Comp2D::Resources::ResourcesManager::getResource( const std::string& resourceName ) const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "ResourcesManager getResource named %s\n", resourceName.c_str() );
	#endif

	Comp2D::Resources::Resource* currentResource = nullptr;

	for( unsigned int i = 0; i < m_resources.size(); ++i )
	{
		currentResource = m_resources[i];

		if( resourceName.compare( currentResource->getName() ) == 0 )
		{
			return currentResource;
		}
	}
	return nullptr;
}
