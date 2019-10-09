/* Game.cpp -- 'Comp2D' Game Engine 'Game' class source file
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

#include "Comp2D/Headers/Game.h"

#include <cmath>
#include <functional>
#include <iterator>
#include <list>
#include <sstream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Box2D/Common/b2Math.h"

#include "Comp2D/Headers/DataManagement/DataManager.h"
#include "Comp2D/Headers/Inputs/GameInputs.h"
#include "Comp2D/Headers/Random/RandomNumberGenerator.h"
#include "Comp2D/Headers/Random/MersenneTwisterRNG.h"
#include "Comp2D/Headers/Resources/ResourcesManager.h"
#include "Comp2D/Headers/Settings/AudioSettings.h"
#include "Comp2D/Headers/Settings/GameSettings.h"
#include "Comp2D/Headers/Settings/GraphicsSettings.h"
#include "Comp2D/Headers/States/GameState.h"
#include "Comp2D/Headers/Time/TimedProcedure.h"
#include "Comp2D/Headers/Time/TimeManager.h"
#include "Comp2D/Headers/Time/Timer.h"

bool Comp2D::Game::inStateTransition = false;
bool Comp2D::Game::paused = false;
bool Comp2D::Game::pausedTimeScale = false;
bool Comp2D::Game::quit = false;

unsigned int Comp2D::Game::gameTimedProcedureID = 0;

Uint32 Comp2D::Game::averageFramesPerSecond = 0;
Uint32 Comp2D::Game::currentStateID = 0;
Uint32 Comp2D::Game::framesPerSecond = 0;
Uint32 Comp2D::Game::framesPerSecondThroughDeltaTime = 0;
Uint32 Comp2D::Game::lastFPSUpdateTime = 0;
Uint32 Comp2D::Game::nextStateID = 0;
Uint32 Comp2D::Game::timeOnLastFrameStartedRendering = 0;
Uint32 Comp2D::Game::timeOnLastFrameFinishedRendering = 0;
Uint32 Comp2D::Game::totalRenderedFramesSinceLastFPSUpdate = 0;
Uint32 Comp2D::Game::windowPixelFormat = 0;

Uint64 Comp2D::Game::totalRenderedFrames = 0;

float Comp2D::Game::timeScaleOnPaused = 0.0f;

b2Vec2 Comp2D::Game::cameraPosition = b2Vec2_zero;

std::list<SDL_TimerID> Comp2D::Game::gameTimerFunctionsIDs;

std::list<SDL_Thread*> Comp2D::Game::gameSeparateThreadFunctions;

std::list<Comp2D::Time::TimedProcedure*> Comp2D::Game::gameTimedProcedures;
std::list<Comp2D::Time::TimedProcedure*> Comp2D::Game::gamePausableTimedProcedures;

Comp2D::States::GameState** Comp2D::Game::gameStates = nullptr;

Comp2D::Time::Timer Comp2D::Game::timeSinceFirstFrameTimer;

SDL_Window* Comp2D::Game::window = nullptr;

SDL_Renderer* Comp2D::Game::renderer = nullptr;

Comp2D::Settings::GameSettings* Comp2D::Game::gameSettings = nullptr;

Comp2D::DataManagement::DataManager* Comp2D::Game::dataManager = nullptr;

Comp2D::Time::TimeManager* Comp2D::Game::timeManager = nullptr;

Comp2D::Random::RandomNumberGenerator* Comp2D::Game::randomNumberGenerator = nullptr;

Comp2D::Resources::ResourcesManager* Comp2D::Game::resourcesManager = nullptr;

bool Comp2D::Game::initialize()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initialize\n" );
	#endif

	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ) >= 0 )
	{
		/*
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			#ifdef DEBUG
				SDL_LogWarn( SDL_LOG_CATEGORY_VIDEO, "Linear texture filtering not enabled!" );
			#endif
		}
		*/

		initializeGameSettings();

		if( initializeGameWindow() )
		{
			if( initializeRenderer() )
			{
				SDL_SetRenderDrawColor
				(
					Comp2D::Game::renderer,
					0xFF,
					0xFF,
					0xFF,
					0xFF
				);

				if( !initializeImageLoader() )
				{
					#ifdef DEBUG
						SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					#endif

					reportError( "Fatal Error: 003", "SDL_image could not initialize! SDL_image Error: ", IMG_GetError() );

					success = false;
				}

				if( success && TTF_Init() == -1 )
				{
					#ifdef DEBUG
						SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					#endif

					reportError( "Fatal Error: 004", "SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError() );

					success = false;
				}

				if( success && !initializeAudio() )
				{
					#ifdef DEBUG
						SDL_LogError( SDL_LOG_CATEGORY_AUDIO, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					#endif

					reportError( "Fatal Error: 005", "SDL_mixer could not initialize! SDL_mixer Error: ", Mix_GetError() );

					success = false;
				}

				if( success )
				{
					#ifdef DEBUG
						{
							SDL_version sdlCompiledVersion;

							SDL_VERSION( &sdlCompiledVersion );

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL Compiled Version: %u.%u.%u\n",
								sdlCompiledVersion.major,
								sdlCompiledVersion.minor,
								sdlCompiledVersion.patch
							);

							SDL_version sdlLinkedVersion;

							SDL_GetVersion( &sdlLinkedVersion );

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL Linked Version: %u.%u.%u\n",
								sdlLinkedVersion.major,
								sdlLinkedVersion.minor,
								sdlLinkedVersion.patch
							);

							SDL_version sdlImageCompiledVersion;

							SDL_IMAGE_VERSION( &sdlImageCompiledVersion );

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_image Compiled Version: %u.%u.%u\n",
								sdlImageCompiledVersion.major,
								sdlImageCompiledVersion.minor,
								sdlImageCompiledVersion.patch
							);

							const SDL_version* sdlImageLinkedVersion = IMG_Linked_Version();

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_image Linked Version: %u.%u.%u\n",
								sdlImageLinkedVersion->major,
								sdlImageLinkedVersion->minor,
								sdlImageLinkedVersion->patch
							);

							SDL_version sdlTTFCompiledVersion;

							SDL_TTF_VERSION( &sdlTTFCompiledVersion );

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_ttf Compiled Version: %u.%u.%u\n",
								sdlTTFCompiledVersion.major,
								sdlTTFCompiledVersion.minor,
								sdlTTFCompiledVersion.patch
							);

							const SDL_version* sdlTTFLinkedVersion = TTF_Linked_Version();

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_ttf Linked Version: %u.%u.%u\n",
								sdlTTFLinkedVersion->major,
								sdlTTFLinkedVersion->minor,
								sdlTTFLinkedVersion->patch
							);

							SDL_version sdlMixerCompiledVersion;

							SDL_MIXER_VERSION( &sdlMixerCompiledVersion );

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_mixer Compiled Version: %u.%u.%u\n",
								sdlMixerCompiledVersion.major,
								sdlMixerCompiledVersion.minor,
								sdlMixerCompiledVersion.patch
							);

							const SDL_version* sdlMixerLinkedVersion = Mix_Linked_Version();

							SDL_LogDebug
							(
								SDL_LOG_CATEGORY_TEST,
								"Game SDL_mixer Linked Version: %u.%u.%u\n",
								sdlMixerLinkedVersion->major,
								sdlMixerLinkedVersion->minor,
								sdlMixerLinkedVersion->patch
							);
						}
					#endif

					initializeTimeManager();
					initializeDataManager();
					initializeRandomNumberGenerator();
					initializeResourcesManager();
					initializeInputs();
					initializeStates();
				}
			}
			else
			{
				#ifdef DEBUG
					SDL_LogError( SDL_LOG_CATEGORY_RENDER, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				#endif

				reportError( "Fatal Error: 002", "Renderer could not be created! SDL Error: ", SDL_GetError() );

				success = false;
			}
		}
		else
		{
			#ifdef DEBUG
				SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			#endif

			reportError( "Fatal Error: 001", "Window could not be created! SDL Error: ", SDL_GetError() );

			success = false;
		}
	}
	else
	{
		#ifdef DEBUG
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		#endif

		reportError( "Fatal Error: 000", "SDL could not initialize! SDL Error: ", SDL_GetError() );

		success = false;
	}

	return success;
}

