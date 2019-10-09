/* AudioSettings.cpp -- 'Comp2D' Game Engine 'AudioSettings' class source file
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

#include "Comp2D/Headers/Settings/AudioSettings.h"

#include <cmath>

#include <SDL.h>
#include <SDL_mixer.h>

Comp2D::Settings::AudioSettings::AudioSettings()
	:
	m_channels( 2 ),
	m_chunkSize( 2048 ),
	m_frequency( 44100 ),
	m_masterVolume( MIX_MAX_VOLUME ),
	m_musicVolume( MIX_MAX_VOLUME ),
	m_numberMixChannels( 16 ),
	m_soundEffectsVolume( MIX_MAX_VOLUME ),
	m_supportedFormatsFlags
	(
		MIX_INIT_OGG
		//| MIX_INIT_MP3
	),
	m_format( MIX_DEFAULT_FORMAT )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings Constructor body Start\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings Constructor body End\n" );
	#endif
}

Comp2D::Settings::AudioSettings::~AudioSettings()
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings Destroying\n" );
	#endif

	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings Destroyed\n" );
	#endif
}

void Comp2D::Settings::AudioSettings::setMasterVolume( int volume )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings setMasterVolume: volume = %i\n", volume );
	#endif

	m_masterVolume = volume % ( MIX_MAX_VOLUME + 1 );

	float masterVolumePercentage = getMasterVolumePercentage();

	Mix_VolumeMusic( static_cast<int>( round( getMusicVolume() * masterVolumePercentage ) ) );
	Mix_Volume( -1, static_cast<int>(round( getSoundEffectsVolume() * masterVolumePercentage ) ) );
}

void Comp2D::Settings::AudioSettings::setMusicVolume( int volume )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings setMusicVolume: volume = %i\n", volume );
	#endif

	m_musicVolume = volume % ( MIX_MAX_VOLUME + 1 );

	Mix_VolumeMusic( static_cast<int>( round( getMusicVolume() * getMasterVolumePercentage() ) ) );
}

void Comp2D::Settings::AudioSettings::setSoundEffectsVolume( int volume )
{
	#ifdef DEBUG
		SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings setSoundEffectsVolume: volume = %i\n", volume );
	#endif

	m_soundEffectsVolume = volume % ( MIX_MAX_VOLUME + 1 );

	Mix_Volume( -1, static_cast<int>( round( getSoundEffectsVolume() * getMasterVolumePercentage() ) ) );
}

int Comp2D::Settings::AudioSettings::getChannels() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getChannels\n" );
	#endif

	return m_channels;
}

int Comp2D::Settings::AudioSettings::getChunkSize() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getChunkSize\n" );
	#endif

	return m_chunkSize;
}

int Comp2D::Settings::AudioSettings::getFrequency() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getFrequency\n" );
	#endif

	return m_frequency;
}

int Comp2D::Settings::AudioSettings::getMasterVolume() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getMasterVolume\n" );
	#endif

	return m_masterVolume;
}

int Comp2D::Settings::AudioSettings::getMusicVolume() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getMusicVolume\n" );
	#endif

	return m_musicVolume;
}

int Comp2D::Settings::AudioSettings::getNumberMixChannels() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getNumberMixChannels\n" );
	#endif

	return m_numberMixChannels;
}

int Comp2D::Settings::AudioSettings::getSoundEffectsVolume() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getSoundEffectsVolume\n" );
	#endif

	return m_soundEffectsVolume;
}

int Comp2D::Settings::AudioSettings::getSupportedFormatsFlags() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getSupportedFormatsFlags\n" );
	#endif

	return m_supportedFormatsFlags;
}

Uint16 Comp2D::Settings::AudioSettings::getFormat() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getFormat\n" );
	#endif

	return m_format;
}

float Comp2D::Settings::AudioSettings::getMasterVolumePercentage() const
{
	#ifdef DEBUG
		//SDL_LogDebug( SDL_LOG_CATEGORY_TEST, "AudioSettings getMasterVolumePercentage\n" );
	#endif

	return static_cast<float>( m_masterVolume ) / static_cast<float>( MIX_MAX_VOLUME );
}
