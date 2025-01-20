//
// Created by Mahmoud Elshafei on 12/2/2024.
//

#ifndef QURANPLAYLIST_AUDIOPLAYER_H
#define QURANPLAYLIST_AUDIOPLAYER_H

#include "Simulate.h"
#include "PlayList.h"
#include <windows.h>
#include <mmsystem.h>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::milliseconds
#include <conio.h>

#pragma comment(lib, "winmm.lib")

bool isPaused = false; // Global flag to manage pause/resume
bool isPlaying = false; // Global flag to stop playback
Node<Surah>* currentSurah = nullptr; // Global pointer refer to current playing


void startProgram();
void playSurah(PlayList&);
void pauseSurah(PlayList&);
void resumeSurah(PlayList&);
void getNext(PlayList&);
void getPrev(PlayList&);


void startProgram() {
    PlaySound(
            TEXT("D:\\My_Github\\FCI-DS-Project\\Quran_Playlist_Project\\BackEnd\\QuranPlaylist\\data\\bismi_allah_4.wav"),
            nullptr, SND_FILENAME | SND_ASYNC);
}

void playSurah(PlayList &playList) {
    if (!currentSurah) {
        currentSurah = playList.getHead();
        if (!currentSurah)
            std::cerr << "No Surah exist to play..!" << std::endl;
    }
    if (currentSurah) {
        std::cout << "Playing " << currentSurah->data.getName() << std::endl;
        PlaySound(currentSurah->data.getAudioPath().c_str(), nullptr, SND_FILENAME | SND_ASYNC);
        isPaused = false;
        isPlaying = true;
//        std::this_thread::sleep_for(std::chrono::seconds(currentSurah->data.getDuration()));
//        std::cout << "Next Surah.." << std::endl;
//        getNext(playList);
    }
}

void pauseSurah(PlayList &playList) {
    if (isPlaying) {
        isPlaying = false;
        isPaused = true;
        std::cout << "Paused.." << std::endl;
        PlaySound(nullptr, nullptr, 0);
    }
}

void resumeSurah(PlayList &playList) {
    if (isPaused) {
        isPaused = false;
        isPlaying = true;
        std::cout << "Resumed.." << std::endl;
        PlaySound(currentSurah->data.getAudioPath().c_str(), nullptr, SND_FILENAME | SND_ASYNC);
    }
}

void getNext(PlayList &playList) {
    currentSurah = playList.nextSurah();
    if (!currentSurah)
        std::cerr << "No Surah exist to play..!" << std::endl;
    else {
        playSurah(playList);
    }
}

void getPrev(PlayList &playList) {
    currentSurah = playList.prevSurah();
    if (!currentSurah)
        std::cerr << "No Surah exist to play..!" << std::endl;
    else {
        playSurah(playList);
    }
}

//void playSound(const std::string &SurahName, const std::string &path, size_t durationMs) {
//    std::cout << "Now Playing: " << SurahName << std::endl;
//    PlaySound(TEXT(path.c_str()) , nullptr, SND_FILENAME | SND_ASYNC);
//    std::this_thread::sleep_for(std::chrono::seconds(durationMs));
//    std::cout << "Sound Over.." << std::endl;
//}

//void playSound(const std::string &path, size_t durationS) {
//    PlaySound(TEXT(path.c_str()), nullptr, SND_FILENAME | SND_ASYNC);
//    auto startTime = std::chrono::steady_clock::now();
//
//    while (true) {
//        if (stopPlayback) {
//            PlaySound(nullptr, nullptr, 0); // Stop the sound
//            return;
//        }
//        if (!isPaused) {
//            auto currentTime = std::chrono::steady_clock::now();
//            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() >= durationS) {
//                break; // Exit loop when sound duration is reached
//            }
//        } else {
//            std::this_thread::sleep_for(std::chrono::seconds(10)); // Avoid busy waiting
//        }
//    }
//    PlaySound(nullptr, nullptr, 0); // Ensure sound stops
//}

//void controlPlaylist(PlayList &playlist) {
////    playlist.start(); // Start with the first Surah
//    stopPlayback = false;
//    isPaused = false;
//
//    while (true) {
//        if (!playlist.getCurrentSurah()) {
//            return std::cerr << "No Surah in the playlist!" << std::endl, void();
//        }
//
//        stopPlayback = false;
//        isPaused = false;
//        Surah *surah = playlist.getCurrentSurah();
//        std::string SurahName = surah->getName();
//        std::string path = surah->getAudioPath();
//        size_t durationS = surah->getDuration();
//        // Launch the playback thread
//        std::thread soundThread(playSound, path, durationS);
//        std::cout << "Now Playing: " << SurahName << std::endl;
//
//        while (true) {
//            if (_kbhit()) {
//                char ch = getch();
//
//                if (ch == 'q') { // Quit playlist
//                    stopPlayback = true;
//                    soundThread.join();
//                    return;
//                } else if (ch == 'a') { // a (previous Surah)
//                    stopPlayback = true;
//                    soundThread.join();
//                    playlist.prevSurah();
//                    break; // Restart loop to play the previous Surah
//                } else if (ch == 'd') { // d (next Surah)
//                    stopPlayback = true;
//                    soundThread.join();
//                    playlist.nextSurah();
//                    break; // Restart loop to play the next Surah
//                } else if (ch == 'w') { // w (pause)
//                    isPaused = true;
//                    std::cout << "Paused" << std::endl;
//                } else if (ch == 's') { // s (resume)
//                    isPaused = false;
//                    std::cout << "Resumed" << std::endl;
//                }
//            }
//
//            // Prevent busy-waiting
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        }
//
//        soundThread.join();  // Ensure sound thread finishes properly
//    }
//}


#endif //QURANPLAYLIST_AUDIOPLAYER_H
