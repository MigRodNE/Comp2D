/* GameState.cpp -- 'Comp2D' Game Engine 'GameState' class source file
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

#include "Comp2D/Headers/States/GameState.h"

#include <functional>
#include <iterator>
#include <list>
#include <set>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <vector>

#include <SDL.h>
#include <SDL_thread.h>

#include "Comp2D/Headers/Game.h"
#include "Comp2D/Headers/Animations/Animation.h"
#include "Comp2D/Headers/Components/AnimationsControllerComponent.h"
#include "Comp2D/Headers/Components/Component.h"
#include "Comp2D/Headers/Components/GameObjectBehavior.h"
#include "Comp2D/Headers/Components/Renderable.h"
#include "Comp2D/Headers/Components/ResourceComponent.h"
#include "Comp2D/Headers/Components/TimelinesControllerComponent.h"
#include "Comp2D/Headers/Components/TransformComponent.h"
#include "Comp2D/Headers/Objects/Dependency.h"
#include "Comp2D/Headers/Objects/GameObject.h"
#include "Comp2D/Headers/States/GameStateBehavior.h"
#include "Comp2D/Headers/Time/TimedProcedure.h"
#include "Comp2D/Headers/Time/TimeManager.h"

unsigned int Comp2D::States::GameState::currentGameStateTimedProcedureID = 0;

std::list<SDL_TimerID> Comp2D::States::GameState::currentGameStateTimerFunctionsIDs;

std::list<SDL_Thread*> Comp2D::States::GameState::currentGameStateSeparateThreadFunctions;

std::list<Comp2D::Time::TimedProcedure*> Comp2D::States::GameState::currentGameStateTimedProcedures;
std::list<Comp2D::Time::TimedProcedure*> Comp2D::States::GameState::currentGameStatePausableTimedProcedures;

Comp2D::States::GameState::GameState( Uint32 stateID )
	:
	m_id{ stateID }
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u Constructor body Start\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u Constructor body End\n", m_id );
	#endif
}

Comp2D::States::GameState::~GameState()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u Destroying\n", m_id );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u Destroyed\n", m_id );
	#endif
}

void Comp2D::States::GameState::checkGameStateTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState checkTimedProcedures\n" );
	#endif

	Uint32 currentTime = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gameStateTimedProcedureIt = currentGameStateTimedProcedures.begin();
		gameStateTimedProcedureIt != currentGameStateTimedProcedures.end();
		++gameStateTimedProcedureIt
	)
	{
		Comp2D::Time::TimedProcedure* currentGameStateTimedProcedure = (*gameStateTimedProcedureIt);

		if( currentGameStateTimedProcedure->checkCallbackTime( currentTime ) )
		{
			currentGameStatePausableTimedProcedures.remove( currentGameStateTimedProcedure );
			currentGameStateTimedProcedures.remove( currentGameStateTimedProcedure );
			delete currentGameStateTimedProcedure;

			--gameStateTimedProcedureIt;
		}
	}
}

void Comp2D::States::GameState::pauseGameStateTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState pauseGameStateTimedProcedures\n" );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gameStatePausableTimedProcedureIt = currentGameStatePausableTimedProcedures.begin();
		gameStatePausableTimedProcedureIt != currentGameStatePausableTimedProcedures.end();
		++gameStatePausableTimedProcedureIt
	)
	{
		(*gameStatePausableTimedProcedureIt)->pause();
	}
}

void Comp2D::States::GameState::unpauseGameStateTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState unpauseGameStateTimedProcedures\n" );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gameStatePausableTimedProcedureIt = currentGameStatePausableTimedProcedures.begin();
		gameStatePausableTimedProcedureIt != currentGameStatePausableTimedProcedures.end();
		++gameStatePausableTimedProcedureIt
	)
	{
		(*gameStatePausableTimedProcedureIt)->unpause();
	}
}

void Comp2D::States::GameState::beforeSetup()
{
#ifdef DEBUG
	SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u beforeSetup\n", m_id );
#endif
}

void Comp2D::States::GameState::finalize()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalize\n", m_id );
	#endif

	finalizeGameStateTimerFunctions();
	finalizeGameStateTimedProcedures();
	finalizeGameSeparateThreadsFunctions();
	finalizeComponents();
	finalizeGameStateBehaviors();
	deleteComponents();
	deleteGameStateBehaviors();
	freeResourcesFromResourceComponents();
	deleteGameObjects();
}

void Comp2D::States::GameState::onEvent( SDL_Event e )
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u onEvent with event of type %u\n", m_stateID, e.type );
	#endif

	if( e.type == SDL_QUIT )
	{
		Comp2D::Game::quitGame();
	}

	Comp2D::States::GameStateBehavior* currentGameStateBehavior = nullptr;

	// gameStateBehaviorsOnEvent( e )
	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator behaviorIt = m_gameStateBehaviors.begin();
		behaviorIt != m_gameStateBehaviors.end();
		++behaviorIt
	)
	{
		currentGameStateBehavior = (*behaviorIt);

		if( currentGameStateBehavior->isEnabled() )
		{
			currentGameStateBehavior->onEvent( e );
		}
	}

	// gameObjectsOnEvent( e )
	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		if( currentGameObject->isActive() && currentGameObject->isActiveInHierarchy() )
		{
			// gameObjectOnEvent( currentGameObject, e );
			Comp2D::Components::GameObjectBehavior* currentGameObjectBehavior = nullptr;

			for
			(
				//std::list<Comp2D::Components::Component*>::iterator it = currentGameObject->activeInHierarchyComponents.begin();
				//it != currentGameObject->activeInHierarchyComponents.end();
				std::vector<Comp2D::Components::Component*>::iterator it = currentGameObject->components.begin();
				it != currentGameObject->components.end();
				++it
			)
			{
				currentGameObjectBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

				if
				(
					currentGameObjectBehavior != nullptr &&
					currentGameObjectBehavior->isEnabled() &&
					currentGameObjectBehavior->isActiveInHierarchy()
				)
				{
					currentGameObjectBehavior->onEvent( e );
				}
			}
		}
	}
}

void Comp2D::States::GameState::render()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u render\n", m_stateID );
	#endif

	for
	(
		std::list<Comp2D::Components::Renderable*>::iterator renderableComponentIt = m_renderableComponents.begin();
		renderableComponentIt != m_renderableComponents.end();
		++renderableComponentIt
	)
	{
		Comp2D::Components::Renderable* currentRenderable = *renderableComponentIt;
		Comp2D::Components::Component* currentComponent = dynamic_cast<Comp2D::Components::Component*>( currentRenderable );

		if
		(
			//currentComponent != nullptr &&
			currentComponent->isActiveInHierarchy() &&
			currentComponent->isEnabled()
		)
		{
			currentRenderable->render();
		}
	}
}

void Comp2D::States::GameState::update()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u update\n", m_stateID );
	#endif

	Uint32 currentTimeSinceSDLInitializationInMilliseconds = Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds();

	updateGameStateBehaviors();

	// updateGameObjects()
	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		if( currentGameObject->isActive() && currentGameObject->isActiveInHierarchy() )
		{
			// updateGameObject( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds )
			updateGameObjectAnimationsControllerComponent( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds );

			updateGameObjectTimelinesControllerComponent( currentGameObject, currentTimeSinceSDLInitializationInMilliseconds );

			if( currentGameObject->parentGameObject == nullptr )
			{
				updateGameObjectTransformComponent( currentGameObject );
			}

			updateGameObjectBehaviors( currentGameObject );
		}
	}
}

void Comp2D::States::GameState::deleteComponents()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u deleteComponents\n", m_id );
	#endif

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::reverse_iterator gameObjectReverseIt = m_gameObjects.rbegin();
		gameObjectReverseIt != m_gameObjects.rend();
		++gameObjectReverseIt
	)
	{
		currentGameObject = (*gameObjectReverseIt);

		// deleteGameObjectComponents( (*gameObjectReverseIt) )
		Comp2D::Components::Component* currentComponent = nullptr;

		for
		(
			std::vector<Comp2D::Components::Component*>::reverse_iterator componentReverseIt =  currentGameObject->components.rbegin();
			componentReverseIt != currentGameObject->components.rend();
			++componentReverseIt
		)
		{
			currentComponent = (*componentReverseIt);

			currentComponent->onDelete();
			delete currentComponent;
			currentComponent = nullptr;
		}

		if( currentGameObject->transform )
		{
			currentGameObject->transform->onDelete();
			delete currentGameObject->transform;
			currentGameObject->transform = nullptr;
		}
	}

	m_componentID = 0;
}

void Comp2D::States::GameState::deleteGameObjects()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u deleteGameObjects\n", m_id );
	#endif

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::reverse_iterator gameObjectReverseIt = m_gameObjects.rbegin();
		gameObjectReverseIt != m_gameObjects.rend();
		++gameObjectReverseIt
	)
	{
		currentGameObject = (*gameObjectReverseIt);
		delete currentGameObject;
		currentGameObject = nullptr;
	}

	m_gameObjects.clear();

	m_gameObjectID = 0;
}

void Comp2D::States::GameState::deleteGameStateBehaviors()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u deleteGameStateBehaviors\n", m_id );
	#endif

	Comp2D::States::GameStateBehavior* currentGameStateBehavior = nullptr;

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::reverse_iterator gameStateBehaviorReverseIt = m_gameStateBehaviors.rbegin();
		gameStateBehaviorReverseIt != m_gameStateBehaviors.rend();
		++gameStateBehaviorReverseIt
	)
	{
		currentGameStateBehavior = (*gameStateBehaviorReverseIt);

		currentGameStateBehavior->onDelete();
		delete currentGameStateBehavior;
		currentGameStateBehavior = nullptr;
	}

	m_gameStateBehaviors.clear();

	m_gameStateBehaviorID = 0;
}

void Comp2D::States::GameState::finalizeComponents()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalizeComponents\n", m_id );
	#endif

	m_renderableComponents.clear();

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::reverse_iterator gameObjectReverseIt = m_gameObjects.rbegin();
		gameObjectReverseIt != m_gameObjects.rend();
		++gameObjectReverseIt
	)
	{
		currentGameObject = (*gameObjectReverseIt);

		for
		(
			std::vector<Comp2D::Components::Component*>::reverse_iterator componentReverseIt = currentGameObject->components.rbegin();
			componentReverseIt != currentGameObject->components.rend();
			++componentReverseIt
		)
		{
			(*componentReverseIt)->onFinalizeState();
		}

		if( currentGameObject->transform )
		{
			currentGameObject->transform->onFinalizeState();
		}
	}
}

void Comp2D::States::GameState::finalizeGameSeparateThreadsFunctions()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalizeGameSeparateThreadsFunctions\n", m_id );
	#endif

	for
	(
		std::list<SDL_Thread*>::reverse_iterator gameStateSeparateThreadFunctionReverseIt = currentGameStateSeparateThreadFunctions.rbegin();
		gameStateSeparateThreadFunctionReverseIt != currentGameStateSeparateThreadFunctions.rend();
		++gameStateSeparateThreadFunctionReverseIt
	)
	{
		#ifdef DEBUG
			SDL_LogDebug
			(
				SDL_LOG_CATEGORY_TEST,
				"GameState with ID %u Waiting Separate Thread Function With Address %p\n",
				m_id,
				*gameStateSeparateThreadFunctionReverseIt
			);
		#endif

		SDL_WaitThread( *gameStateSeparateThreadFunctionReverseIt, nullptr );
	}

	currentGameStateSeparateThreadFunctions.clear();
}

void Comp2D::States::GameState::finalizeGameStateBehaviors()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalizeGameStateBehaviors\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::reverse_iterator gameStateBehaviorReverseIt = m_gameStateBehaviors.rbegin();
		gameStateBehaviorReverseIt != m_gameStateBehaviors.rend();
		++gameStateBehaviorReverseIt
	)
	{
		(*gameStateBehaviorReverseIt)->onFinalizeState();
	}
}

void Comp2D::States::GameState::finalizeGameStateTimedProcedures()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalizeGameStateTimedProcedures\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::reverse_iterator currentGameStateTimedProcedureReverseIt = currentGameStateTimedProcedures.rbegin();
		currentGameStateTimedProcedureReverseIt != currentGameStateTimedProcedures.rend();
		++currentGameStateTimedProcedureReverseIt
	)
	{
		delete (*currentGameStateTimedProcedureReverseIt);
	}

	currentGameStatePausableTimedProcedures.clear();
	currentGameStateTimedProcedures.clear();
}

void Comp2D::States::GameState::finalizeGameStateTimerFunctions()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u finalizeGameStateTimerFunctions\n", m_id );
	#endif

	for
	(
		std::list<SDL_TimerID>::reverse_iterator currentGameStateTimerFunctionIDReverseIt = currentGameStateTimerFunctionsIDs.rbegin();
		currentGameStateTimerFunctionIDReverseIt != currentGameStateTimerFunctionsIDs.rend();
		++currentGameStateTimerFunctionIDReverseIt
	)
	{
		#ifdef DEBUG
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u Removing Timer Function with ID %i\n", m_id, *currentGameStateTimerFunctionIDReverseIt );
		#endif

		SDL_RemoveTimer( *currentGameStateTimerFunctionIDReverseIt );
	}

	currentGameStateTimerFunctionsIDs.clear();
}

void Comp2D::States::GameState::freeResourcesFromResourceComponents()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u freeResourcesFromResourceComponents\n", m_id );
	#endif

	Game::resourcesManager->freeResources( m_resourceComponentsResourcesNames );

	m_resourceComponentsResourcesNames.clear();
}

void Comp2D::States::GameState::initialize()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u initialize\n", m_id );
	#endif

	loadResourcesFromResourceComponents();
	solveGameObjectsComponentsDependencies();
	initializeGameStateBehaviors();
	initializeComponents();
	updateGameObjectsTransformComponent();
}

void Comp2D::States::GameState::initializeComponents()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u initializeComponents\n", m_id );
	#endif

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		if( currentGameObject->transform )
		{
			currentGameObject->transform->onInitializeState();
		}

		for
		(
			std::vector<Comp2D::Components::Component*>::iterator componentIt = currentGameObject->components.begin();
			componentIt != currentGameObject->components.end();
			++componentIt
		)
		{
			Comp2D::Components::Component* currentComponent = (*componentIt);

			currentComponent->onInitializeState();

			if( Comp2D::Components::Renderable* currentRenderableComponent = dynamic_cast<Comp2D::Components::Renderable*>( currentComponent ) )
			{
				m_renderableComponents.push_back( currentRenderableComponent );
			}
		}
	}

	m_renderableComponents.sort
	(
		[]( const Comp2D::Components::Renderable* renderableA, const Comp2D::Components::Renderable* renderableB )
		{
			if
			(
				static_cast<int>( renderableA->renderLayer ) < static_cast<int>( renderableB->renderLayer ) ||
				(
					renderableA->renderLayer == renderableB->renderLayer &&
					renderableA->orderInRenderLayer < renderableB->orderInRenderLayer
				)
			)
			{
				return true;
			}
			return false;
		}
	);
}

void Comp2D::States::GameState::initializeGameStateBehaviors()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u initializeGameStateBehaviors\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator gameStateBehaviorIt = m_gameStateBehaviors.begin();
		gameStateBehaviorIt != m_gameStateBehaviors.end();
		++gameStateBehaviorIt
	)
	{
		(*gameStateBehaviorIt)->onInitializeState();
	}
}

void Comp2D::States::GameState::loadResourcesFromAnimationsControllerComponent( Comp2D::Components::AnimationsControllerComponent* animationsControllerComponent )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u loadResourcesFromAnimationsControllerComponent: animationsControllerComponent with ID %u\n", m_id, animationsControllerComponent->getID() );
	#endif

	std::string animationsControllerComponentACResourceName = animationsControllerComponent->getAnimationsControllerResource()->getName();

	m_resourceComponentsResourcesNames.emplace( animationsControllerComponentACResourceName );

	Game::resourcesManager->loadResource( animationsControllerComponentACResourceName );

	const std::vector<std::string> animationsControllerComponentAnimationsResourcesNames
		= animationsControllerComponent->getAnimationsController()->getAnimationsResourcesNames();

	for
	(
		std::vector<std::string>::const_iterator animationResourceNameConstIt = animationsControllerComponentAnimationsResourcesNames.cbegin();
		animationResourceNameConstIt != animationsControllerComponentAnimationsResourcesNames.cend();
		++animationResourceNameConstIt
	)
	{
		m_resourceComponentsResourcesNames.emplace( *animationResourceNameConstIt );
	}
}

void Comp2D::States::GameState::loadResourcesFromResourceComponents()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u loadResourcesFromResourceComponents\n", m_id );
	#endif

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		Comp2D::Components::ResourceComponent* currentResourceComponent = nullptr;

		for
		(
			std::vector<Comp2D::Components::Component*>::iterator componentIt = currentGameObject->components.begin();
			componentIt != currentGameObject->components.end();
			++componentIt
		)
		{
			currentResourceComponent = dynamic_cast<Comp2D::Components::ResourceComponent*>( *componentIt );

			if( currentResourceComponent )
			{
				m_resourceComponentsResourcesNames.emplace( currentResourceComponent->getResource()->getName() );
			}
			else
			{
				Comp2D::Components::AnimationsControllerComponent* currentAnimationsControllerComponent
					= dynamic_cast<Comp2D::Components::AnimationsControllerComponent*>( *componentIt );

				if( currentAnimationsControllerComponent )
				{
					loadResourcesFromAnimationsControllerComponent( currentAnimationsControllerComponent );
				}
				else
				{
					Comp2D::Components::TimelinesControllerComponent* currentTimelinesControllerComponent
						= dynamic_cast<Comp2D::Components::TimelinesControllerComponent*>( *componentIt );

					if( currentTimelinesControllerComponent )
					{
						loadResourcesFromTimelinesControllerComponent( currentTimelinesControllerComponent );
					}
				}
			}
		}
	}

	Game::resourcesManager->loadResources( m_resourceComponentsResourcesNames );
}

void Comp2D::States::GameState::loadResourcesFromTimelinesControllerComponent( Comp2D::Components::TimelinesControllerComponent* timelinesControllerComponent )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u loadResourcesFromTimelinesControllerComponent: timelinesControllerComponent with ID %u\n", m_id, timelinesControllerComponent->getID() );
	#endif

	std::string timelinesControllerComponentTCResourceName = timelinesControllerComponent->getTimelinesControllerResource()->getName();

	m_resourceComponentsResourcesNames.emplace( timelinesControllerComponentTCResourceName );

	Game::resourcesManager->loadResource( timelinesControllerComponentTCResourceName );

	const std::vector<std::string> timelinesControllerComponentTimelinesResourcesNames
		= timelinesControllerComponent->getTimelinesController()->getTimelinesResourcesNames();

	for
	(
		std::vector<std::string>::const_iterator timelineResourceNameConstIt = timelinesControllerComponentTimelinesResourcesNames.cbegin();
		timelineResourceNameConstIt != timelinesControllerComponentTimelinesResourcesNames.cend();
		++timelineResourceNameConstIt
	)
	{
		m_resourceComponentsResourcesNames.emplace( *timelineResourceNameConstIt );
	}
}

void Comp2D::States::GameState::pause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u pause\n", m_id );
	#endif

	pauseGameStateTimedProcedures();
	pauseGameStateBehaviors();
	pauseGameObjectsComponents();
}

void Comp2D::States::GameState::pauseGameObjectComponents( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u pauseGameObjectComponents: gameObject with ID %u\n",
			m_id,
			gameObject->getID()
		);
		*/
	#endif

	for
	(
		std::vector<Comp2D::Components::Component*>::iterator gameObjectComponentIt = gameObject->components.begin();
		gameObjectComponentIt != gameObject->components.end();
		++gameObjectComponentIt
	)
	{
		(*gameObjectComponentIt)->onPaused();
	}
}

