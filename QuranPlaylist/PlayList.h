//
// Created by Mahmoud Elshafei on 11/16/2024.
//

#ifndef QURANPLAYLIST_PLAYLIST_H
#define QURANPLAYLIST_PLAYLIST_H


#include "DoublyLinkedList.h"
#include "Surah.h"
#include <fstream>

class PlayList {
    DoublyLinkedList<Surah> playlist;
    std::string reader;
    Node<Surah> *currentSurah{nullptr};
public:
    PlayList() = default; // O(1) time - O(1) memory
    explicit PlayList(const std::string &reader) : reader(reader) {} // O(1) time - O(1) memory
    ~PlayList() { // O(n) time - O(1) memory
        playlist.clear();
        currentSurah = nullptr;
    }

    bool operator==(PlayList &other) const {
        return (playlist == other.playlist && reader == other.reader);
    }

    // add a new surah to the playlist
    void addSurah(const Surah &surah) { // O(1) time - O(1) memory
        playlist.insertEnd(surah);
        if (!currentSurah)
            currentSurah = playlist.getHead();
    }

    // remove an existing surah to the playlist
    void removeSurah(const Surah &surah) { // O(1) time - O(1) memory
        playlist.remove(surah);
    }

    Surah *getSurahByName(const std::string &surahName) {
        for (auto cur = playlist.getHead(); cur; cur = cur->next) {
            if (cur->data.getName() == surahName)
                return &cur->data;
        }
        return nullptr;
    }

    // get the next surah in the playlist
    Node<Surah> *nextSurah() { // O(1) time - O(1) memory
        if (currentSurah) {
            if (currentSurah->next) {
                currentSurah = currentSurah->next; // Move to the next Surah
            } else {
                currentSurah = playlist.getHead(); // Loop back to the start of the playlist
            }
            return currentSurah;
        } else {
            return nullptr;
        }

//        if (currentSurah && currentSurah->next) {
//            currentSurah = currentSurah->next;
////            displayCurrent();
//        } else
//            std::cout << "No next Surah available!" << std::endl;
    }

    // get the previous surah in the playlist
    Node<Surah>* prevSurah() {
        if (currentSurah) {
            if (currentSurah->prev) {
                currentSurah = currentSurah->prev; // Move to the previous Surah
            } else {
                currentSurah = playlist.getTail(); // Loop back to the end of the playlist
            }
            return currentSurah;
        } else {
            return nullptr;
        }

//        if (!currentSurah->prev)
//        if (currentSurah && currentSurah->prev) {
//            currentSurah = currentSurah->prev;
////            displayCurrent();
//        } else
//            std::cout << "No previous Surah available!" << std::endl;
    }

    // get the start of the playlist
    void start() { // O(1) time - O(1) memory
        currentSurah = playlist.getHead();
//        displayCurrent();
    }

    // return to the start of the playlist
    void restart() { // O(1) time - O(1) memory
        start();
    }

    std::string getReader() const {
        return reader;
    }

    // go to an existing surah in the playlist
    void jumpToSurah(const Surah &surah) { // O(n) time - O(1) memory
        Node<Surah> *temp = playlist.find(surah);
        if (temp)
            currentSurah = temp;
        else
            std::cout << "Surah not found in this playlist!" << std::endl;
//        displayCurrent();
    }

    // display the current playing
    void displayCurrent() const { // O(1) time - O(1) memory
        if (currentSurah)
            std::cout << "Now playing: " << currentSurah->data.getName() << std::endl;
        else
            std::cout << "Playlist is empty or no Surah selected!" << std::endl;
    }

    Surah *getCurrentSurah() {
        return reinterpret_cast<Surah *>(currentSurah);
    }

    // get the total time of the playlist
    size_t getTotalDuration() { // O(n) time - O(1) memory
        size_t tot = 0;
        for (Node<Surah> *cur = playlist.getHead(); cur; cur = cur->next)
            tot += cur->data.getDuration();

        return tot;
    }

    // get the total size of the playlist
    size_t size() const { // O(1) time - O(1) memory
        return playlist.size();
    }

    // save the current playlist to a file
    void saveToFile() {
        std::ofstream outfile("playlists.txt");
        if (!outfile)
            return std::cerr << "Error opening file for writing..\n", void();
        if (outfile.is_open()) {
            Node<Surah> *temp = playlist.getHead();
            outfile << reader << "\n";
            while (temp) {
                outfile << temp->data.getId() << ","
                        << temp->data.getName() << ","
                        << temp->data.getType() << ","
                        << temp->data.getAudioPath() << ","
                        << temp->data.getDuration() << "\n";
                temp = temp->next;
            }
            outfile.close();
            std::cout << "Playlist saved to file successfully..!" << std::endl;
        }
    }

