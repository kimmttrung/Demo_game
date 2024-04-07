#pragma once
// virtual : mt, dt
class Iobject
{
public:
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

};