#include "ComFun.h"
 
bool SDLCommonFunc::CheckVaCham(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if(left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b)
    {
        return false;
    }
    return true;
}

// SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Renderer* des, int x, int y)
// {
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(des, src);
//     if(texture == NULL)
//     {
//         // handle error
//         return SDL_Rect();
//     }

//     SDL_Rect dstRect;
//     dstRect.x = x;
//     dstRect.y = y;
//     SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);

//     SDL_RenderCopy(des, texture, NULL, &dstRect);

//     SDL_DestroyTexture(texture); // don't forget to destroy the texture after using it

//     return dstRect;
// }

// Kiểm tra focus
// bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
// {
//     if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h)
//     {
//         return true;
//     }
//     return false;
// }

// int SDLCommonFunc::ShowMenu(SDL_Renderer* des, TTF_Font* font)
// {
//     SDL_Surface* menu_surface = IMG_Load("img/1.jpg");
//     if(menu_surface == NULL)
//     {
//         return 1;
//     }

//     SDL_Texture* menu_texture = SDL_CreateTextureFromSurface(des, menu_surface);
//     SDL_FreeSurface(menu_surface); // Don't forget to free the surface after creating the texture

//     const int n_menu = 2;
//     SDL_Rect pos[n_menu] = {{200, 400, 0, 0}, {200, 200, 0, 0}};
//     TextObject text_menu[n_menu];

//     for(int i = 0; i < n_menu; i++)
//     {
//         text_menu[i].SetText((i == 0) ? "PLAY GAME" : "EXIT");
//         text_menu[i].SetColor(TextObject::BLACK_TEXT);
//         text_menu[i].LoadFromRenderText(font, des);
//     }

//     bool selected[n_menu] = {false, false};
//     int xm = 0;
//     int ym = 0;
//     SDL_Event m_event;

//     while(true)
//     {
//         SDL_RenderCopy(des, menu_texture, NULL, NULL);

//         for(int i = 0; i < n_menu; i++)
//         {
//             text_menu[i].RenderText(des, pos[i].x, pos[i].y);
//         }

//         while(SDL_PollEvent(&m_event))
//         {
//             switch(m_event.type)
//             {
//                 case SDL_QUIT:
//                     SDL_DestroyTexture(menu_texture);
//                     return 1;
//             }
//         }
//     }
// }