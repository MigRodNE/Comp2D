/* GenericResource.h -- 'Comp2D' Game Engine 'GenericResource' class header file
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

#ifndef Comp2D_HEADERS_RESOURCES_GENERICRESOURCE_H_
#define Comp2D_HEADERS_RESOURCES_GENERICRESOURCE_H_

#include <string>

#include <SDL.h>

#include "Comp2D/Headers/Resources/Resource.h"

namespace Comp2D
{
	namespace Resources
	{
		template <class T>
		class GenericResource : public Resource
		{
		protected:
			T* m_genericResource = nullptr;

		public:
			GenericResource( const std::string& genericResourceName )
				:
				Resource( genericResourceName )
			{
				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s Constructor body Start\n", m_name.c_str() );
				#endif

				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s Constructor body End\n", m_name.c_str() );
				#endif
			}

			virtual ~GenericResource()
			{
				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s Destroying\n", m_name.c_str() );
				#endif

				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s Destroyed\n", m_name.c_str() );
				#endif
			}

			void load() override
			{
				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s load\n", m_name.c_str() );
				#endif

				m_genericResource = new T();

				m_loaded = true;
			}

			void free() override
			{
				#ifdef DEBUG
					SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s free\n", m_name.c_str() );
				#endif

				delete m_genericResource;
				m_genericResource = nullptr;

				m_loaded = false;
			}

			T* getGenericResource() const
			{
				#ifdef DEBUG
					//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GenericResource named %s getGenericResource\n", m_name.c_str() );
				#endif

				return m_genericResource;
			}
		};
	}
}

#endif /* Comp2D_HEADERS_RESOURCES_GENERICRESOURCE_H_ */