void Comp2D::Game::initializeGameSettings()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeGameSettings\n" );
	#endif

	gameSettings = new Comp2D::Settings::GameSettings();
}

bool Comp2D::Game::initializeGameWindow()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeGameWindow\n" );
	#endif

	window = SDL_CreateWindow
	(
		gameSettings->getWindowTitle().c_str(),
		gameSettings->getWindowInitXPos(),
		gameSettings->getWindowInitYPos(),
		gameSettings->graphicsSettings.getScreenWidth(),
		gameSettings->graphicsSettings.getScreenHeight(),
		gameSettings->getWindowFlags()
	);

	windowPixelFormat = SDL_GetWindowPixelFormat( window );

	return window != nullptr;
}

bool Comp2D::Game::initializeRenderer()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeRenderer\n" );
	#endif

	renderer = SDL_CreateRenderer
	(
		window,
		-1,
		gameSettings->graphicsSettings.getRendererFlags()
	);

	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

	return renderer != nullptr;
}

bool Comp2D::Game::initializeImageLoader()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeImageLoader\n" );
	#endif

	return IMG_Init( gameSettings->getImageLoadingFlags() ) & gameSettings->getImageLoadingFlags();
}

bool Comp2D::Game::initializeAudio()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeAudio\n" );
	#endif

	bool success = false;

	success = Mix_OpenAudio
	(
		gameSettings->audioSettings.getFrequency(),
		gameSettings->audioSettings.getFormat(),
		gameSettings->audioSettings.getChannels(),
		gameSettings->audioSettings.getChunkSize()
	)
	>= 0;

	if( success )
	{
		int supportedFormatsFlags = gameSettings->audioSettings.getSupportedFormatsFlags();

		success = ( Mix_Init( supportedFormatsFlags ) & supportedFormatsFlags ) == supportedFormatsFlags;

		if( success )
		{
			int numberMixChannels = gameSettings->audioSettings.getNumberMixChannels();

			success = Mix_AllocateChannels( numberMixChannels ) == numberMixChannels;
		}
	}

	return success;
}

