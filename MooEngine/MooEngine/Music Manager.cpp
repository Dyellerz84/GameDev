#include "Music Manager.h"

#include <fstream>

MOO::Audio::MusicManager::MusicManager()
{

}

void MOO::Audio::MusicManager::Reset()
{
	currentSong.stop();
	playlists.clear();
}

void MOO::Audio::MusicManager::Play()
{
	currentSong.play();
}

void MOO::Audio::MusicManager::Stop()
{
	currentSong.stop();
}

void MOO::Audio::MusicManager::Pause()
{
	currentSong.pause();
}

void MOO::Audio::MusicManager::NextSong()
{
	currentSongIndex++;

	if( currentSongIndex >= playlists[currentPlaylist].size() )
	{
		currentSongIndex = 0;
	}

	currentSong.openFromFile( playlists[currentPlaylist][currentSongIndex] );
	currentSong.play();
}

void MOO::Audio::MusicManager::PreviousSong()
{
	currentSongIndex--;

	if( currentSongIndex < 0 )
	{
		currentSongIndex = playlists[currentPlaylist].size() - 1;
	}

	currentSong.openFromFile( playlists[currentPlaylist][currentSongIndex] );
	currentSong.play();
}

void MOO::Audio::MusicManager::ChangePlaylist( const std::string& listToPlay )
{
	currentPlaylist = listToPlay;
	currentSongIndex = 0;

	currentSong.openFromFile( playlists[currentPlaylist][currentSongIndex] );
	currentSong.play();
}

void MOO::Audio::MusicManager::LoadNewPlaylist( const std::string& listToLoad )
{
	if( playlists.find( listToLoad ) != playlists.end() )
	{
		std::ifstream fromFile( listToLoad.c_str() );

		while( fromFile )
		{
			std::string temp;

			fromFile >> temp;

			playlists[listToLoad].push_back(temp);
		}
	}
}