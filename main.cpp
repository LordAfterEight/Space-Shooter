#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Titlescreen.h" //includes colorXXX and fontXXX objects
#include "Assets.h"
#include <thread>
#include <chrono>
#include <csignal>
#include <iostream>
#include <Windows.h>
#include "discord-files/discord.h"
using namespace std;
using namespace sf;


// To-do list:
//     - Settings:
//         - Audio (On, Off, (Volume?))
//     - Controls Screen:
//         - WASD movement
//         - F4 for fullscreen
//         - Esc to quit
//         - Space to shoot
//     - Shooting:
//         - Sprite creation
//         - Audio creation
//         - Behaviour
//     - Enemies:
//         - Sprite creation
//         - Audio creation
//         - Behaviour (random events)
//     - Sound:
//         - More fight soundtrack
//
// Future Content:
//     - Powerups update
//     - More gamemodes update (Endless, Endless Bosses, Hardcore, (Story?))
//     - More weapons update
//     - More ships update
//     


int playerPosX = screenWidth / 2 - 64;
int playerPosY = screenHeight / 2 - 64;


struct DiscordState {
    std::unique_ptr<discord::Core> core;
};


void check(int i) {
    cout << "\ncheck " << i;
}
//main
int main() {
    Event event;
    auto icon = Image{};

    const auto assets = LoadAssets();
    //catch (exception& e) { cerr << "Exception: " << e.what() << endl; }

    if (!icon.loadFromFile("assets/icon.png")) { return EXIT_FAILURE; }

    mciSendString("stop fightTheme1", NULL, 0, NULL);
    mciSendString("open \"assets/sound/fight1.mp3\" type mpegvideo alias fightTheme1", NULL, 0, NULL);

    //Application Stuff
    
    DiscordState state{};
    discord::Core* core;
    discord::Result coreResult;
    SetEnvironmentVariable("DISCORD_INSTANCE_ID", "1");
    coreResult = discord::Core::Create(1276234139540131934, DiscordCreateFlags_Default, &core);
    coreResult == discord::Result::Ok && core
        ? std::cout << "Core Ok\n"
        : std::cout << "Core Not Ok\n";

    if (!core) {
        std::cout << "Failed to instantiate Discord!";
        std::exit(-1);
    }
    //Application Stuff

    //Activity Stuff
    discord::Activity currentActivity{};
    discord::ActivityAssets activityAssets{};
    currentActivity.SetName("SpaceShooter V0.3");
    currentActivity.SetDetails("In main menu");
    currentActivity.GetAssets().SetLargeImage("assets/textures/player/largeIcon.png");
    currentActivity.SetType(discord::ActivityType::Playing);
    //Activity Stuff

    while (window.isOpen()) {
        for (int i = 0; i <= 16; i++) {
            core->RunCallbacks();
            core->ActivityManager().UpdateActivity(currentActivity, [](discord::Result result) {
                system("cls");
                cout << ((result == discord::Result::Ok) ? "Succeeded to" : "Failed to") << " update activity";
                });
        }
        
        if (titlescreen == true) {
            titleScreen(); 
        }

        currentActivity.SetDetails("Fighting");

        mciSendString("stop mainMenuTheme", NULL, 0, NULL);
        mciSendString("play fightTheme1 repeat", NULL, 0, NULL);

        Text exitGame("Hold Esc to quit", fontCorruptorClean, 15);
        exitGame.setFillColor(colorRed);
        exitGame.setPosition(10, screenHeight - 25);

        Sprite player;
        player.setTexture(assets.playerTextureNormal1);
        player.setPosition(playerPosX, playerPosY);

        while (window.pollEvent(event)) { //Main game loop
            while (true) {
                //Event handling
                if (event.type == Event::Closed) { window.close(); mciSendString("stop mainMenuTheme", NULL, 0, NULL); exit; }
                if (Keyboard::isKeyPressed(Keyboard::F4)) { toggleFullscreen(120);  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); }
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    window.draw(exitGame);
                    window.display();
                    Sleep(2000);
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        window.close();
                        mciSendString("stop mainMenuTheme", NULL, 0, NULL);
                        break;
                        exit;
                    }
                }
                if (event.type == (Event::MouseButtonPressed || Event::MouseButtonReleased || Event::MouseMoved)) { cout << "Mouse event detected\n"; }

                //Activity stuff
                core->RunCallbacks();
                core->ActivityManager().UpdateActivity(currentActivity, [](discord::Result result) {
                    system("cls");
                    cout << ((result == discord::Result::Ok) ? "Succeeded to" : "Failed to") << " update activity";
                });

                //Sprite stuff
                if (Keyboard::isKeyPressed(Keyboard::D) and playerPosX < screenWidth - 128) { player.setPosition(playerPosX += 3, playerPosY); player.setTexture(assets.playerTextureRight1); }
                else if (Keyboard::isKeyPressed(Keyboard::A) and playerPosX > 0) { player.setPosition(playerPosX -= 3, playerPosY); player.setTexture(assets.playerTextureLeft1); }
                else player.setTexture(assets.playerTextureNormal1);
                if (Keyboard::isKeyPressed(Keyboard::W) and playerPosY > 0) { player.setPosition(playerPosX, playerPosY -= 3); }
                if (Keyboard::isKeyPressed(Keyboard::S) and playerPosY < screenHeight - 128) { player.setPosition(playerPosX, playerPosY += 3); }

                window.clear();
                window.draw(player);
                window.display();
            }
        }
    }
}