void Comp2D::Game::initializeTimeManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeTimeManager\n" );
	#endif

	timeManager = new Comp2D::Time::TimeManager();
}

void Comp2D::Game::initializeDataManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeDataManager\n" );
	#endif

	dataManager = new Comp2D::DataManagement::DataManager();

	if( !dataManager->loadDataFromFile() )
	{
		dataManager->setDataToDefaultValues();

		dataManager->saveDataOnFile();
	}
}

void Comp2D::Game::initializeRandomNumberGenerator()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeRandomNumberGenerator\n" );
	#endif

	randomNumberGenerator = new Comp2D::Random::MersenneTwisterRNG();
}

void Comp2D::Game::initializeResourcesManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeResourcesManager\n" );
	#endif

	resourcesManager = new Comp2D::Resources::ResourcesManager();
}

void Comp2D::Game::initializeInputs()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeInputs\n" );
	#endif

	Comp2D::Inputs::GameInputs::initializeGameInputs();
}

void Comp2D::Game::initializeStates()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game initializeStates\n" );
	#endif

	if( NUMBER_OF_STATES < 1 )
	{
		quitGame();
		return;
	}

	gameStates = new Comp2D::States::GameState*[NUMBER_OF_STATES];
	Uint32 id = FIRST_STATE_ID;
	// Add States Here
	gameStates[0] = new Comp2D::States::GameState( id++ );

	gameStates[FIRST_STATE_ID]->beforeSetup();
	gameStates[FIRST_STATE_ID]->setup();
	gameStates[FIRST_STATE_ID]->initialize();
	timeManager->setCurrentStateInitializedTime( SDL_GetTicks() );
}

