/* AudioSettings.h -- 'Comp2D' Game Engine 'AudioSettings' class header file
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

#ifndef Comp2D_HEADERS_SETTINGS_AUDIOSETTINGS_H_
#define Comp2D_HEADERS_SETTINGS_AUDIOSETTINGS_H_

#include <SDL.h>

namespace Comp2D
{
	namespace Settings
	{
		class AudioSettings
		{
		private:
			int m_channels;
			int m_chunkSize;
			int m_frequency;
			int m_masterVolume;
			int m_musicVolume;
			int m_numberMixChannels;
			int m_soundEffectsVolume;
			int m_supportedFormatsFlags;

			Uint16 m_format;

		public:
			AudioSettings();

			~AudioSettings();

			void setMasterVolume( int volume );
			void setMusicVolume( int volume );
			void setSoundEffectsVolume( int volume );

			int getChannels() const;
			int getChunkSize() const;
			int getFrequency() const;
			int getMasterVolume() const;
			int getMusicVolume() const;
			int getNumberMixChannels() const;
			int getSoundEffectsVolume() const;
			int getSupportedFormatsFlags() const;

			Uint16 getFormat() const;

			float getMasterVolumePercentage() const;
		};
	}
}

#endif /* Comp2D_HEADERS_SETTINGS_AUDIOSETTINGS_H_ */
