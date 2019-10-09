/* Game.h -- 'Comp2D' Game Engine 'Game' class header file
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

#ifndef Comp2D_HEADERS_GAME_H_
#define Comp2D_HEADERS_GAME_H_

#include <functional>
#include <list>
#include <string>

#include <SDL.h>
#include <SDL_thread.h>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/DataManagement/DataManager.h"
#include "Comp2D/Headers/Random/RandomNumberGenerator.h"
#include "Comp2D/Headers/Resources/ResourcesManager.h"
#include "Comp2D/Headers/Settings/GameSettings.h"
#include "Comp2D/Headers/Utilities/Vector2D.h"

// TODO: Mudar esquema de classe estática para Singleton do objeto game,
// 		 para fins de segurança
// TODO: Usar <iterator> std::begin, std::end, std::rbegin() e std::rend() para
//		 iterar no array de GameState
// TODO: BUG: updateFramesPerSecondThroughDeltaTime com FPS acima de 300 retorna 1000 ou 500
// TODO: (OPCIONAL) Colocar get e set para cor de SDL_RenderClear no updateLoop
// TODO: (OPCIONAL) Criar um medidor de Average State FPS

namespace Comp2D
{
	namespace States
	{
		class GameState;
	}

	namespace Time
	{
		class TimedProcedure;
		class TimeManager;
		class Timer;
	}

	class Game
	{
	private:
		Game() = delete;

		static bool inStateTransition;
		static bool paused;
		static bool pausedTimeScale;
		static bool quit;

		constexpr static Uint32 FIRST_STATE_ID = 0;
		// Change this when adding States
		constexpr static Uint32 NUMBER_OF_STATES = 1;

		static unsigned int gameTimedProcedureID;

		static Uint32 averageFramesPerSecond;
		static Uint32 currentStateID;
		static Uint32 framesPerSecond;
		static Uint32 framesPerSecondThroughDeltaTime;
		static Uint32 lastFPSUpdateTime;
		static Uint32 nextStateID;
		static Uint32 timeOnLastFrameStartedRendering;
		static Uint32 timeOnLastFrameFinishedRendering;
		static Uint32 totalRenderedFramesSinceLastFPSUpdate;
		static Uint32 windowPixelFormat;

		static Uint64 totalRenderedFrames;

		static float timeScaleOnPaused;

		static b2Vec2 cameraPosition;

		static std::list<SDL_TimerID> gameTimerFunctionsIDs;

		static std::list<SDL_Thread*> gameSeparateThreadFunctions;

		static std::list<Comp2D::Time::TimedProcedure*> gameTimedProcedures;
		static std::list<Comp2D::Time::TimedProcedure*> gamePausableTimedProcedures;

		static Comp2D::States::GameState** gameStates;

		static Comp2D::Time::Timer timeSinceFirstFrameTimer;

		static bool initialize();
		static void initializeGameSettings();
		static bool initializeGameWindow();
		static bool initializeRenderer();
		static bool initializeImageLoader();
		static bool initializeAudio();
		static void initializeTimeManager();
		static void initializeDataManager();
		static void initializeRandomNumberGenerator();
		static void initializeResourcesManager();
		static void initializeInputs();
		static void initializeStates();
		static void startUpdateLoop();
		static void finalize();
		static void finalizeGameTimerFunctions();
		static void finalizeGameTimedProcedures();
		static void finalizeGameSeparateThreadsFunctions();
		static void finalizeStates();
		static void finalizeInputs();
		static void finalizeResourcesManager();
		static void finalizeRandomNumberGenerator();
		static void finalizeDataManager();
		static void finalizeTimeManager();
		static void finalizeAudio();
		static void finalizeImageLoader();
		static void finalizeRenderer();
		static void finalizeGameWindow();
		static void finalizeGameSettings();

		static void checkGameTimedProcedures();
		static void pauseGameTimedProcedures();
		static void unpauseGameTimedProcedures();
		static void updateAverageFramePerSecond();
		static void updateFramesPerSecond();
		static void updateFramesPerSecondThroughDeltaTime();

	public:
		static SDL_Window* window;

		static SDL_Renderer* renderer;

		static Settings::GameSettings* gameSettings;

		static Comp2D::DataManagement::DataManager* dataManager;

		static Comp2D::Time::TimeManager* timeManager;

		static Comp2D::Random::RandomNumberGenerator* randomNumberGenerator;

		static Comp2D::Resources::ResourcesManager* resourcesManager;

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
		static void pause( bool pauseTimeScale = true );
		static void quitGame();
		static void reportError
		(
			const std::string& errorTitle,
			const std::string& errorText,
			const char* errorData = nullptr,
			bool quitGameAfterReport = true
		);
		static void setCameraPosition( const b2Vec2& position );
		static void start();
		static void startStateTransition( Uint32 nextStateID );
		static void unpause();

		static bool isPaused();

		static Uint32 getAverageFramesPerSecond();
		static Uint32 getCurrentStateID();
		static Uint32 getFramesPerSecond();
		static Uint32 getFramesPerSecondThroughDeltaTime();
		static Uint32 getWindowPixelFormat();

		static float getCameraPositionX();
		static float getCameraPositionY();

		static Comp2D::Utilities::Vector2D<int> getCameraScreenPosition();

		static const b2Vec2& getCameraPosition();
	};
}

#endif /* Comp2D_HEADERS_GAME_H_ */
