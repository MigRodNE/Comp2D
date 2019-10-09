/* Component.h -- 'Comp2D' Game Engine 'Component' class header file
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

#ifndef Comp2D_HEADERS_COMPONENTS_COMPONENT_H_
#define Comp2D_HEADERS_COMPONENTS_COMPONENT_H_

#include "Comp2D/Headers/Objects/GameObject.h"

namespace Comp2D
{
	namespace Components
	{
		class Component
		{
		protected:
			bool m_activeInHierarchy;
			bool m_enabled;
			bool m_executedOnInstantiated;

			unsigned int m_id;

		public:
			Comp2D::Objects::GameObject* gameObject;

			Component
			(
				unsigned int id,
				Comp2D::Objects::GameObject* gameObject
			);

			virtual ~Component();

			bool operator==( const Component& rhs ) const;

			bool operator!=( const Component& rhs ) const;

			virtual void debugLogComponentData() const = 0;

			virtual void onActivateInHierarchy() = 0;
			virtual void onDeactivateInHierarchy() = 0;
			virtual void onDelete() = 0;
			virtual void onDisable() = 0;
			virtual void onEnable() = 0;
			virtual void onFinalizeState() = 0;
			virtual void onInitializeState() = 0;
			virtual void onInstantiated() = 0;
			virtual void onPaused() = 0;
			virtual void onUnpaused() = 0;

			void setActiveInHierarchy( bool activeInHierarchy );
			void setEnabled( bool enabled );

			bool executedOnInstantiated() const;
			bool isActiveInHierarchy() const;
			bool isEnabled() const;

			unsigned int getID() const;
		};
	}
}

#endif /* Comp2D_HEADERS_COMPONENTS_COMPONENT_H_ */
