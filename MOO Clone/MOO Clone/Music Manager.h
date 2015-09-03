#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

#include <SFML\Audio.hpp>

namespace MOO
{
	namespace Audio
	{
		class MusicManager
		{

		private:

			sf::Music currentSong;

			short int currentSongIndex;
			std::string currentPlaylist;

			std::unordered_map<std::string, std::vector<std::string> > playlists;

		public:

			MusicManager();
			
			void Reset();

			void Play();
			void Stop();
			void Pause();
			
			void NextSong();
			void PreviousSong();

			void ChangePlaylist( const std::string& listToPlay );
			void LoadNewPlaylist( const std::string& listToLoad );
		};
	}
}