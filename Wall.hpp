#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class Wall {
public:
	sf::Texture texture;
	sf::Sprite sprite;

	Wall(std::string path, sf::Vector2f position, sf::Vector2f scale) {
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(scale);
	}
};