void Comp2D::Game::startUpdateLoop()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game startUpdateLoop\n" );
	#endif

	SDL_Event e;

	timeSinceFirstFrameTimer.start();

	while( !quit )
	{
		if( inStateTransition )
		{
			if( nextStateID == currentStateID )
			{
				gameStates[currentStateID]->resetState();
			}
			else
			{
				gameStates[currentStateID]->finalize();

				currentStateID = nextStateID;
				gameStates[currentStateID]->beforeSetup();
				gameStates[currentStateID]->setup();
				gameStates[currentStateID]->initialize();
				timeManager->setCurrentStateInitializedTime( timeManager->getTimeSinceSDLInitializationInMilliseconds() );
			}

			inStateTransition = false;

			//timeSinceFirstFrameTimer.start();
		}
		else
		{
			//deltaTimeTimer.stop();
			//deltaTimeTimer.start();

			timeOnLastFrameStartedRendering = SDL_GetTicks();

			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( renderer );

			gameStates[currentStateID]->render();

			SDL_RenderPresent( renderer );

			timeOnLastFrameFinishedRendering = SDL_GetTicks();

			//deltaTimeTimer.pause();

			updateAverageFramePerSecond();
			updateFramesPerSecond();

			timeManager->setDeltaTime
			(
				timeOnLastFrameFinishedRendering - timeOnLastFrameStartedRendering
			);

			updateFramesPerSecondThroughDeltaTime();

			checkGameTimedProcedures();
			Comp2D::States::GameState::checkGameStateTimedProcedures();

			while( SDL_PollEvent( &e ) != 0 )
			{
				gameStates[currentStateID]->onEvent( e );
			}
			Comp2D::Inputs::GameInputs::updateInputDevicesStates();
			gameStates[currentStateID]->update();
		}
	}
}

void Comp2D::Game::finalize()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalize\n" );
	#endif

	finalizeStates();
	finalizeGameTimerFunctions();
	finalizeGameTimedProcedures();
	finalizeGameSeparateThreadsFunctions();
	finalizeInputs();
	finalizeResourcesManager();
	finalizeRandomNumberGenerator();
	finalizeDataManager();
	finalizeTimeManager();

	finalizeAudio();
	TTF_Quit();
	finalizeImageLoader();

	finalizeRenderer();
	finalizeGameWindow();

	finalizeGameSettings();

	SDL_Quit();
}

void Comp2D::Game::finalizeGameTimerFunctions()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeGameTimerFunctions\n" );
	#endif

	for
	(
		std::list<SDL_TimerID>::reverse_iterator gameTimerFunctionIDReverseIt = gameTimerFunctionsIDs.rbegin();
		gameTimerFunctionIDReverseIt != gameTimerFunctionsIDs.rend();
		++gameTimerFunctionIDReverseIt
	)
	{
		#ifdef DEBUG
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game Removing Timer Function with ID %i\n", *gameTimerFunctionIDReverseIt );
		#endif

		SDL_RemoveTimer( *gameTimerFunctionIDReverseIt );
	}

	gameTimerFunctionsIDs.clear();
}

void Comp2D::Game::finalizeGameTimedProcedures()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeGameTimedProcedures\n" );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::reverse_iterator gameTimedProcedureReverseIt = gameTimedProcedures.rbegin();
		gameTimedProcedureReverseIt != gameTimedProcedures.rend();
		++gameTimedProcedureReverseIt
	)
	{
		delete (*gameTimedProcedureReverseIt);
	}

	gamePausableTimedProcedures.clear();
	gameTimedProcedures.clear();
}

