#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "player.hpp"
#include "Wall.hpp"
#include <iostream>
#include <vector>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700
#define PI 3.141592654
#define GRIDSIZE 64

double distance(sf::Vector2f a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

sf::Vector2f normalize(sf::Vector2f a) {
    double len = distance(a);
    if (len == 0) return sf::Vector2f(0, 0);
    return sf::Vector2f(a.x / len, a.y / len);
}

void handleCollision(Player& player, const std::vector<Wall>& walls) {
    sf::FloatRect playerBounds = player.sprite.getGlobalBounds();

    for (const auto& wall : walls) {
        sf::FloatRect wallBounds = wall.sprite.getGlobalBounds();

        if (playerBounds.intersects(wallBounds)) {
            sf::FloatRect intersection;
            playerBounds.intersects(wallBounds, intersection);

            if (intersection.width < intersection.height) {
                if (playerBounds.left < wallBounds.left) {
                    player.sprite.move(-intersection.width, 0);
                }
                else {
                    player.sprite.move(intersection.width, 0);
                }
            }
            else {
                if (playerBounds.top < wallBounds.top) {
                    player.sprite.move(0, -intersection.height);
                }
                else {
                    player.sprite.move(0, intersection.height);
                }
            }
        }
    }
}

char map[10][10] = {
    "#########",
    "#.......#",
    "#.##....#",
    "#.#.....#",
    "#....#..#",
    "#....#..#",
    "#.......#",
    "#.##....#",
    "#.......#",
    "#########",
};


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ray-casting");

    sf::View main_view;
    main_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    sf::Clock dt_clock;
    float dt = 0;

    Player player("Resources\\Textures\\player.png", sf::Vector2f(2, 2), sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 0.5f, 250.f);

    Wall default_wall("Resources\\Textures\\GreenBoxSelected.png", sf::Vector2f(0, 0), sf::Vector2f(4, 4));
    std::vector<Wall> walls;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            switch (map[i][j]) {
                case '#':
                    default_wall.sprite.setPosition(i * GRIDSIZE, j * GRIDSIZE);
                    walls.push_back(Wall(default_wall));
                    break;

                default:
                    break;
            }
        }
    }

    main_view.zoom(0.5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt = dt_clock.restart().asSeconds();

        player.movement(player, dt);
        player.angle = player.sprite.getRotation();

        player.sprite.move(player.velocity);


        handleCollision(player, walls);

        main_view.setCenter(player.sprite.getPosition());

        player.velocity.x = 0.f;
        player.velocity.y = 0.f;

        window.clear();

        window.setView(main_view);
        window.draw(player.sprite);

        for (auto& wall : walls) {
            window.draw(wall.sprite);
        }

        window.display();
    }

    return 0;
}