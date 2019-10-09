/* Main.cpp -- 'Comp2D' Game Engine main function code
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

#ifdef DEBUG
	#include <sstream>
	#include <string>
#endif

#ifdef LOG_TO_TEXT_FILE
	#include <chrono>
	#include <iomanip>
	#include <iostream>
	#include <fstream>
#endif

#include <SDL.h>

#include "Comp2D/Headers/Game.h"

#ifdef LOG_TO_TEXT_FILE
	std::string g_logFileName;

	SDL_RWops* g_logTextFile;

	void logOutputToConsoleAndFileFunction
	(
		void* userdata,
		int category,
		SDL_LogPriority priority,
		const char* message
	)
	{
		std::stringstream completeMessageStringStream;
		completeMessageStringStream.str( "" );

		switch( priority )
		{
			case SDL_LOG_PRIORITY_CRITICAL:
				completeMessageStringStream << "CRITICAL (";
				break;
			case SDL_LOG_PRIORITY_DEBUG:
				completeMessageStringStream << "DEBUG (";
				break;
			case SDL_LOG_PRIORITY_ERROR:
				completeMessageStringStream << "ERROR (";
				break;
			case SDL_LOG_PRIORITY_INFO:
				completeMessageStringStream << "INFO (";
				break;
			case SDL_LOG_PRIORITY_VERBOSE:
				completeMessageStringStream << "VERBOSE (";
				break;
			case SDL_LOG_PRIORITY_WARN:
				completeMessageStringStream << "WARN (";
				break;
			default:
				completeMessageStringStream << "UNKNOWN PRIORITY (";
				break;
		}

		switch( category )
		{
			case SDL_LOG_CATEGORY_APPLICATION:
				completeMessageStringStream << "APPLICATION): ";
				break;
			case SDL_LOG_CATEGORY_ASSERT:
				completeMessageStringStream << "ASSERT): ";
				break;
			case SDL_LOG_CATEGORY_AUDIO:
				completeMessageStringStream << "AUDIO): ";
				break;
			case SDL_LOG_CATEGORY_CUSTOM:
				completeMessageStringStream << "CUSTOM): ";
				break;
			case SDL_LOG_CATEGORY_ERROR:
				completeMessageStringStream << "ERROR): ";
				break;
			case SDL_LOG_CATEGORY_INPUT:
				completeMessageStringStream << "INPUT): ";
				break;
			case SDL_LOG_CATEGORY_RENDER:
				completeMessageStringStream << "RENDER): ";
				break;
			case SDL_LOG_CATEGORY_SYSTEM:
				completeMessageStringStream << "SYSTEM): ";
				break;
			case SDL_LOG_CATEGORY_TEST:
				completeMessageStringStream << "TEST): ";
				break;
			case SDL_LOG_CATEGORY_VIDEO:
				completeMessageStringStream << "VIDEO): ";
				break;
			default:
				completeMessageStringStream << "UNKNOWN CATEGORY): ";
				break;
		}

		completeMessageStringStream << message << '\n';

	    std::ofstream myfile;

		myfile.open( g_logFileName.c_str(), std::ios::out | std::ios::app );

		myfile << completeMessageStringStream.str().c_str();

		myfile.close();

	    std::cout << completeMessageStringStream.str().c_str();
	}
#endif

int main( int argc, char* argv[] )
{
	#ifdef LOG_TO_TEXT_FILE
		std::chrono::system_clock::time_point timeAtProgramStart = std::chrono::system_clock::now();
		std::time_t timeAtProgramStart_c = std::chrono::system_clock::to_time_t( timeAtProgramStart );

		std::stringstream logFileNameStringStream;
		logFileNameStringStream.str( "" );

		struct tm timeinfo;
		localtime_s( &timeinfo, &timeAtProgramStart_c );

		logFileNameStringStream << "Logs/log_" << std::put_time( &timeinfo, "%Y_%m_%d_%H_%M_%S" ) << ".txt";

		g_logFileName = logFileNameStringStream.str();

		//void (*defaultLogOutputFunction)(void*, int, SDL_LogPriority, const char*);
		//void* defaultLogOutputFunctionUserData;
		//SDL_LogGetOutputFunction( &defaultLogOutputFunction, &defaultLogOutputFunctionUserData );

		SDL_LogSetOutputFunction( logOutputToConsoleAndFileFunction, nullptr );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "main body start\n" );

		{
			std::stringstream argvStringStream;
			argvStringStream.str( "" );

			for( int argIndex = 0; argIndex < argc; ++argIndex )
			{
				argvStringStream << argv[argIndex] << " ";
			}

			SDL_LogDebug
			(
				SDL_LOG_CATEGORY_TEST,
				"argc = %i; argv = %s\n",
				argc,
				argvStringStream.str().c_str()
			);
		}
	#endif

	Comp2D::Game::start();

	#ifdef LOG_TO_TEXT_FILE
		//SDL_LogSetOutputFunction( defaultLogOutputFunction, defaultLogOutputFunctionUserData );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "main body end\n" );
	#endif

	return 0;
}
