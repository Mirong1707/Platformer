#ifndef UNTITLED2_SHAPE_H
#define UNTITLED2_SHAPE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <vector>

namespace pe {

    float modVec2(sf::Vector2<float> &v){
        return v.x * v.x + v.y * v.y;
    }
    struct Shape {
        enum Type {
            sRectangle
        };
        Shape(){};
        virtual bool isCollide(std::shared_ptr<Shape> b1) = 0;
        virtual void s_draw() = 0;
        virtual void frame() = 0;
        Type getType() {
            return t;
        }
        virtual ~Shape() = default;

    protected:
        Type t;
    };

    struct Rectangle : Shape {
        sf::Color c;
        Rectangle(sf::Vector2<float> p1, sf::Vector2<float> p2, sf::RenderWindow& w, float &fps) : fps(fps){
            vertices = std::vector{p1, p2};
            t = sRectangle;
            c = sf::Color(0, 255, 0);
            window = &w;
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


        void s_draw() override {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2<float>(getWidth(), getHeight()));
            rect.setFillColor(c);
            rect.setPosition(vertices[0].x, vertices[0].y);
            window->draw(rect);
        };

        void frame() override{
            s_draw();
        }


        float getWidth() {
            return vertices[1].x - vertices[0].x;
        }
        float getHeight() {
            return vertices[1].y - vertices[0].y;
        }

    protected:
        // *----
        // |   |
        // ----*
        std::vector<sf::Vector2<float>> vertices;
        sf::RenderWindow *window;
        float fps;
    };


    struct RectObj : Rectangle{

        RectObj(sf::Vector2<float> p1, sf::Vector2<float> p2, sf::RenderWindow &w, float &fps) : Rectangle(p1, p2, w, fps) {
        }

        void gravity(){
            force += sf::Vector2<float>(0, 0.0015);
        }

        void resistance(){
            sf::Vector2<float> mxVel(2, 0);
            if(modVec2(velocity) > modVec2(mxVel)){
                velocity *= std::sqrt(modVec2(mxVel) / modVec2(velocity));
            }
        }

        void Forces(){
            force = {0, 0};
            gravity();
            float k = 0.5;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                velocity.y = 0;
                force = {0, -0.5};
            }
            velocity += k * force;
            resistance();
        }

        void move() {
            sf::Vector2 scaleVel = (velocity / fps) * 60.0f;
            std::cout << velocity.y << "\n";
            vertices[0] += scaleVel;
            vertices[1] += scaleVel;
            if(vertices[1].y > 500){
                float delta = vertices[1].y - 500;
                vertices[1].y -= delta;
                vertices[0].y -= delta;
            }
        }

        void frame() override{
            Forces();
            move();
            s_draw();
        }

    private:
        sf::Vector2<float> force{0, 0};
        sf::Vector2<float> velocity{0, 0};
    };
}// namespace pe


#endif//UNTITLED2_SHAPE_H