void Comp2D::States::GameState::pauseGameObjectsComponents()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u pauseGameObjectsComponents\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		pauseGameObjectComponents( *gameObjectIt );
	}
}

void Comp2D::States::GameState::pauseGameStateBehaviors()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u pauseGameStateBehaviors\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator gameStateBehaviorIt = m_gameStateBehaviors.begin();
		gameStateBehaviorIt != m_gameStateBehaviors.end();
		++gameStateBehaviorIt
	)
	{
		(*gameStateBehaviorIt)->onPaused();
	}
}

void Comp2D::States::GameState::solveGameObjectComponentDependency( Comp2D::Objects::Dependency* componentDependency )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u solveGameObjectComponentDependency\n",
			m_id
		);
		*/
	#endif

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		Comp2D::Objects::GameObject* currentGameObject = *gameObjectIt;

		if( currentGameObject->getName().compare( componentDependency->requiredGameObjectName ) == 0 )
		{
			if( componentDependency->requiredObjectType == Comp2D::Objects::ERequiredObjectType::GameObject )
			{
				(*componentDependency->dependentPointerToRequiredObject) = currentGameObject;
			}
			else
			{
				unsigned int currentGameObjectComponentIndex = 0;

				for
				(
					std::vector<Comp2D::Components::Component*>::iterator gameObjectComponentIt = currentGameObject->components.begin();
					gameObjectComponentIt != currentGameObject->components.end();
					++gameObjectComponentIt
				)
				{
					Comp2D::Components::Component* currentGameObjectComponent = *gameObjectComponentIt;

					if
					(
						typeid( *currentGameObjectComponent ).hash_code() == componentDependency->requiredComponentType.hash_code() &&
						currentGameObjectComponentIndex++ == componentDependency->requiredComponentIndex
					)
					{
						(*componentDependency->dependentPointerToRequiredObject) = currentGameObjectComponent;

						break;
					}
				}
			}

			break;
		}
	}
}

