/* Dependency.h -- 'Comp2D' Game Engine 'Dependency' class header file
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

#ifndef Comp2D_HEADERS_OBJECTS_DEPENDENCY_H_
#define Comp2D_HEADERS_OBJECTS_DEPENDENCY_H_

#include <string>
#include <typeindex>
#include <typeinfo>

// TODO: Encapsular atributos e criar métodos get

namespace Comp2D
{
	namespace Objects
	{
		enum class ERequiredObjectType
		{
			GameObject,
			Component,
			RequiredObjectTypeCount
		};

		class Dependency
		{
		public:
			void** dependentPointerToRequiredObject;

			ERequiredObjectType requiredObjectType;

			unsigned int requiredComponentIndex;

			std::type_index requiredComponentType;

			std::string requiredGameObjectName;

			Dependency
			(
				void** dependentPointerToRequiredObject,
				const std::string& requiredGameObjectName
			);

			Dependency
			(
				void** dependentPointerToRequiredObject,
				const std::string& requiredGameObjectName,
				const std::type_info& requiredComponentType,
				unsigned int requiredComponentIndex = 0
			);

			~Dependency();
		};
	}
}

#endif /* Comp2D_HEADERS_OBJECTS_DEPENDENCY_H_ */
