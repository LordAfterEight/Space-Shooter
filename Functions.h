#include <iostream>
#include <windows.h>
#include <conio.h>
#include <SFML/Graphics.hpp>
#pragma comment(lib, "Winmm.lib")
using namespace sf;
int screenWidth = 1920;
int screenHeight = 1080;
int frameRate = 120;
bool fullscreen = false;
RenderWindow window(VideoMode(screenWidth, screenHeight), "Space Shooter V0.3");
void Sleep(int time) {
    _Thrd_sleep_for(time);
}
void toggleFullscreen(int framerate) {
    if (fullscreen == false) {
        window.create(VideoMode(screenWidth, screenHeight), "Space Shooter V0.3 Fullscreen", Style::Fullscreen);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(frameRate);
        window.setMouseCursorVisible(false);
    }
    if (fullscreen == true) {
        window.create(VideoMode(screenWidth, screenHeight), "Space Shooter V0.3", Style::Default);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(frameRate);
        window.setMouseCursorVisible(false);
    }
    fullscreen = !fullscreen;
}