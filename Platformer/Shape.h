#ifndef UNTITLED2_SHAPE_H
#define UNTITLED2_SHAPE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
namespace pe {
    struct Shape {
        enum Type {
            sRectangle
        };
        Shape(){};
        virtual bool isCollide(std::shared_ptr<Shape> b1) = 0;
        virtual void s_draw(sf::RenderWindow &window) = 0;
        virtual void move(sf::Vector2<float> v) = 0;
        Type getType() {
            return t;
        }
        virtual ~Shape() = default;

    protected:
        Type t;
    };

    struct Rectangle : Shape {
        sf::Color c;
        Rectangle(sf::Vector2<float> p1, sf::Vector2<float> p2) {
            vertices = std::vector{p1, p2};
            t = sRectangle;
            c = sf::Color(0, 255, 0);
        }
        bool isCollide(std::shared_ptr<Shape> b1) override {
            if (b1->getType() == sRectangle) {
                c = sf::Color(0, 255, 0);
                std::shared_ptr<Rectangle> r1 = std::dynamic_pointer_cast<Rectangle>(b1);
                if (vertices[0].x > r1->vertices[1].x || vertices[1].x < r1->vertices[0].x) return false;
                if (vertices[0].y > r1->vertices[1].y || vertices[1].y < r1->vertices[0].y) return false;
                c = sf::Color(255, 0, 0);
                return true;
            }
            return false;
        }

        void s_draw(sf::RenderWindow &window) override {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2<float>(getWidth(), getHeight()));
            rect.setFillColor(c);
            rect.setPosition(vertices[0].x, vertices[0].y);
            window.draw(rect);
        };

        void move(sf::Vector2<float> v) override {
            vertices[0] += v;
            vertices[1] += v;
        }


        float getWidth() {
            return vertices[1].x - vertices[0].x;
        }
        float getHeight() {
            return vertices[1].y - vertices[0].y;
        }

    private:
        // *----
        // |   |
        // ----*
        std::vector<sf::Vector2<float>> vertices;
    };
}// namespace pe


#endif//UNTITLED2_SHAPE_H
