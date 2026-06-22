// platform.h
#pragma once
#include <graphics.h> 
#include "tool.h"    

class platform {
public:
    struct collisionshape {
        float y;
        float left, right;
    };

    void on_draw() const {
        putimage_alpha(render_position.x, render_position.y, img);
    }

public:
    collisionshape shape;
    IMAGE* img = nullptr;       
    POINT render_position = { 0 };

public:
    platform() = default;
    ~platform() = default;
};