    // get a playlist from a file
    void loadFromFile() {
        std::ifstream infile("playlists.txt");
        if (!infile)
            return std::cerr << "Error opening file for reading..\n", void();
        if (infile.is_open()) {
            playlist.clear();
            currentSurah = nullptr;
            std::string input;
            std::getline(infile, input);
            reader = input;
            while (std::getline(infile, input)) {
                std::istringstream ss(input);
                std::string id, name, type, path, duration;
                std::getline(ss, id, ',');
                std::getline(ss, name, ',');
                std::getline(ss, type, ',');
                std::getline(ss, path, ',');
                std::getline(ss, duration, '\n');
                Surah surah(std::stoi(id), name, type, path, std::stoi(duration));
                playlist.insertEnd(surah);
            }
            currentSurah = playlist.getHead();
            infile.close();
            std::cout << "Playlist loaded from file successfully..!" << std::endl;
        }
    }

    // print the playlist
    void print() {
        std::cout << std::setw(10) << "| " << reader << " PlayList |" << std::endl;
        for (Node<Surah> *cur = playlist.getHead(); cur; cur = cur->next) {
            std::cout << cur->data;
        }
    }

    // print the playlist a formal way
    friend std::ostream &operator<<(std::ostream &out, PlayList &playList1) {
//        out << std::flush;  // Clear the output buffer

        const int width = 20;  // Column width for uniform spacing

        out << std::setw(width * 5 / 2 - 4) << "| " << playList1.reader << " PlayList |" << std::endl;
        out
                << "+-----+--------------+----------+-------+----------------------------------------------------------------------+"
                << std::endl;
        out << "| " << std::left << std::setw(4) << "ID"
            << "| " << std::left << std::setw(13) << "Name"
            << "| " << std::left << std::setw(9) << "Type"
            << "| " << std::left << std::setw(6) << "Time"
            << "| " << std::left << std::setw(68) << "Audio Path" << " |" << std::endl;
        out
                << "+-----+--------------+----------+-------+----------------------------------------------------------------------+"
                << std::endl;

        for (Node<Surah> *cur = playList1.playlist.getHead(); cur; cur = cur->next) {
            out << "| " << std::left << std::setw(4) << cur->data.getId()
                << "| " << std::left << std::setw(13) << cur->data.getName()
                << "| " << std::left << std::setw(9) << cur->data.getType()
                << "| " << std::left << std::setw(6) << cur->data.getDuration()
                << "| " << std::left << std::setw(68) << cur->data.getAudioPath() << " |" << std::endl;
        }
        out
                << "+-----+--------------+----------+-------+----------------------------------------------------------------------+"
                << std::endl;
        return out;
    }
//    friend std::ostream& operator<<(std::ostream &out, PlayList &playList1) {
////        out << std::flush;  // Clear the output buffer
//
//        const int width = 20;  // Column width for uniform spacing
//
//        out << std::setw(width * 5 / 2 - 4) << "| " << playList1.reader << " PlayList |" << std::endl;
//        out << "+---------------------+---------------------+---------------------+---------------------+----------------------+" << std::endl;
//        out << "| " << std::left << std::setw(width) << "Surah ID"
//            << "| " << std::left << std::setw(width) << "Name"
//            << "| " << std::left << std::setw(width) << "Type"
//            << "| " << std::left << std::setw(width) << "Audio Path"
//            << "| " << std::left << std::setw(width) << "Duration" << " |" << std::endl;
//        out << "+---------------------+---------------------+---------------------+---------------------+----------------------+" << std::endl;
//
//        for (Node<Surah>* cur = playList1.playlist.getHead(); cur; cur = cur->next) {
//            out << "| " << std::left << std::setw(width) << cur->data.getId()
//                << "| " << std::left << std::setw(width) << cur->data.getName()
//                << "| " << std::left << std::setw(width) << cur->data.getType()
//                << "| " << std::left << std::setw(width) << cur->data.getAudioPath()
//                << "| " << std::left << std::setw(width) << cur->data.getDuration() << " |" << std::endl;
//        }
//        out << "+---------------------+---------------------+---------------------+---------------------+----------------------+" << std::endl;
//        return out;
//    }

    friend std::istream &operator>>(std::istream &in, PlayList &playList) {
        // Read the reader's name
        std::cout << "Enter Reader Name: ";
        std::getline(in, playList.reader);

        int numSurahs;
        std::cout << "Enter number of Surahs in the playlist: ";
        in >> numSurahs;
        in.ignore();

        for (int i = 0; i < numSurahs; ++i) {
            int id, duration;
            std::string name, type, audioPath;

            std::cout << "Enter Surah " << i + 1 << " details:\n";

            std::cout << "ID: ";
            in >> id;
            in.ignore();

            std::cout << "Name: ";
            std::getline(in, name);

            std::cout << "Type: ";
            std::getline(in, type);

            std::cout << "Audio Path: ";
            std::getline(in, audioPath);

            std::cout << "Duration: ";
            in >> duration;
            in.ignore();

            Surah surah(id, name, type, audioPath, duration);
            playList.playlist.insertEnd(surah);
        }

        return in;
    }


    Node<Surah> *getHead() {
        auto temp = currentSurah;
        start();
        auto ret = currentSurah;
        currentSurah = temp;
        return ret;
    }
};


#endif //QURANPLAYLIST_PLAYLIST_H