void Comp2D::States::GameState::solveGameObjectComponentsDependencies( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u solveGameObjectComponentsDependencies: gameObject with ID %u\n",
			m_id,
			gameObject->getID()
		);
		*/
	#endif

	for
	(
		std::list<Comp2D::Objects::Dependency*>::iterator gameObjectComponentDependencyIt = gameObject->componentDependencies.begin();
		gameObjectComponentDependencyIt != gameObject->componentDependencies.end();
		++gameObjectComponentDependencyIt
	)
	{
		solveGameObjectComponentDependency( *gameObjectComponentDependencyIt );
	}

	for
	(
		std::list<Comp2D::Objects::Dependency*>::iterator gameObjectComponentDependencyIt = gameObject->componentDependencies.begin();
		gameObjectComponentDependencyIt != gameObject->componentDependencies.end();
		++gameObjectComponentDependencyIt
	)
	{
		delete *gameObjectComponentDependencyIt;
	}
	gameObject->componentDependencies.clear();
}

void Comp2D::States::GameState::solveGameObjectsComponentsDependencies()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u solveGameObjectsComponentsDependencies\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		solveGameObjectComponentsDependencies( *gameObjectIt );
	}
}

void Comp2D::States::GameState::unpause()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u unpause\n", m_id );
	#endif

	unpauseGameStateBehaviors();
	unpauseGameObjectsComponents();
	unpauseGameStateTimedProcedures();
}

