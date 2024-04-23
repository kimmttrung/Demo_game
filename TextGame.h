#pragma once

#include "BaseObject.h"
#include "ComFun.h"

class TextObject : public BaseObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        XANH_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* des);
    void Free();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(const int& type);
    void SetText(const std::string& text) { str_val_ = text; }

    //std::string GetText() const { return str_val_; }

    void RenderText(SDL_Renderer* des, const int& xp, const int& yp, SDL_Rect* clip = NULL);// vẽ 1 đoạn văn bản lên màn hình
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
    
};