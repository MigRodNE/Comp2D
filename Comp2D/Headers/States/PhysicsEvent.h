/* PhysicsEvent.h -- 'Comp2D' Game Engine 'PhysicsEvent' class header file
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

#ifndef Comp2D_HEADERS_STATES_PHYSICSEVENT_H_
#define Comp2D_HEADERS_STATES_PHYSICSEVENT_H_

#include <list>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameStateBehavior.h"

namespace Comp2D
{
	namespace States
	{
		class PhysicsEvent
		{
		protected:
			b2Contact* m_contact;

			const b2ContactImpulse* m_impulse;

			const b2Manifold* m_oldManifold;

			Comp2D::Objects::GameObject* m_gameObjectA;
			Comp2D::Objects::GameObject* m_gameObjectB;

			std::list<Comp2D::States::GameStateBehavior*>* m_gameStateBehaviors;

		public:
			PhysicsEvent
			(
				std::list<Comp2D::States::GameStateBehavior*>* gameStateBehaviors,
				Comp2D::Objects::GameObject* gameObjectA,
				Comp2D::Objects::GameObject* gameObjectB,
				b2Contact* contact,
				const b2ContactImpulse* impulse = nullptr,
				const b2Manifold* oldManifold = nullptr
			);

			virtual ~PhysicsEvent();

			virtual void triggerEvent() = 0;
		};
	}
}

#endif /* Comp2D_HEADERS_STATES_PHYSICSEVENT_H_ */
