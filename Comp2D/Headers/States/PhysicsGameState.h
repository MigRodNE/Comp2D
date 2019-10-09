/* PhysicsGameState.h -- 'Comp2D' Game Engine 'PhysicsGameState' class header file
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

#ifndef Comp2D_HEADERS_STATES_PHYSICSGAMESTATE_H_
#define Comp2D_HEADERS_STATES_PHYSICSGAMESTATE_H_

#include <list>

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Common/b2Settings.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/States/GameState.h"

// TODO: Considerar encapsular o atributo estático scaleFactor

namespace Comp2D
{
	namespace States
	{
		class PhysicsEvent;

		class PhysicsGameState : public GameState, public b2ContactListener
		{
		private:
			std::list<PhysicsEvent*> m_physicsEvents;

			void beforeSetup() override;
			void finalize() override;
			void update() override;

			void finalizePhysicsWorld();
			void initializePhysicsWorld();
			void triggerPhysicsEvents();

		protected:
			int32 m_velocityIterations;
			int32 m_positionIterations;

			float32 m_timeStep;

			b2Vec2 m_gravity;

		public:
			static float32 scaleFactor;

			b2World* world = nullptr;

			PhysicsGameState
			(
				Uint32 stateID,
				b2Vec2 gravity = b2Vec2( 0.0f, 10.0f ),
				int32 velocityIterations = 8,
				int32 positionIterations = 3,
				float32 timeStep = 1.0f / 60.0f
			);

			virtual ~PhysicsGameState();

			virtual void setup() override;

			void BeginContact( b2Contact* contact ) override;
			void EndContact( b2Contact* contact ) override;
			void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse ) override;
			void PreSolve( b2Contact* contact, const b2Manifold* oldManifold ) override;
		};
	}
}

#endif /* Comp2D_HEADERS_STATES_PHYSICSGAMESTATE_H_ */
