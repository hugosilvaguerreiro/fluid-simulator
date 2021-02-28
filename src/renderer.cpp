#include "renderer.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

Renderer::Renderer(WINDOW_SIZE window_size, std::string title) {
    this->size = window_size;
    this->window = new sf::RenderWindow(
                            sf::VideoMode(window_size.width, window_size.height), 
                            title);

    this->current_frame = new sf::Image();
    this->current_frame->create(window_size.width, window_size.height);
    this->current_frame_sprite = new sf::Sprite();
    this->current_frame_texture = new sf::Texture();
}

void Renderer::renderCircle() {
    sf::Image *image = new sf::Image();

    //setPixel(unsigned int x, unsigned int y, const Color& color);

      

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (this->window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        window->display();
    }

}

void Renderer::renderSquare(int x, int y, int size, RGBA color, bool stroke, int stroke_size) {
    RGBA border = {0,0,0,255};//TODO: add option to method
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            int x1= i+x;
            int y1= j+y;

            if(x1 < 0) x1 = 0; if(x1 > this->size.height) x1 = this->size.height;
            if(y1 < 0) y1 = 0; if(y1 > this->size.width) y1 = this->size.width;

            if(stroke && (i - stroke_size < 0 || i +stroke_size > size 
                        || j - stroke_size < 0 || j + stroke_size > size)) {
                this->drawPixel(x1, y1, border);
            } else {
                this->drawPixel(x1, y1, color);
            }
        }
    }

    
}

void Renderer::checkEvents() {
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Renderer::drawPixel(unsigned int x, unsigned int y, RGBA color) {
    sf::Color c = sf::Color(color.R, color.G, color.B, color.A);
    this->current_frame->setPixel(x,  y, c);
}

void Renderer::clearFrame() {
    this->current_frame->create(this->size.width, this->size.height);
}

void Renderer::renderFrame() {
    this->current_frame_texture->loadFromImage(*this->current_frame);
    this->current_frame_sprite->setTexture(*this->current_frame_texture, true);
            
    this->window->clear();
    this->window->draw(*this->current_frame_sprite);
    this->window->display();
    
}

bool Renderer::windowOpen() {
    return this->window->isOpen();
}

sf::RenderWindow* Renderer::getWindow()  {
    return this->window;
}

Renderer::~Renderer(){
    delete this->window;
    delete this->current_frame_sprite;
    delete this->current_frame_texture;
    delete this->current_frame;
}

