#pragma once
#include <QAudioOutput>
#include <QMediaPlayer>

#include "IAudioBackend.hpp"

namespace Track8::Player {

class QtMultimediaBackend : public IAudioBackend {
public:
    QtMultimediaBackend();

    void load(const std::filesystem::path& path) override;
    void play() override;
    void pause() override;
    void stop() override;

    void setVolume(float volume) override;
    void seek(int64_t positionMs) override;

    void onFinished(std::function<void()> callback) override;
    void onStateChanged(std::function<void(PlaybackState)> callback) override;
    void onDurationChanged(std::function<void(std::int64_t)> callback) override;
    void onPositionChanged(std::function<void(std::int64_t)> callback) override;

private:
    std::function<void()> m_finishedCallback;
    std::function<void(PlaybackState)> m_stateChangedCallback;
    std::function<void(std::int64_t)> m_positionChangedCallback;
    std::function<void(std::int64_t)> m_durationChangedCallback;
    QMediaPlayer m_player;
    QAudioOutput m_output;
};

} // namespace Track8::Player