void Comp2D::Game::finalizeGameSeparateThreadsFunctions()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeGameSeparateThreadsFunctions\n" );
	#endif

	for
	(
		std::list<SDL_Thread*>::reverse_iterator gameSeparateThreadFunctionReverseIt = gameSeparateThreadFunctions.rbegin();
		gameSeparateThreadFunctionReverseIt != gameSeparateThreadFunctions.rend();
		++gameSeparateThreadFunctionReverseIt
	)
	{
		#ifdef DEBUG
			SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game Waiting Separate Thread Function With Address %p\n", *gameSeparateThreadFunctionReverseIt );
		#endif

		SDL_WaitThread( *gameSeparateThreadFunctionReverseIt, nullptr );
	}

	gameSeparateThreadFunctions.clear();
}

void Comp2D::Game::finalizeStates()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeStates\n" );
	#endif

	if( NUMBER_OF_STATES > FIRST_STATE_ID && gameStates != nullptr )
	{
		gameStates[currentStateID]->finalize();

		for
		(
			Uint32 i = NUMBER_OF_STATES - 1, deletedStatesCount = 1;
			deletedStatesCount <= NUMBER_OF_STATES;
			--i, ++deletedStatesCount
		)
		{
			delete gameStates[i];
			gameStates[i] = nullptr;
		}

		gameStates = nullptr;
	}
}

void Comp2D::Game::finalizeInputs()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeInputs\n" );
	#endif

	Comp2D::Inputs::GameInputs::finalizeGameInputs();
}

void Comp2D::Game::finalizeResourcesManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeResourcesManager\n" );
	#endif

	delete resourcesManager;
}

void Comp2D::Game::finalizeRandomNumberGenerator()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeRandomNumberGenerator\n" );
	#endif

	delete randomNumberGenerator;
}

void Comp2D::Game::finalizeDataManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeDataManager\n" );
	#endif

	delete dataManager;
}

void Comp2D::Game::finalizeTimeManager()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeTimeManager\n" );
	#endif

	delete timeManager;
}

void Comp2D::Game::finalizeAudio()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeAudio\n" );
	#endif

	Mix_CloseAudio();
	Mix_Quit();
}

void Comp2D::Game::finalizeImageLoader()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeImageLoader\n" );
	#endif

	IMG_Quit();
}

void Comp2D::Game::finalizeRenderer()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeRenderer\n" );
	#endif

	SDL_DestroyRenderer( renderer );
	renderer = nullptr;
}

void Comp2D::Game::finalizeGameWindow()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeGameWindow\n" );
	#endif

	SDL_DestroyWindow( window );
	window = nullptr;
}

void Comp2D::Game::finalizeGameSettings()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game finalizeGameSettings\n" );
	#endif

	delete gameSettings;
}

void Comp2D::Game::checkGameTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game checkTimedProcedures\n" );
	#endif

	Uint32 currentTime = timeManager->getTimeSinceSDLInitializationInMilliseconds();

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gameTimedProcedureIt = gameTimedProcedures.begin();
		gameTimedProcedureIt != gameTimedProcedures.end();
		++gameTimedProcedureIt
	)
	{
		Comp2D::Time::TimedProcedure* currentGameTimedProcedure = (*gameTimedProcedureIt);

		if( currentGameTimedProcedure->checkCallbackTime( currentTime ) )
		{
			gamePausableTimedProcedures.remove( currentGameTimedProcedure );
			gameTimedProcedures.remove( currentGameTimedProcedure );
			delete currentGameTimedProcedure;

			--gameTimedProcedureIt;
		}
	}
}

void Comp2D::Game::pauseGameTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game pauseGameTimedProcedures\n" );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gamePausableTimedProcedureIt = gamePausableTimedProcedures.begin();
		gamePausableTimedProcedureIt != gamePausableTimedProcedures.end();
		++gamePausableTimedProcedureIt
	)
	{
		(*gamePausableTimedProcedureIt)->pause();
	}
}

void Comp2D::Game::unpauseGameTimedProcedures()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game unpauseGameTimedProcedures\n" );
	#endif

	for
	(
		std::list<Comp2D::Time::TimedProcedure*>::iterator gamePausableTimedProcedureIt = gamePausableTimedProcedures.begin();
		gamePausableTimedProcedureIt != gamePausableTimedProcedures.end();
		++gamePausableTimedProcedureIt
	)
	{
		(*gamePausableTimedProcedureIt)->unpause();
	}
}

