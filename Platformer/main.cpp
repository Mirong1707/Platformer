#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shape.h"

int main() {
    int w = 200, h = 200;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1500, 1500), "SFML window");
    sf::Clock clock;
    float lastTime = 0;
    std::vector<std::shared_ptr<pe::Shape>> drawable; // все в этом векторе отрисовывается каждый кадр
    float fps = 30;
    drawable.push_back(std::make_shared<pe::RectObj>(sf::Vector2<float>(500.0, 0.0),
                                                       sf::Vector2<float>(600.0, 100.0), window, fps));
    while (window.isOpen()) {

        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rect->move(sf::Vector2<float>(1, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rect->move(sf::Vector2<float>(-1, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rect->move(sf::Vector2<float>(0, -1));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rect->move(sf::Vector2<float>(0, 1));
        }*/
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();

        //draw
        for(auto &i : drawable){
            i->frame();
        }
        window.display();

        //fps
        sf::Time time = clock.getElapsedTime();
        fps = 1 / (time.asSeconds() - lastTime);
        lastTime = time.asSeconds();
        window.setTitle(std::to_string(fps));
    }
    return EXIT_SUCCESS;
}