void Comp2D::States::GameState::unpauseGameObjectComponents( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u unpauseGameObjectComponents: gameObject with ID %u\n",
			m_id,
			gameObject->getID()
		);
		*/
	#endif

	for
	(
		std::vector<Comp2D::Components::Component*>::iterator gameObjectComponentIt = gameObject->components.begin();
		gameObjectComponentIt != gameObject->components.end();
		++gameObjectComponentIt
	)
	{
		(*gameObjectComponentIt)->onUnpaused();
	}
}

void Comp2D::States::GameState::unpauseGameObjectsComponents()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u unpauseGameObjectsComponents\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		unpauseGameObjectComponents( *gameObjectIt );
	}
}

void Comp2D::States::GameState::unpauseGameStateBehaviors()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u unpauseGameStateBehaviors\n", m_id );
	#endif

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator gameStateBehaviorIt = m_gameStateBehaviors.begin();
		gameStateBehaviorIt != m_gameStateBehaviors.end();
		++gameStateBehaviorIt
	)
	{
		(*gameStateBehaviorIt)->onUnpaused();
	}
}

void Comp2D::States::GameState::updateGameObjectAnimationsControllerComponent( Comp2D::Objects::GameObject* gameObject, Uint32 currentTime )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u updateGameObjectAnimationsControllerComponent: gameObject with ID %u; currentTime = %u\n",
			m_stateID,
			gameObject->getID(),
			currentTime
		);
		*/
	#endif

	Comp2D::Components::AnimationsControllerComponent* currentAnimationsControllerComponent = nullptr;

	for
	(
		//std::list<Comp2D::Components::Component*>::iterator activeInHierarchyComponentIt = gameObject->activeInHierarchyComponents.begin();
		//activeInHierarchyComponentIt != gameObject->activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator activeInHierarchyComponentIt = gameObject->components.begin();
		activeInHierarchyComponentIt != gameObject->components.end();
		++activeInHierarchyComponentIt
	)
	{
		currentAnimationsControllerComponent = dynamic_cast<Comp2D::Components::AnimationsControllerComponent*>( *activeInHierarchyComponentIt );

		if
		(
			currentAnimationsControllerComponent != nullptr &&
			currentAnimationsControllerComponent->isEnabled() &&
			currentAnimationsControllerComponent->isActiveInHierarchy()
		)
		{
			currentAnimationsControllerComponent->update( currentTime );
		}
	}
}