void Comp2D::Game::updateAverageFramePerSecond()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game updateAverageFramePerSecond\n" );
	#endif

	++totalRenderedFrames;

	averageFramesPerSecond = static_cast<Uint32>
	(
		round
		(
			static_cast<double>( totalRenderedFrames ) /
			( static_cast<double>( timeSinceFirstFrameTimer.getElapsedTimeInMilliseconds() ) / 1000.0 )
		)
	);
}

void Comp2D::Game::updateFramesPerSecond()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game updateFramesPerSecond\n" );
	#endif

	++totalRenderedFramesSinceLastFPSUpdate;

	if( ( timeOnLastFrameFinishedRendering - lastFPSUpdateTime ) >= 1000 )
	{
		framesPerSecond = totalRenderedFramesSinceLastFPSUpdate;

		totalRenderedFramesSinceLastFPSUpdate = 0;
		lastFPSUpdateTime = SDL_GetTicks();
	}
}

void Comp2D::Game::updateFramesPerSecondThroughDeltaTime()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game updateFramesPerSecondThroughDeltaTime\n" );
	#endif

	framesPerSecondThroughDeltaTime = static_cast<Uint32>( round( 1.0f / timeManager->getDeltaTimeInSeconds() ) );
}

void Comp2D::Game::callFunctionAfterTimeOnSeparateThread
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
			"Game callFunctionAfterTimeOnSeparateThread: callbackTimeInMilliseconds = %u\n",
			callbackTimeInMilliseconds
		);
	#endif

	//typedef Uint32 function_t( Uint32, void* );

	gameTimerFunctionsIDs.push_back
	(
		SDL_AddTimer
		(
			callbackTimeInMilliseconds,
			//timerFunction.target<function_t>(),
			timerFunction,
			param
		)
	);
}

void Comp2D::Game::callFunctionOnSeparateThread
(
	int (*separateThreadFunction)(void*),
	void* data,
	const std::string& threadName
)
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game callFunctionOnSeparateThread: threadName = %s\n", threadName.c_str() );
	#endif

	gameSeparateThreadFunctions.push_back
	(
		SDL_CreateThread
		(
			separateThreadFunction,
			threadName.c_str(),
			data
		)
	);
}

void Comp2D::Game::callProcedureAfterTimeOnGameThread
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
			"Game callProcedureAfterTimeOnGameThread: callbackTimeInMilliseconds = %u; pausable = %i\n",
			callbackTimeInMilliseconds,
			pausable
		);
	#endif

	Comp2D::Time::TimedProcedure* createdGameTimedProcedure = new Comp2D::Time::TimedProcedure
	(
		gameTimedProcedureID++,
		timedProcedure,
		timeManager->getTimeSinceSDLInitializationInMilliseconds() + callbackTimeInMilliseconds,
		pausable
	);

	if( createdGameTimedProcedure->isPausable() )
	{
		if( paused )
		{
			createdGameTimedProcedure->pause();
		}

		gamePausableTimedProcedures.push_back( createdGameTimedProcedure );
	}

	gameTimedProcedures.push_back( createdGameTimedProcedure );
}

void Comp2D::Game::pause( bool pauseTimeScale )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game pause\n" );
	#endif

	if( !paused )
	{
		timeManager->pause();

		pauseGameTimedProcedures();

		if( pauseTimeScale )
		{
			timeScaleOnPaused = timeManager->getTimeScale();

			timeManager->setTimeScale( 0.0f );

			pausedTimeScale = true;
		}

		gameStates[currentStateID]->pause();

		paused = true;
	}
}

void Comp2D::Game::quitGame()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game quitGame\n" );
	#endif

	quit = true;
}

