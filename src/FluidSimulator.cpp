#include "FluidSimulator.h"
#include <cstdlib>
#include "Solver.cpp"


FluidSimulator::FluidSimulator(int size, float diffusion, float viscosity, float dt) {
    int N = size;
    
    this->size = size;
    this->dt = dt;
    this->diff = diffusion;
    this->visc = viscosity;
    
    this->s =       (float*) calloc(N * N * N, sizeof(float));
    this->density = (float*) calloc(N * N * N, sizeof(float));
    
    this->Vx = (float*) calloc(N * N * N, sizeof(float));
    this->Vy = (float*) calloc(N * N * N, sizeof(float));
    //cube->Vz = (float*) calloc(N * N * N, sizeof(float));
    
    this->Vx0 = (float*) calloc(N * N * N, sizeof(float));
    this->Vy0 = (float*) calloc(N * N * N, sizeof(float));
    //cube->Vz0 = (float*) calloc(N * N * N, sizeof(float));
    
}

FluidSimulator::~FluidSimulator() {
    free(this->s);
    free(this->density);
    
    free(this->Vx);
    free(this->Vy);
    //free(this->Vz);
    
    free(this->Vx0);
    free(this->Vy0);
}



void FluidSimulator::simulationStep() {
    int N          = this->size;
    float visc     = this->visc;
    float diff     = this->diff;
    float dt       = this->dt;
    float *Vx      = this->Vx;
    float *Vy      = this->Vy;
    float *Vx0     = this->Vx0;
    float *Vy0     = this->Vy0;
    float *s       = this->s;
    float *density = this->density;
    
    diffuse(1, Vx0, Vx, visc, dt, 4, N);
    diffuse(2, Vy0, Vy, visc, dt, 4, N);
    
    project(Vx0, Vy0, Vx, Vy, 4, N);
    
    advect(1, Vx, Vx0, Vx0, Vy0, dt, N);
    advect(2, Vy, Vy0, Vx0, Vy0, dt, N);
    
    project(Vx, Vy, Vx0, Vy0, 4, N);
    
    diffuse(0, s, density, diff, dt, 4, N);
    advect(0, density, s, Vx, Vy, dt, N);
}

void FluidSimulator::addDensity(int x, int y, float amount) {
    int N = this->size;
    this->density[IX(x, y)] += amount;
}

void FluidSimulator::addVelocity(int x, int y, Vector2 direction) {

    int N = this->size;
    int index = IX(x, y);
    
    this->Vx[index] += direction.x;
    this->Vy[index] += direction.y;
}