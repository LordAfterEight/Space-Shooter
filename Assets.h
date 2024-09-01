#include <SFML/Graphics.hpp>
using namespace sf;

struct LoadAssets {
	Texture playerTextureNormal1;
	Texture playerTextureRight1;
	Texture playerTextureLeft1;
	LoadAssets() {
		try {
			if (!playerTextureNormal1.loadFromFile("assets/textures/player/Ship1-1.png")) cout << "Failed to load texture";//throw EXIT_FAILURE;
			if (!playerTextureLeft1.loadFromFile("assets/textures/player/Ship1-Left.png")) cout << "Failed to load texture";  //throw EXIT_FAILURE;
			if (!playerTextureRight1.loadFromFile("assets/textures/player/Ship1-Right.png")) cout << "Failed to load texture";  //throw EXIT_FAILURE;
		}
		catch (const exception& e) {
			cerr << "Exception: " << e.what() << endl;
		}
	}
};