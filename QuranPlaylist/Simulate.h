//
// Created by Mahmoud Elshafei on 12/1/2024.
//

#ifndef QURANPLAYLIST_SIMULATE_H
#define QURANPLAYLIST_SIMULATE_H

#include "Library.h"
#include "AudioPlayer.h"

void welcome() {
    startProgram();
    std::cout << "+=================================================================+" << std::endl;
    std::cout << "|            Welcome to our Qu'ran Playlist Manager               |" << std::endl;
}

void ManagerMenu() {
    std::cout << "+=================================================================+" << std::endl;
    std::cout << "|               Qu'ran Playlist Manager Menu                      |" << std::endl;
    std::cout << "+=================================================================+" << std::endl;
    std::cout << "| 1. Add a new playlist                                           |" << std::endl;
    std::cout << "| 2. Add Surah to an existing playlist                            |" << std::endl;
    std::cout << "| 3. Remove Surah from an existing playlist                       |" << std::endl;
    std::cout << "| 4. Shuffle the order of Library Playlists                       |" << std::endl;
    std::cout << "| 5. Display All Current Playlists                                |" << std::endl;
    std::cout << "| 6. Display all Playlists Surah                                  |" << std::endl;
    std::cout << "| 7. Display Surah in a specific playlist                         |" << std::endl;
    std::cout << "| 8. Play Surah from specific playlist                            |" << std::endl;
    std::cout << "|    Use Key (a) to play the previous Surah                       |" << std::endl;
    std::cout << "|    Use Key (d) to play the next Surah                           |" << std::endl;
    std::cout << "|    Use Key (w) to pause the current Surah                       |" << std::endl;
    std::cout << "|    Use Key (s) to resume the current Surah                      |" << std::endl;
    std::cout << "|    Press q to exit current playlist & return back to menu       |" << std::endl;
    std::cout << "| 9. Save an existing playlist to a file                          |" << std::endl;
    std::cout << "| 10. Load an existing playlist from a file                       |" << std::endl;
    std::cout << "| 11. Remove an existing playlist                                 |" << std::endl;
    std::cout << "| 12. Exit                                                        |" << std::endl;
    std::cout << "+=================================================================+" << std::endl;
    std::cout << "Your choice: ";
}

Surah getSurahInformation() {
    size_t id;
    std::string name, type, path;
    size_t duration;

    std::cout << "Enter Surah ID: ";
    while (!(std::cin >> id)) { // Validate numeric input
        std::cerr << "Invalid input. Please enter a valid Surah ID: ";
        std::cin.clear();
        std::cin.ignore();
    }

    std::cin.ignore();
    std::cout << "Enter Surah name: ";
    std::getline(std::cin, name);
    if (name.empty()) {
        std::cerr << "Surah name cannot be empty!" << std::endl;
        return getSurahInformation();
    }

    std::cout << "Enter Surah type: ";
    std::getline(std::cin, type);

    std::cout << "Enter Surah path: ";
    std::getline(std::cin, path);

    std::cout << "Enter Surah duration: ";
    while (!(std::cin >> duration)) { // Validate numeric input
        std::cerr << "Invalid input. Please enter a valid duration: ";
        std::cin.clear();
        std::cin.ignore();
    }

    return Surah(id, name, type, path, duration);
}


//Surah getSurahInformation() {
//    std::cout << "Enter Surah ID: ";
//    size_t id;
//    std::cin >> id;
//    std::cout << std::endl;
//    std::cout << "Enter Surah name: ";
//    std::cin.ignore();
//    std::string name;
//    std::getline(std::cin, name);
//    std::cout << std::endl;
//    std::cout << "Enter Surah type: ";
//    std::string type;
//    std::getline(std::cin, type);
//    std::cout << std::endl;
//    std::cout << "Enter Surah path: ";
//    std::string path;
//    std::getline(std::cin, path);
//    std::cout << std::endl;
//    std::cout << "Enter Surah Duration: ";
//    size_t duration;
//    std::cin >> duration;
//    std::cout << std::endl;
//    Surah surah(id, name, type, path, duration);
//    return surah;
//}



PlayList getPlayListInformation() {
    std::string playlistName;
    std::cout << "Enter playlist Name: \n";
//    std::cin.ignore();
    std::getline(std::cin, playlistName);
    if (playlistName.empty()) {
        std::cerr << "Playlist name cannot be empty!" << std::endl;
        return getPlayListInformation();
    }
    return PlayList(playlistName);
}

//PlayList getPlayListInformation() {
//    std::string playlistName;
//    std::cout << "Enter playlist Name: " << std::endl;
//    std::cin.ignore();
//    std::getline(std::cin, playlistName);
//    PlayList playList(playlistName);
//    return playList;
//}

void addNewPlayList(Library &library, PlayList &playList) {

    library.addNewPlayList(playList);
    std::cout << "Playlist added successfully to your library.." << std::endl;
}

void addSurahToAnExistingPlayList(PlayList &playList, Surah &surah) {
    playList.addSurah(surah);
    std::cout << "Surah added to " << playList.getReader() << " playlist successfully.." << std::endl;
}

void removeSurahFromExistingPlayList(PlayList &playList, Surah &surah) {
    playList.removeSurah(surah);
    std::cout << "Surah " << surah.getName() << " remove from " << playList.getReader() << " playlist successfully.." << std::endl;
}

void shuffleTheLibraryOrder(Library &library) {
    library.shufflePlaylists();
}

void displayAllCurrentPlayListsWithInformation(Library &library) {
    library.printWholePlaylistsWithInformation();
}

void displayAllCurrentPlayListsNames(Library &library) {
    library.printPlaylistsNames();
}

void displaySpecificPlaylist(PlayList &playList) {
    std::cout << playList;
}


void playPlaylist(PlayList& playList) {
    playSurah(playList);
}

void playNext(PlayList& playList) {
    getNext(playList);
}

void playPrevious(PlayList& playList) {
    getPrev(playList);
}

void pausePlaylist(PlayList& playList) {
    pauseSurah(playList);
}

void resumePlaylist(PlayList& playList) {
    resumeSurah(playList);
}

//void playSurah(const std::string &SurahName, const std::string& path, size_t durationMs) {
////    playAudio(SurahName, path);
//    playSound(SurahName, path, durationMs);
//}

void saveLibraryToFile(Library &library) {
    library.saveToFile();
}

void loadLibraryFromFile(Library &library) {
    library.loadFromFile();
}

void removePlaylistFromLibrary(Library& library, PlayList& playList) {
    library.removePlayList(playList);
}

void Exit() {
    std::cout << "Bye Bye.. See U Later <3.." << std::endl;
}



#endif //QURANPLAYLIST_SIMULATE_H
