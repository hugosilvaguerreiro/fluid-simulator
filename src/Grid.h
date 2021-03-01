#ifndef GRID
#define GRID

#define IX(x, y) ((x) + (y) * N )

struct Vector2
{
  float x;
  float y;
};

class Grid {
    int size;
    float* grid;

    public:
        Grid(int size);
        ~Grid();

        float getValue(int x, int y);
        void setValue(int x, int y, float value);


};

#endif