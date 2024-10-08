#ifndef WAVPLAY_H
#define WAVPLAY_H

#include <cstdlib>
#include <string>

void playWavFile(const std::string& filename) {
    std::string command = "start wmplayer \"" + filename + "\"";
    std::system(command.c_str());
}

#endif
