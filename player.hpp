#pragma once
#include "SFML/Graphics.hpp"
#define PI 3.141592654

class Player {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	float turn_speed;
    float angle;
	sf::Vector2f velocity;

	void movement(Player& player, float dt) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            float angle = player.sprite.getRotation() - player.turn_speed;
            float angle_turned = angle < 0 ? angle += 360 : angle;

            player.sprite.setRotation(angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            float angle = player.sprite.getRotation() + player.turn_speed;
            float angle_turned = angle >= 360 ? angle -= 360 : angle;

            player.sprite.setRotation(angle);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.velocity.x += cos(player.sprite.getRotation() * (PI / 180)) * dt * player.speed;
            player.velocity.y += sin(player.sprite.getRotation() * (PI / 180)) * dt * player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.velocity.x -= cos(player.sprite.getRotation() * (PI / 180)) * dt * player.speed;
            player.velocity.y -= sin(player.sprite.getRotation() * (PI / 180)) * dt * player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            float angle_strafe = player.sprite.getRotation() - 90;

            angle_strafe = angle_strafe < 0 ? angle_strafe += 360 : angle_strafe;

            player.velocity.x += cos(angle_strafe * (PI / 180)) * dt * player.speed;
            player.velocity.y += sin(angle_strafe * (PI / 180)) * dt * player.speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            float angle_strafe = player.sprite.getRotation() + 90;

            angle_strafe = angle_strafe >= 360 ? angle_strafe -= 360 : angle_strafe;

            player.velocity.x += cos(angle_strafe * (PI / 180)) * dt * player.speed;
            player.velocity.y += sin(angle_strafe * (PI / 180)) * dt * player.speed;
        }
	}

	Player(std::string path, sf::Vector2f scale, sf::Vector2f position, float turn_speed_f, float speed_f) {
		texture.loadFromFile(path);

		turn_speed = turn_speed_f;
		speed = speed_f;

		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(scale);
		sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
		velocity = sf::Vector2f(0.f, 0.f);
	}
};