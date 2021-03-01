#ifndef FLUIDSIMULATOR
#define FLUIDSIMULATOR

#include "Grid.h"

class FluidSimulator {


    public:
        int size;
        float dt;
        float diff;
        float visc;
        
        float* s;
        float* density;
        
        float* Vx;
        float* Vy;
        //float *Vz;

        float* Vx0;
        float* Vy0;
        //float *Vz0;


        FluidSimulator(int size, float diffusion, float viscosity, float dt);
        ~FluidSimulator();

        void simulationStep();
        void addDensity(int x, int y, float amount);
        void addVelocity(int x, int y, Vector2 direction);
};


#endif