void Comp2D::Game::reportError
(
	const std::string& errorTitle,
	const std::string& errorText,
	const char* errorData,
	bool quitGameAfterReport
)
{
	#ifdef DEBUG
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Game reportError: errorTitle = %s; errorText = %s; errorData = %s; quitGame = %i\n",
			errorTitle.c_str(),
			errorText.c_str(),
			errorData,
			quitGameAfterReport
		);
	#endif

	std::stringstream errorTextStringStream;
	errorTextStringStream.str( "" );

	errorTextStringStream << errorText;

	if( errorData )
	{
		errorTextStringStream << errorData;
	}

	errorTextStringStream << '\n';

	SDL_ShowSimpleMessageBox
	(
		SDL_MESSAGEBOX_ERROR,
		errorTitle.c_str(),
		errorTextStringStream.str().c_str(),
		window
	);

	if( quitGameAfterReport )
	{
		quitGame();
	}
}

void Comp2D::Game::setCameraPosition( const b2Vec2& position )
{
	#ifdef DEBUG
		/*
		SDL_LogDebug
		(
			SDL_LOG_CATEGORY_TEST,
			"Game setCameraPosition: position = ( %f, %f )\n",
			position.x,
			position.y
		);
		*/
	#endif

	cameraPosition.x = position.x;
	cameraPosition.y = position.y;
}

void Comp2D::Game::start()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game start\n" );
	#endif

	if( initialize() )
	{
		startUpdateLoop();
	}
	else
	{
		#ifdef DEBUG
			SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize!\n" );
		#endif
	}

	finalize();
}

void Comp2D::Game::startStateTransition( Uint32 nextStateID )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game startStateTransition: nextStateID = %u\n", nextStateID );
	#endif

	Comp2D::Game::nextStateID = nextStateID;
	inStateTransition = true;

	/*
	if( nextStateID == currentStateID )
	{
		gameStates[currentStateID]->resetState();
	}
	else
	{
		Comp2D::Game::nextStateID = nextStateID;
		inStateTransition = true;
	}
	*/
}

void Comp2D::Game::unpause()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game unpause\n" );
	#endif

	if( paused )
	{
		if( pausedTimeScale )
		{
			timeManager->setTimeScale( timeScaleOnPaused );

			pausedTimeScale = false;
		}

		gameStates[currentStateID]->unpause();

		unpauseGameTimedProcedures();

		timeManager->unpause();

		paused = false;
	}
}

bool Comp2D::Game::isPaused()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game isPaused\n" );
	#endif

	return paused;
}

Uint32 Comp2D::Game::getAverageFramesPerSecond()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getAverageFramePerSecond\n" );
	#endif

	return averageFramesPerSecond;
}

Uint32 Comp2D::Game::getCurrentStateID()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getCurrentStateID\n" );
	#endif

	return currentStateID;
}

Uint32 Comp2D::Game::getFramesPerSecond()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getFramesPerSecond\n" );
	#endif

	return framesPerSecond;
}

Uint32 Comp2D::Game::getFramesPerSecondThroughDeltaTime()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getFramesPerSecondThroughDeltaTime\n" );
	#endif

	return framesPerSecondThroughDeltaTime;
}

Uint32 Comp2D::Game::getWindowPixelFormat()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getWindowPixelFormat\n" );
	#endif

	return windowPixelFormat;
}

float Comp2D::Game::getCameraPositionX()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getCameraPositionX\n" );
	#endif

	return cameraPosition.x;
}

float Comp2D::Game::getCameraPositionY()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getCameraPositionY\n" );
	#endif

	return cameraPosition.y;
}

Comp2D::Utilities::Vector2D<int> Comp2D::Game::getCameraScreenPosition()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getCameraScreenPosition\n" );
	#endif

	int screenX = static_cast<int>( round( cameraPosition.x - Comp2D::Game::getCameraPositionX() ) );
	int screenY = static_cast<int>( round( cameraPosition.y - Comp2D::Game::getCameraPositionY() ) );

	return Comp2D::Utilities::Vector2D<int>( screenX, screenY );
}

const b2Vec2& Comp2D::Game::getCameraPosition()
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "Game getCameraPosition\n" );
	#endif

	return cameraPosition;
}
