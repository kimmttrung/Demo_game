#include "TextGame.h"

TextObject::TextObject()
{
    str_val_ = "";
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
}

TextObject::~TextObject()
{
    
}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* des)// tạo văn bản từ font
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);// tạo 1 bề mặt từ văn bản
    if(text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface(des, text_surface);
        width_ = text_surface->w;
        height_ = text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    return texture_ != NULL;
}
void TextObject::Free()
{
    if(texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::SetColor(const int& type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if(type == XANH_TEXT)
    {
        SDL_Color color = {0, 18, 255};
        text_color_ = color;
    }
    else if(type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0};
        text_color_ = color;
    }
}

void TextObject::RenderText(SDL_Renderer* des, const int& xp, const int& yp, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {xp, yp, width_, height_};// vị trí và kích thước của văn bản

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(des, texture_, clip, &renderQuad);// copy văn bản lên màn hình
}

