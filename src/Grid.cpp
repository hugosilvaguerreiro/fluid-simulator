#include <cstdlib>
#include "Grid.h"


Grid::Grid(int size) {
    this->size = size;
    this->grid = (float*) calloc(this->size * this->size, sizeof(float));
}

Grid::~Grid() {
    free(this->grid);
}

float Grid::getValue(int x, int y) {
    int N = this->size;
    return this->grid[IX(x, y)];
}

void Grid::setValue(int x, int y, float value) {
    int N = this->size;
    this->grid[IX(x, y)] = value;
    
}
