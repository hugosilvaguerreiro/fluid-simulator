#include "FluidSimulator.h"
#include "renderer.h"
#include <iostream>
#include <random>

#define IX(x, y) ((x) + (y) * N )

int SCALE = 3;

void render_densities(FluidSimulator* fs, Renderer* r) {
    int N = fs->size;

    
    int cx = int(0.5*r->size.width/SCALE);
    int cy = int(0.5*r->size.height/SCALE);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            fs->addDensity(cx+i, cy+i, 1);
        }
    }

    for (int i = 0; i < 2; i++) {
        float angle = rand() % 5 +1;

        float x = 1 * cos(angle);
        float y = 1 * sin(angle);
        Vector2 v = {x, y};
        fs->addVelocity(cx, cy, v);

    }

    fs->simulationStep();
    
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        float x = i *SCALE;
        float y = j *SCALE;
        float d = fs->density[IX(i, j)];


        unsigned short alpha = int(d * 255);
        unsigned short alpha2 = 255-alpha;

        RGBA rgb = {200, 200, 255 , alpha};
        r->renderSquare(x, y, SCALE, rgb, false);

      }
    }
}

// main loop
int main() {
    unsigned int N = 250;
    FluidSimulator* c = new FluidSimulator(N, 0.0000001, 0.0000001, 0.2);
    
    

    WINDOW_SIZE w = {N*SCALE, N*SCALE};

    Renderer r = Renderer(w, "test");
    sf::RenderWindow* window = r.getWindow();
    // main render loop
    while (r.windowOpen())
    {
        r.checkEvents(); //checks if window has been closed
        render_densities(c, &r);
        r.renderFrame();
    }
    
    delete c;

    return 0;
}

