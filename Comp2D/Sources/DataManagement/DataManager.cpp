/* DataManager.cpp -- 'Comp2D' Game Engine 'DataManager' class source file
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

#include "Comp2D/Headers/DataManagement/DataManager.h"

#include <string>

#include <SDL.h>

Comp2D::DataManagement::DataManager::DataManager()
	:
	m_defaultDataFileName( "saved_game.dat" )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager Constructor body End\n" );
	#endif
}

Comp2D::DataManagement::DataManager::~DataManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager Destroyed\n" );
	#endif
}

void Comp2D::DataManagement::DataManager::setDataToDefaultValues()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager setDataToDefaultValues\n" );
	#endif
}

void Comp2D::DataManagement::DataManager::setDefaultDataFileName(  const std::string& defaultDataFileName  )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager setDefaultDataFileName: defaultDataFileName = %s\n", defaultDataFileName.c_str() );
	#endif

	m_defaultDataFileName = defaultDataFileName;
}

bool Comp2D::DataManagement::DataManager::loadDataFromFile()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager loadDataFromFile\n" );
	#endif

	return loadDataFromFile( m_defaultDataFileName );
}

bool Comp2D::DataManagement::DataManager::loadDataFromFile( const std::string& dataFileName )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager loadDataFromFile: dataFileName = %s\n", dataFileName.c_str() );
	#endif

	SDL_RWops* dataFile = SDL_RWFromFile( dataFileName.c_str(), "r+b" );

	if( dataFile )
	{
		SDL_RWclose( dataFile );

		return true;
	}

	return false;
}

bool Comp2D::DataManagement::DataManager::saveDataOnFile()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager saveDataOnFile\n" );
	#endif

	return saveDataOnFile( m_defaultDataFileName );
}

bool Comp2D::DataManagement::DataManager::saveDataOnFile( const std::string& dataFileName )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager saveDataOnFile: dataFileName = %s\n", dataFileName.c_str() );
	#endif

	SDL_RWops* dataFile = SDL_RWFromFile( dataFileName.c_str(), "w+b" );

	if( dataFile )
	{
		SDL_RWclose( dataFile );

		return true;
	}

	return false;
}

const std::string& Comp2D::DataManagement::DataManager::getDefaultDataFileName() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "DataManager getDefaultDataFileName\n" );
	#endif

	return m_defaultDataFileName;
}