void Comp2D::States::GameState::updateGameObjectBehaviors( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u updateGameObjectBehaviors: gameObject with ID %u\n",
			m_stateID,
			gameObject->getID()
		);
		*/
	#endif

	Comp2D::Components::GameObjectBehavior* currentBehavior = nullptr;

	for
	(
		//std::list<Comp2D::Components::Component*>::iterator it = gameObject->activeInHierarchyComponents.begin();
		//it != gameObject->activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator it = gameObject->components.begin();
		it != gameObject->components.end();
		++it
	)
	{
		currentBehavior = dynamic_cast<Comp2D::Components::GameObjectBehavior*>( *it );

		if
		(
			currentBehavior != nullptr &&
			currentBehavior->isEnabled() &&
			currentBehavior->isActiveInHierarchy()
		)
		{
			currentBehavior->update();
		}
	}
}

void Comp2D::States::GameState::updateGameObjectsTransformComponent()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u updateGameObjectsTransformComponent\n", m_id );
	#endif

	Comp2D::Objects::GameObject* currentGameObject = nullptr;

	for
	(
		std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = m_gameObjects.begin();
		gameObjectIt != m_gameObjects.end();
		++gameObjectIt
	)
	{
		currentGameObject = (*gameObjectIt);

		if( currentGameObject->isActive() && currentGameObject->isActiveInHierarchy() )
		{
			if( currentGameObject->parentGameObject == nullptr )
			{
				updateGameObjectTransformComponent( currentGameObject );
			}
		}
	}
}

