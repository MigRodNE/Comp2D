/* GameState.h -- 'Comp2D' Game Engine 'GameState' class header file
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

#ifndef Comp2D_HEADERS_STATES_GAMESTATE_H_
#define Comp2D_HEADERS_STATES_GAMESTATE_H_

#include <functional>
#include <list>
#include <set>
#include <string>

#include <SDL.h>
#include <SDL_thread.h>

#include "Comp2D/Headers/Game.h"
//#include "Comp2D/Headers/Components/AnimationsControllerComponent.h"
//#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/Renderable.h"
//#include "Comp2D/Headers/Components/TimelinesControllerComponent.h"
#include "Comp2D/Headers/Objects/Dependency.h"
//#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/Time/TimedProcedure.h"

// TODO: Utilizar Binary Search no metodo solveGameObjectComponentDependency
// TODO: (OPCIONAL) Modularizar mais com base nos comentários em GameState.cpp

namespace Comp2D
{
	namespace Components
	{
		class AnimationsControllerComponent;
		class Component;
		class TimelinesControllerComponent;
		class TransformComponent;
	}

	namespace Objects
	{
		class GameObject;
	}

	namespace States
	{
		class GameStateBehavior;
		class LightsGameState;
		class PhysicsGameState;

		class GameState
		{
		private:
			static unsigned int currentGameStateTimedProcedureID;

			static std::list<SDL_TimerID> currentGameStateTimerFunctionsIDs;

			static std::list<SDL_Thread*> currentGameStateSeparateThreadFunctions;

			static std::list<Comp2D::Time::TimedProcedure*> currentGameStateTimedProcedures;
			static std::list<Comp2D::Time::TimedProcedure*> currentGameStatePausableTimedProcedures;

			static void checkGameStateTimedProcedures();
			static void pauseGameStateTimedProcedures();
			static void unpauseGameStateTimedProcedures();

			virtual void beforeSetup();
			virtual void finalize();
			virtual void initialize();
			virtual void onEvent( SDL_Event e );
			virtual void render();
			virtual void update();

			void deleteComponents();
			void deleteGameObjects();
			void deleteGameStateBehaviors();
			void finalizeComponents();
			void finalizeGameSeparateThreadsFunctions();
			void finalizeGameStateBehaviors();
			void finalizeGameStateTimedProcedures();
			void finalizeGameStateTimerFunctions();
			void freeResourcesFromResourceComponents();
			void initializeComponents();
			void initializeGameStateBehaviors();
			void loadResourcesFromAnimationsControllerComponent( Comp2D::Components::AnimationsControllerComponent* animationsControllerComponent );
			void loadResourcesFromResourceComponents();
			void loadResourcesFromTimelinesControllerComponent( Comp2D::Components::TimelinesControllerComponent* timelinesControllerComponent );
			void pause();
			void pauseGameObjectComponents( Comp2D::Objects::GameObject* gameObject );
			void pauseGameObjectsComponents();
			void pauseGameStateBehaviors();
			void solveGameObjectComponentDependency( Comp2D::Objects::Dependency* componentDependency );
			void solveGameObjectComponentsDependencies( Comp2D::Objects::GameObject* gameObject );
			void solveGameObjectsComponentsDependencies();
			void unpause();
			void unpauseGameObjectComponents( Comp2D::Objects::GameObject* gameObject );
			void unpauseGameObjectsComponents();
			void unpauseGameStateBehaviors();
			void updateGameObjectAnimationsControllerComponent( Comp2D::Objects::GameObject* gameObject, Uint32 currentTime );
			void updateGameObjectBehaviors( Comp2D::Objects::GameObject* gameObject );
			void updateGameObjectsTransformComponent();
			void updateGameObjectTimelinesControllerComponent( Comp2D::Objects::GameObject* gameObject, Uint32 currentTime );
			void updateGameObjectTransformComponent( Comp2D::Objects::GameObject* gameObject );
			void updateGameStateBehaviors();

		protected:
			Uint32 m_componentID = 0;
			Uint32 m_gameObjectID = 0;
			Uint32 m_gameStateBehaviorID = 0;
			Uint32 m_id;

			std::set<std::string> m_resourceComponentsResourcesNames;

			std::list<Comp2D::Components::Renderable*> m_renderableComponents;

			std::list<Comp2D::States::GameStateBehavior*> m_gameStateBehaviors;

			std::list<Comp2D::Objects::GameObject*> m_gameObjects;

			Comp2D::States::GameStateBehavior* attachGameStateBehavior
			(
				Comp2D::States::GameStateBehavior* gameStateBehavior,
				bool enabled = true
			);

		public:
			GameState( Uint32 stateID );

			virtual ~GameState();

			static void callFunctionAfterTimeOnSeparateThread
			(
				//std::function<Uint32(Uint32, void*)> timerFunction,
				Uint32 (*timerFunction)(Uint32, void*),
				void* param,
				Uint32 callbackTimeInMilliseconds
			);
			static void callFunctionOnSeparateThread
			(
				int (*separateThreadFunction)(void*),
				void* data,
				const std::string& threadName
			);
			static void callProcedureAfterTimeOnGameThread
			(
				std::function<void()> timedProcedure,
				Uint32 callbackTimeInMilliseconds,
				bool pausable = true/*,
				bool useTimeScale = true,
				bool useDeltaTime = true*/
			);

			virtual void resetState();
			virtual void setup();

			Uint32 getID() const;

			Comp2D::Components::Component* createComponent
			(
				Comp2D::Components::Component* component,
				bool enabled = true
			);

			Comp2D::Components::TransformComponent* createTransformComponent
			(
				Comp2D::Components::TransformComponent* transformComponent,
				bool enabled = true
			);

			Comp2D::Objects::GameObject* createGameObject( Comp2D::Objects::GameObject* gameObject );

			friend class Comp2D::Game;
			friend class Comp2D::States::PhysicsGameState;
			friend class Comp2D::States::LightsGameState;
		};
	}
}

#endif /* Comp2D_HEADERS_STATES_GAMESTATE_H_ */
