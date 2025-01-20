#include "Library.h"
#include "Simulate.h"

int main() {
    system("color 0A");
    welcome();
    Library MyLibrary;
    int op;
    bool flag = true;
    do {
        ManagerMenu();
        std::cin >> op;
        std::cin.ignore();
        switch (op) {
            case 1: {
                PlayList playList = getPlayListInformation();
                if (MyLibrary.doesPlayListExist(playList.getReader())) {
                    std::cerr << "This Playlist already exist.." << std::endl;
                    break;
                }
                addNewPlayList(MyLibrary, playList);
                break;
            }
            case 2: {
                std::cout << "Current playlists: " << std::endl;
                displayAllCurrentPlayListsNames(MyLibrary);
                std::cout << "Enter the playlist name: " << std::endl;
                std::string playlistName;
                std::getline(std::cin, playlistName);
                if (!MyLibrary.doesPlayListExist(playlistName)) {
                    std::cerr << "No playlist with this name.." << std::endl;
                    break;
                }
                PlayList *playlist;
                playlist = MyLibrary.findPlayListByReader(playlistName);
                if (!playlist) {
                    std::cerr << "Error finding playlist." << std::endl;
                    break;
                }
                std::cout << "Enter the surah information: " << std::endl;
                Surah surah = getSurahInformation();
                addSurahToAnExistingPlayList(*playlist, surah);
                break;
            }
            case 3: {
                std::cout << "Current playlists: " << std::endl;
                displayAllCurrentPlayListsNames(MyLibrary);
                std::cout << "Enter the playlist name: " << std::endl;
                std::string playlistName;
                std::getline(std::cin, playlistName);
                if (!MyLibrary.doesPlayListExist(playlistName)) {
                    std::cerr << "No playlist with this name.." << std::endl;
                    break;
                }
                PlayList *playlist;
                playlist = MyLibrary.findPlayListByReader(playlistName);
                std::cout << "Enter the surah name: " << std::endl;
                std::string surahName;
                std::getline(std::cin, surahName);
                Surah *surah = playlist->getSurahByName(surahName);
                removeSurahFromExistingPlayList(*playlist, *surah);
                break;
            }
            case 4: {
                shuffleTheLibraryOrder(MyLibrary);
                break;
            }
            case 5: {
                displayAllCurrentPlayListsNames(MyLibrary);
                break;
            }
            case 6: {
                displayAllCurrentPlayListsWithInformation(MyLibrary);
                break;
            }
            case 7: {
                std::cout << "Current playlists: " << std::endl;
                displayAllCurrentPlayListsNames(MyLibrary);
                std::cout << "Enter the playlist name: " << std::endl;
                std::string playlistName;
                std::getline(std::cin, playlistName);
                if (!MyLibrary.doesPlayListExist(playlistName)) {
                    std::cerr << "No playlist with this name.." << std::endl;
                    break;
                }
                PlayList *playlist;
                playlist = MyLibrary.findPlayListByReader(playlistName);
                if (!playlist) {
                    std::cerr << "Error finding playlist." << std::endl;
                    break;
                }
                displaySpecificPlaylist(*playlist);
                break;
            }
            case 8: { // simulate the audio player
                // put the logic here
                std::cout << "Current playlists: " << std::endl;
                displayAllCurrentPlayListsNames(MyLibrary);
                std::cout << "Enter the playlist name: " << std::endl;
                std::string playlistName;
                std::getline(std::cin, playlistName);
                if (!MyLibrary.doesPlayListExist(playlistName)) {
                    std::cerr << "No playlist with this name.." << std::endl;
                    break;
                }
                PlayList *playlist;
                playlist = MyLibrary.findPlayListByReader(playlistName);
                displaySpecificPlaylist(*playlist);
                std::cout << "Starting playlist: " << playlistName << std::endl;
                playPlaylist(*playlist);
                bool stopPlayback = false;
                while (!stopPlayback) {
                    char pressed = _getch();
                    if (pressed == 'q') { // Quit playlist
                        stopPlayback = true;
                        currentSurah = nullptr;
                        pausePlaylist(*playlist);
                    } else if (pressed == 'a') { // a (previous Surah)
                        playPrevious(*playlist);
                    } else if (pressed == 'd') { // d (next Surah)
                        playNext(*playlist);
                    } else if (pressed == 'w') { // w (pause)
                        pausePlaylist(*playlist);
                    } else if (pressed == 's') { // s (resume)
                        resumePlaylist(*playlist);
                    }
                }
                break;
            }
            case 9: {
                saveLibraryToFile(MyLibrary);
                break;
            }
            case 10: {
                loadLibraryFromFile(MyLibrary);
                break;
            }
            case 11: {
                std::cout << "Current playlists: " << std::endl;
                displayAllCurrentPlayListsNames(MyLibrary);
                std::cout << "Enter the playlist name: " << std::endl;
                std::string playlistName;
                std::getline(std::cin, playlistName);
                if (!MyLibrary.doesPlayListExist(playlistName)) {
                    std::cerr << "No playlist with this name.." << std::endl;
                    break;
                }
                PlayList *playlist;
                if (!playlist) {
                    std::cerr << "Error finding playlist." << std::endl;
                    break;
                }
                playlist = MyLibrary.findPlayListByReader(playlistName);
                removePlaylistFromLibrary(MyLibrary, *playlist);
                break;
            }
            case 12: {
                Exit();
                flag = false;
                break;
            }
            default:
                std::cout << "Enter a valid choice from 1 to 12 " << std::endl;
        }
    } while (flag);

//    system("pause");
    return 0;
}
