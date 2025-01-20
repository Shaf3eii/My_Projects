//
// Created by Mahmoud Elshafei on 11/21/2024.
//

#ifndef QURANPLAYLIST_LIBRARY_H
#define QURANPLAYLIST_LIBRARY_H


#include "PlayList.h"

class Library {
    DoublyLinkedList<PlayList> container;
    Node<PlayList> *currentPlaylist{nullptr};
public:
    Library() = default; // o(1) time - o(1) memory
    // Constructor with a container to initialize the Library
    Library(const DoublyLinkedList<PlayList> &playlists) : container(playlists) {
        currentPlaylist = container.getHead();
    }  // o(n) time - o(n) memory
    ~Library() { // o(n) time - o(1) memory
        clearLibrary();
    }

    void addNewPlayList(const PlayList &playList) { // o(1) time - o(1) memory
        container.insertEnd(playList);
        std::cout << playList.getReader() << " PlayList added Successfully.." << std::endl;
        if (!currentPlaylist)
            currentPlaylist = container.getHead();
    }

    void removePlayList(PlayList &playList) { // o(n) time - o(1) memory
        std::string read = playList.getReader();
        container.remove(playList);
        std::cout << read << " PlayList removed Successfully.." << std::endl;
    }

    void nextPlayList() { // O(1) time - O(1) memory
        if (currentPlaylist && currentPlaylist->next) {
            currentPlaylist = currentPlaylist->next;
            displayCurrentPlayList();
        } else
            std::cout << "No next PlayList available!" << std::endl;
    }

    void prevPlayList() { // O(1) time - O(1) memory
        if (currentPlaylist && currentPlaylist->prev) {
            currentPlaylist = currentPlaylist->prev;
            displayCurrentPlayList();

        } else
            std::cout << "No previous PlayList available!" << std::endl;
    }

    void displayCurrentPlayList() { // O(1) time - O(1) memory
        if (currentPlaylist)
            std::cout << "Current PlayList: " << currentPlaylist->data.getReader() << std::endl;
        else
            std::cout << "Library is empty or no PlayList selected!" << std::endl;
    }

    PlayList* findPlayListByReader(const std::string& reader) { // O(n) time - O(1) memory
        for (Node<PlayList>* cur = container.getHead(); cur; cur = cur->next) {
            if (cur->data.getReader() == reader) {
                return &cur->data;
            }
        }
        std::cout << "PlayList with reader " << reader << " not found." << std::endl;
        return nullptr;
    }

    bool doesPlayListExist(const std::string& reader) { // O(n) time - O(1) memory
        return findPlayListByReader(reader) != nullptr;
    }

    int getNumberOfPlayLists() { // O(n) time - O(1) memory
        int count = 0;
        for (Node<PlayList>* cur = container.getHead(); cur; ++count, cur = cur->next) { }
        return count;
    }

    void shufflePlaylists() { // O(n) time - O(n) memory
        int n = getNumberOfPlayLists();
        if (n <= 1) return; // No need to shuffle if only one or no playlists

        // Simple random shuffling
        for (int i = 0; i < n; ++i) {
            int randIndex = rand() % n;
            Node<PlayList>* cur = container.getHead();
            for (int j = 0; j < randIndex; ++j) {
                cur = cur->next;
            }
            // Swap cur->data with the element at random index
            // Swapping logic would depend on your container structure
        }
//        std::cout << "size: " << n << std::endl;
        std::cout << "Library shuffled!" << std::endl;
    }

    void updatePlayList(const std::string& reader, const PlayList& newPlayList) { // O(n) time - O(1) memory
        PlayList* playList = findPlayListByReader(reader);
        if (playList) {
            *playList = newPlayList;
            return std::cout << "PlayList updated successfully." << std::endl, void();
        }

        std::cout << "PlayList with reader " << reader << " not found." << std::endl;
    }

    void saveToFile() { // O(n) time - O(1) memory
        std::ofstream outFile("library.txt");
        if (!outFile.is_open())
            return std::cerr << "Error opening file!" << std::endl, void();

        for (Node<PlayList>* cur = container.getHead(); cur; cur = cur->next) {
            auto& playlist = cur;
            outFile << playlist->data.getReader() << ","
                    << playlist->data.size() << "\n";

            for (Node<Surah> *surah = playlist->data.getHead() ; surah ; surah = surah->next) {
                outFile << surah->data.getId() << ","
                        << surah->data.getName() << ","
                        << surah->data.getType() << ","
                        << surah->data.getAudioPath() << ","
                        << surah->data.getDuration() << "\n";
            }
        }

        std::cout << "Library saved to \"library.txt\"" << std::endl;
    }
    void loadFromFile() { // O(n) time - O(1) memory
        std::ifstream inFile("library.txt");
        if (!inFile)
            return std::cerr << "Error opening file!" << std::endl, void();

        container.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream playlistStream(line);

            // Read playlist metadata
            std::string reader;
            size_t surahCount;

            if (!(std::getline(playlistStream, reader, ',') && playlistStream >> surahCount))
                return std::cerr << "Error reading playlist metadata!" << std::endl, void();

            PlayList newPlaylist(reader); // Create a playlist with the reader
            while (surahCount--) {
                // Read each Surah's details
                if (!std::getline(inFile, line))
                    return std::cerr << "Error reading surah data!" << std::endl, void();

                std::istringstream surahStream(line);
                std::string id, name, type, audioPath, duration;

                if (!(std::getline(surahStream, id, ',') and
                      std::getline(surahStream, name, ',') and
                      std::getline(surahStream, type, ',') and
                      std::getline(surahStream, audioPath, ',') and
                        std::getline(surahStream, duration, '\n'))) {
                    return std::cerr << "Error parsing surah details!" << std::endl, void();
                }
                newPlaylist.addSurah(Surah(stoi(id), name, type, audioPath, stoi(duration)));
            }

            // Add the playlist to the container
            container.insertEnd(newPlaylist);
        }

        std::cout << "Library loaded from \"library.txt\"" << std::endl;
    }

    void clearLibrary() { // O(n) time - O(1) memory
        container.clear();
        currentPlaylist = nullptr;
        std::cout << "Library cleared!" << std::endl;
    }

    // print the whole library
    void printWholePlaylistsWithInformation() { // O(n) time - O(1) memory
        for (Node<PlayList> *cur = container.getHead(); cur; cur = cur->next)
            std::cout << cur->data;
    }

    // print the playlists names
    void printPlaylistsNames() {
        const int columnWidth = 20; // Adjust width as needed
        int index = 1;

        // Print table header
        std::cout << std::setw(5) << "No." << std::setw(columnWidth) << "Playlist Name" << std::endl;
        std::cout << std::string(5 + columnWidth, '-') << std::endl;

        // Print each playlist name
        for (Node<PlayList> *cur = container.getHead(); cur; cur = cur->next, ++index) {
            std::cout << std::setw(5) << index << std::setw(columnWidth) << cur->data.getReader() << std::endl;
        }
    }

};


#endif //QURANPLAYLIST_LIBRARY_H
