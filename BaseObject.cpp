
#include "BaseObject.h"

BaseObject::BaseObject()// khoi tao hcn
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)// load anh
{
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface != NULL)
    {
        
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        // tao ket cau tu 1 be mat hien co
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if(new_texture != NULL)
        {
            rect_.w = load_surface->w;// rect_.w : chiều rông tấm ảnh: 480/8 = 60(<= 1 ô của map)
            rect_.h = load_surface->h; // rect_.h : chiều cao tấm ảnh: 64
        }

        SDL_FreeSurface(load_surface);
    }

    p_object_ = new_texture;
    
    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    // vi tri va kich thuoc anh
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    // dẩy toàn bộ thông số pObject lên des
    SDL_RenderCopy(des, p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}