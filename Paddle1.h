#pragma once
#include "Paddle.h"
class Paddle1 :
    public Paddle {
public:
    Paddle1(float x, float y) : Paddle(x, y) {}
    void Render();
};

