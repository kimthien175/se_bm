#pragma once
#include "Paddle.h"

class Paddle0 :
    public Paddle {
public:
    Paddle0(float x, float y) : Paddle(x, y) {}
    void Render();
};

