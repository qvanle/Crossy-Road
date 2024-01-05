#include <raylib.h>
#include <window.hpp>

Window::MusicController::MusicController() 
{
    stop = false;
    focus = 0;
}

Window::MusicController::~MusicController() 
{
    for (auto& music : m_data)
        UnloadMusicStream(music);
}

void Window::MusicController::choose(int index) 
{
    if (index < 0 || index >= m_data.size())
        return;
    focus = index;
}

void Window::MusicController::play() 
{
    if (stop)
        return;
    PlayMusicStream(m_data[focus]);
}

void Window::MusicController::pause() 
{
    if (stop)
        return;
    stop = true;
    PauseMusicStream(m_data[focus]);
}

void Window::MusicController::cont() 
{
    stop = false;
    ResumeMusicStream(m_data[focus]);
}

void Window::MusicController::add(Music music) 
{
    m_data.push_back(music);
}

bool Window::MusicController::isEnd() 
{
    return !IsMusicStreamPlaying(m_data[focus]);
}

int Window::MusicController::getFocus() 
{
    return focus;
}

int Window::MusicController::size() 
{
    return m_data.size();
}

void Window::MusicController::update() 
{
    if (stop)
        return;
    UpdateMusicStream(m_data[focus]);
}

void Window::MusicController::toggle() 
{
    if (stop)
        cont();
    else
        pause();
}
