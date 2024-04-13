#pragma once

#include "ComFun.h"

class BaseObject
{
public:
    BaseObject(); // constructor
    ~BaseObject();// destructor

    void SetRect(const int& x, const int& y) {rect_.x = x; rect_.y = y;}// vị trí đối tượng lên màn hình
    SDL_Rect GetRect() const {return rect_;} // trả về kích thước đối tượng là hcn
    SDL_Texture* GetObject() const {return p_object_;}// trả về contro của đối tượng sd

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);// load hình ảnh
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);// vẽ hình ảnh lên màn hình
    void Free();

protected:
    SDL_Texture* p_object_;  // luu hinh anh
    SDL_Rect rect_;  // luu kich thuoc

};

// virtual: ghi đè hàm trong các lớp dẫn xuất(Đa hình trong hướng đối tượng)