#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <conio.h>
#include <stdlib.h>
#include "Fonts.h"
#include "Colors.h"
#include "Functions.h"
#include <iostream>
#include <Windows.h>
using namespace std;
using namespace sf;

#pragma comment(lib, "Winmm.lib")

bool titlescreen = true;

int titleScreen() {
    Event event;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(120);
    auto icon = Image{};
    if (!icon.loadFromFile("assets/icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window.clear();
    loadFonts();


    Text title("Space Shooter V0.3", fontPerfectDark, 70);
    title.setFillColor(colorPur);
    title.setOutlineColor(colorWhi);
    title.setOutlineThickness(1);
    title.setPosition(screenWidth / 2 - 400, -85);

    RectangleShape line1(Vector2f(1000, 2));
    line1.setFillColor(colorWhi);
    line1.setPosition(screenWidth / 2 - 430, -85);

    RectangleShape line2(Vector2f(1000, 2));
    line2.setFillColor(colorWhi);
    line2.setPosition(screenWidth / 2 - 530, 0);

    Text fullscreenText("Press F4 to toggle Fullscreen", fontDivlit, 20);
    fullscreenText.setPosition(10, 10);
    fullscreenText.setFillColor(colorGr7);

    Text madeByText("Made by Elias Stettmayer", fontDivlit, 20);
    madeByText.setPosition(1650, 10);
    madeByText.setFillColor(colorGr7);

    Text startGameText("Press Enter to start the game", fontCorruptorClean, 30);
    startGameText.setFillColor(colorPur);
    startGameText.setPosition(screenWidth / 2 - 550, screenHeight / 2);

    Text underDev("You are using the active development version which will contain bugs", fontPerfectDark, 15);
    underDev.setFillColor(colorRed);
    underDev.setPosition(screenWidth / 2 - 400, 10);


    mciSendString("open \"assets/sound/mainmenu.mp3\" type mpegvideo alias mainMenuTheme", NULL, 0, NULL);
    mciSendString("play mainmenutheme repeat", NULL, 0, NULL);

    for (int i = 0; i <= screenHeight / 4; i = i++) { //Title moving
        window.clear();
        window.draw(title);
        window.draw(line1);
        window.draw(line2);
        window.draw(fullscreenText);
        window.draw(madeByText);
        window.draw(underDev);
        window.display();
        title.setPosition(screenWidth / 2 - 400, -85 + i);
        line1.setPosition(screenWidth / 2 - 430, -85 + i);
        line2.setPosition(screenWidth / 2 - 550, i);
        if (Keyboard::isKeyPressed(Keyboard::F4)) { toggleFullscreen(120); }
        Sleep(10);
    }
    while (titlescreen == true) {
        while (window.isOpen() and window.pollEvent(event)) {
            window.clear();
            window.draw(title);
            window.draw(line1);
            window.draw(line2);
            window.draw(startGameText);
            window.draw(fullscreenText);
            window.draw(madeByText);
            window.draw(underDev);
            window.display();
            if (Keyboard::isKeyPressed(Keyboard::F4)) { toggleFullscreen(120); window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }
            if (Keyboard::isKeyPressed(Keyboard::Return)) { titlescreen = false;  break; }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                Text exitGame("Hold Esc to quit", fontCorruptorClean, 15);
                exitGame.setFillColor(colorRed);
                exitGame.setPosition(screenWidth / 2 - 550, screenHeight / 2 + 100);
                window.draw(exitGame);
                window.display();
                Sleep(3000);
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.close();
                    mciSendString("stop mainMenuTheme", NULL, 0, NULL);
                    break;
                    exit;
                }
            }
            if (event.type == Event::Closed) { window.close(); mciSendString("stop mainMenuTheme", NULL, 0, NULL); exit; }
            if (event.type == (Event::MouseButtonPressed || Event::MouseButtonReleased || Event::MouseMoved)) { cout << "Mouse event detected\n"; continue; }
            Sleep(10);
        }
    }
    return 0;
}