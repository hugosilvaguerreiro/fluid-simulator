
#ifndef RENDERER
#define RENDERER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

typedef struct {
    unsigned int width;
    unsigned int height;

} WINDOW_SIZE;

typedef struct {
    unsigned short int R;
    unsigned short int G;
    unsigned short int B;
    unsigned short int A;
} RGBA;

class Renderer {


    

    public:
        WINDOW_SIZE       size;
        sf::RenderWindow* window;
        sf::Image*        current_frame;
        sf::Texture*      current_frame_texture;
        sf::Sprite*       current_frame_sprite;

        Renderer(WINDOW_SIZE size, std::string title="window");
        ~Renderer();

        void renderCircle();
        /*
            Renders a square
        */
        void renderSquare(int x, int y, int size, RGBA color, bool stroke=false, int stroke_size=1);

        /* 
            Checks if any relevant event has happened
        */
        void checkEvents();

        /*
            Used to set the color of a pixel in the current frame
        */
        void drawPixel(unsigned int x, unsigned int y, RGBA color);

        // renders the current frame
        void renderFrame();

        //clears the pixels of the current frame;
        void clearFrame();

        // returns true if the window is still open, false otherwise
        bool windowOpen();

        sf::RenderWindow* getWindow();
};

#endif
