//
// Created by Harry Skerritt on 10/07/2026.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <raylib.h>

#include "../AssetManager/AssetManager.h"


class AudioManager {
public:
    // Toggle
    static void ToggleSFX() {
        sfx_enabled = !sfx_enabled;
    }

    static void ToggleMusic() {
        music_enabled = !music_enabled;
        if (curr_music != nullptr) {
            if (music_enabled) PlayMusicStream(*curr_music);
            else StopMusicStream(*curr_music);
        }
    }

    // Getters
    static bool IsSFXEnabled() { return sfx_enabled; }
    static bool IsMusicEnabled() { return music_enabled; }

    // SFX
    static void PlaySFX(std::string sound) {
        if (sfx_enabled) PlaySound(AssetManager::GetSound(sound));
    }

    // Music
    static void UpdateMusic() {
        if (music_enabled && curr_music != nullptr) {
            UpdateMusicStream(*curr_music);
        }
    }

    static void SwapMusic(const std::string& new_music_key) {
        if (curr_music != nullptr) {
            StopMusicStream(*curr_music);
        }

        curr_music = &AssetManager::GetMusic(new_music_key);

        if (music_enabled) {
            PlayMusicStream(*curr_music);
            SetMusicVolume(*curr_music, 0.3f);
        }
    }

private:
    static inline bool sfx_enabled = true;
    static inline bool music_enabled = true;
    static inline Music* curr_music = nullptr;
};



#endif //AUDIOMANAGER_H
