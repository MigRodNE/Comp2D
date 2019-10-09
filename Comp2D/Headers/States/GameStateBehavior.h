/* GameStateBehavior.h -- 'Comp2D' Game Engine 'GameStateBehavior' class header file
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

#ifndef Comp2D_HEADERS_STATES_GAMESTATEBEHAVIOR_H_
#define Comp2D_HEADERS_STATES_GAMESTATEBEHAVIOR_H_

#include <SDL.h>

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameState.h"

// TODO: Transformar métodos em virtuais puros, após testes

namespace Comp2D
{
	namespace States
	{
		class GameStateBehavior
		{
		protected:
			bool m_enabled;

			unsigned int m_id;

		public:
			Comp2D::States::GameState* gameState;

			GameStateBehavior( unsigned int id );

			virtual ~GameStateBehavior();

			virtual void debugLogComponentData() const;

			virtual void beginContact
			(
				b2Contact* contact,
				Comp2D::Objects::GameObject* gameObjectA,
				Comp2D::Objects::GameObject* gameObjectB
			);
			virtual void endContact
			(
				b2Contact* contact,
				Comp2D::Objects::GameObject* gameObjectA,
				Comp2D::Objects::GameObject* gameObjectB
			);
			virtual void onDelete();
			virtual void onDisable();
			virtual void onEnable();
			virtual void onEvent( SDL_Event e );
			virtual void onFinalizeState();
			virtual void onInitializeState();
			virtual void onInstantiated();
			virtual void onPaused();
			virtual void onUnpaused();
			virtual void postSolve
			(
				b2Contact* contact,
				const b2ContactImpulse* impulse,
				Comp2D::Objects::GameObject* gameObjectA,
				Comp2D::Objects::GameObject* gameObjectB
			);
			virtual void preSolve
			(
				b2Contact* contact,
				const b2Manifold* oldManifold,
				Comp2D::Objects::GameObject* gameObjectA,
				Comp2D::Objects::GameObject* gameObjectB
			);
			virtual void update();

			void setEnabled( bool enabled );

			bool isEnabled() const;

			unsigned int getID() const;
		};
	}
}

#endif /* Comp2D_HEADERS_STATES_GAMESTATEBEHAVIOR_H_ */
