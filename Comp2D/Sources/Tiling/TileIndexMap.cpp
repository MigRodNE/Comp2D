/* TileIndexMap.cpp -- 'Comp2D' Game Engine 'TileIndexMap' class source file
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

#include "Comp2D/Headers/Tiling/TileIndexMap.h"

#include <SDL.h>

Comp2D::Tiling::TileIndexMap::TileIndexMap
(
	unsigned int columnCount,
	unsigned int lineCount
)
	:
	m_columnCount( columnCount ),
	m_lastLineIndex( lineCount - 1 ),
	m_lineCount( lineCount ),
	m_tileIndexesCount( columnCount * lineCount ),
	m_tileIndexes( nullptr )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s Constructor body Start\n", m_name.c_str() );
	#endif

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s Constructor body End\n", m_name.c_str() );
	#endif
}

Comp2D::Tiling::TileIndexMap::~TileIndexMap()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s Destroying\n", m_name.c_str() );
	#endif

	delete[] m_tileIndexes;

	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s Destroyed\n", m_name.c_str() );
	#endif
}

unsigned int Comp2D::Tiling::TileIndexMap::getColumnCount() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s getColumnCount\n", m_name.c_str() );
	#endif

	return m_columnCount;
}

unsigned int Comp2D::Tiling::TileIndexMap::getLineCount() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s getLineCount\n", m_name.c_str() );
	#endif

	return m_lineCount;
}

unsigned int Comp2D::Tiling::TileIndexMap::getTileIndex
(
	unsigned int columnIndex,
	unsigned int lineIndex
) const
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"TileIndexMap named %s getTileIndex: columnIndex = %u; lineIndex = %u\n",
			m_name.c_str(),
			columnIndex,
			lineIndex
		);
		*/
	#endif

	return m_tileIndexes[ columnIndex + m_lastLineIndex * lineIndex ];
}

unsigned int Comp2D::Tiling::TileIndexMap::getTileIndexesCount() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s getTileIndexesCount\n", m_name.c_str() );
	#endif

	return m_tileIndexesCount;
}

const unsigned int* Comp2D::Tiling::TileIndexMap::getTileIndexes() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s getTileIndexes\n", m_name.c_str() );
	#endif

	return m_tileIndexes;
}

const std::string& Comp2D::Tiling::TileIndexMap::getName() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "TileIndexMap named %s getName\n", m_name.c_str() );
	#endif

	return m_name;
}