void Comp2D::States::GameState::updateGameObjectTimelinesControllerComponent( Comp2D::Objects::GameObject* gameObject, Uint32 currentTime )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u updateGameObjectTimelinesControllerComponent: gameObject with ID %u; currentTime = %u\n",
			m_stateID,
			gameObject->getID(),
			currentTime
		);
		*/
	#endif

	Comp2D::Components::TimelinesControllerComponent* currentTimelinesControllerComponent = nullptr;

	for
	(
		//std::list<Comp2D::Components::Component*>::iterator activeInHierarchyComponentIt = gameObject->activeInHierarchyComponents.begin();
		//activeInHierarchyComponentIt != gameObject->activeInHierarchyComponents.end();
		std::vector<Comp2D::Components::Component*>::iterator activeInHierarchyComponentIt = gameObject->components.begin();
		activeInHierarchyComponentIt != gameObject->components.end();
		++activeInHierarchyComponentIt
	)
	{
		currentTimelinesControllerComponent = dynamic_cast<Comp2D::Components::TimelinesControllerComponent*>( *activeInHierarchyComponentIt );

		if
		(
			currentTimelinesControllerComponent != nullptr &&
			currentTimelinesControllerComponent->isEnabled() &&
			currentTimelinesControllerComponent->isActiveInHierarchy()
		)
		{
			currentTimelinesControllerComponent->update( currentTime );
		}
	}
}

