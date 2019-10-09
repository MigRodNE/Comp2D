/* ResourcesManager.h -- 'Comp2D' Game Engine 'ResourcesManager' class header file
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

#ifndef Comp2D_HEADERS_RESOURCES_RESOURCESMANAGER_H_
#define Comp2D_HEADERS_RESOURCES_RESOURCESMANAGER_H_

#include <set>
#include <string>
#include <vector>

#include "Comp2D/Headers/Resources/Resource.h"

// TODO: Realizar binary search nos métodos de load, free e get Resource

namespace Comp2D
{
	namespace Resources
	{
		class ResourcesManager
		{
		private:
			std::vector<Resource*> m_resources;

		public:
			ResourcesManager();

			~ResourcesManager();

			void addResource( Resource* resource, bool loadOnAdd = false );
			Resource* loadResource( const std::string& resourceName, bool appendWithLoaded = true );
			void loadResources( const std::set<std::string>& resourcesNames, bool appendWithLoaded = true );
			void loadAllResources();
			void freeResource( const std::string& resourceName );
			void freeResources( const std::set<std::string>& resourcesNames );
			void freeAllResources();

			Resource* getResource( const std::string& resourceName ) const;
		};
	}
}

#endif /* Comp2D_HEADERS_RESOURCES_RESOURCESMANAGER_H_ */