void Comp2D::States::GameState::updateGameObjectTransformComponent( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u updateGameObjectTransformComponent: gameObject with ID %u\n",
			m_id,
			gameObject->getID()
		);
		*/
	#endif

	if( gameObject->transform )
	{
		gameObject->transform->updateTransform();
	}

	Comp2D::Objects::GameObject* currentChildGameObject = nullptr;

	for
	(
		//std::list<Comp2D::Objects::GameObject*>::iterator gameObjectIt = gameObject->activeInHierarchyChildGameObjects.begin();
		//gameObjectIt != gameObject->activeInHierarchyChildGameObjects.end();
		std::vector<Comp2D::Objects::GameObject*>::iterator gameObjectIt = gameObject->childGameObjects.begin();
		gameObjectIt != gameObject->childGameObjects.end();
		++gameObjectIt
	)
	{
		currentChildGameObject = (*gameObjectIt);

		if
		(
			currentChildGameObject->isActiveInHierarchy() &&
			currentChildGameObject->isActive()
		)
		{
			updateGameObjectTransformComponent( currentChildGameObject );
		}
	}
}

void Comp2D::States::GameState::updateGameStateBehaviors()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u updateGameStateBehaviors\n", m_id );
	#endif

	Comp2D::States::GameStateBehavior* currentGameStateBehavior = nullptr;

	for
	(
		std::list<Comp2D::States::GameStateBehavior*>::iterator gameStateBehaviorIt = m_gameStateBehaviors.begin();
		gameStateBehaviorIt != m_gameStateBehaviors.end();
		++gameStateBehaviorIt
	)
	{
		currentGameStateBehavior = (*gameStateBehaviorIt);

		if( currentGameStateBehavior->isEnabled() )
		{
			currentGameStateBehavior->update();
		}
	}
}

Comp2D::States::GameStateBehavior* Comp2D::States::GameState::attachGameStateBehavior
(
	Comp2D::States::GameStateBehavior* gameStateBehavior,
	bool enabled
)
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u attachGameStateBehavior: gameStateBehavior with ID %u; enabled = %i\n",
			m_id,
			gameStateBehavior->getID(),
			enabled
		);
	#endif

	gameStateBehavior->gameState = this;
	gameStateBehavior->onInstantiated();
	m_gameStateBehaviors.push_back( gameStateBehavior );
	gameStateBehavior->setEnabled( enabled );
	return gameStateBehavior;
}

void Comp2D::States::GameState::callFunctionAfterTimeOnSeparateThread
(
	//std::function<Uint32(Uint32, void*)> timerFunction,
	Uint32 (*timerFunction)(Uint32, void*),
	void* param,
	Uint32 callbackTimeInMilliseconds
)
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState callFunctionAfterTimeOnSeparateThread: callbackTimeInMilliseconds = %u\n",
			callbackTimeInMilliseconds
		);
	#endif

	currentGameStateTimerFunctionsIDs.push_back
	(
		SDL_AddTimer
		(
			callbackTimeInMilliseconds,
			//timerFunction.target<Uint32(Uint32, void*)>(),
			timerFunction,
			param
		)
	);
}

void Comp2D::States::GameState::callFunctionOnSeparateThread
(
	int (*separateThreadFunction)(void*),
	void* data,
	const std::string& threadName
)
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState callFunctionOnSeparateThread: threadName = %s\n", threadName.c_str() );
	#endif

	currentGameStateSeparateThreadFunctions.push_back
	(
		SDL_CreateThread
		(
			separateThreadFunction,
			threadName.c_str(),
			data
		)
	);
}

void Comp2D::States::GameState::callProcedureAfterTimeOnGameThread
(
	std::function<void()> timedProcedure,
	Uint32 callbackTimeInMilliseconds,
	bool pausable/*,
	bool useTimeScale,
	bool useDeltaTime*/
)
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState callProcedureAfterTimeOnGameThread: callbackTimeInMilliseconds = %u; pausable = %i\n",
			callbackTimeInMilliseconds,
			pausable
		);
	#endif

	Comp2D::Time::TimedProcedure* createGameStateTimedProcedure = new Comp2D::Time::TimedProcedure
	(
		currentGameStateTimedProcedureID++,
		timedProcedure,
		Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() + callbackTimeInMilliseconds,
		pausable
	);

	if( createGameStateTimedProcedure->isPausable() )
	{
		if( Comp2D::Game::isPaused() )
		{
			createGameStateTimedProcedure->pause();
		}

		currentGameStatePausableTimedProcedures.push_back( createGameStateTimedProcedure );
	}

	currentGameStateTimedProcedures.push_back( createGameStateTimedProcedure );
}

void Comp2D::States::GameState::resetState()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u resetState\n", m_id );
	#endif

	finalize();

	beforeSetup();
	setup();
	initialize();

	Comp2D::Game::timeManager->setCurrentStateInitializedTime( Comp2D::Game::timeManager->getTimeSinceSDLInitializationInMilliseconds() );
}

void Comp2D::States::GameState::setup()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u setup\n", m_id );
	#endif
}

Uint32 Comp2D::States::GameState::getID() const
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "GameState with ID %u getID\n", m_id );
	#endif

	return m_id;
}

Comp2D::Components::Component* Comp2D::States::GameState::createComponent
(
	Comp2D::Components::Component* component,
	bool enabled
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u createComponent: component with ID %u; enabled = %i\n",
			m_id,
			component->getID(),
			enabled
		);
		*/
	#endif

	component->onInstantiated();
	//component->gameObject->addComponent( component, enabled );
	//return component;
	return component->gameObject->addComponent( component, enabled );
}

Comp2D::Components::TransformComponent*  Comp2D::States::GameState::createTransformComponent
(
	Comp2D::Components::TransformComponent* transformComponent,
	bool enabled
)
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u createTransformComponent: transformComponent with ID %u; enabled = %i\n",
			m_id,
			transformComponent->getID(),
			enabled
		);
		*/
	#endif

	transformComponent->onInstantiated();
	transformComponent->gameObject->transform = transformComponent;
	transformComponent->setActiveInHierarchy( transformComponent->gameObject->isActiveInHierarchy() );
	transformComponent->setEnabled( enabled );
	return transformComponent;
}

Comp2D::Objects::GameObject* Comp2D::States::GameState::createGameObject( Comp2D::Objects::GameObject* gameObject )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"GameState with ID %u createGameObject: gameObject with ID %u\n",
			m_id,
			gameObject->getID()
		);
		*/
	#endif

	m_gameObjects.push_back( gameObject );
	return gameObject;
}
