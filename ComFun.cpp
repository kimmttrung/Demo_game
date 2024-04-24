#include "ComFun.h"
#include "TextGame.h"


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
//     SDL_Rect offset;
//     offset.x = x;
//     offset.y = y;
//     SDL_BlitSurface(src, NULL, des, &offset);

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
//     SDL_Surface* menu_surface = IMG_Load("img/start1.png");
//     if(menu_surface == NULL)
//     {
//         return 1;
//     }

//     const int n_menu = 2;
//     SDL_Rect pos[n_menu] = {{200, 400, 0, 0}, {200, 500, 0, 0}};
//     TextObject text_menu[n_menu];

//     for(int i = 0; i < n_menu; i++)
//     {
//         text_menu[i].SetText((i == 0) ? "PLAY GAME" : "EXIT");
//         text_menu[i].SetColor(TextObject::BLACK_TEXT);
//         text_menu[i].SetRect(pos[i].x, pos[i].y);
//         //text_menu[i].LoadFromRenderText(font, des);
//     }

//     bool selected[n_menu] = {false, false};
//     int xm = 0;
//     int ym = 0;
//     SDL_Event m_event;

//     while(true)
//     {
//         // SDL_RenderClear(des);
//         SDLCommonFunc::ApplySurface(g_menu, des, 0, 0);
//         for(int i = 0; i < n_menu; i++)
//         {
//             text_menu[i].RenderText(des, font);
//         }

//         while(SDL_PollEvent(&m_event))
//         {
//             switch(m_event.type)
//             {
//                 case SDL_QUIT:
//                 {
//                     return 1;
//                 }
//                 case SDL_MOUSEMOTION:
//                 {
//                     xm = m_event.motion.x;// lấy tọa độ chuột
//                     ym = m_event.motion.y;
//                     for(int i = 0; i < n_menu; i++)
//                     {
//                         if(SDLCommonFunc::CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
//                         {
//                             if(selected[i] == false)
//                             {
//                                 selected[i] = true;
//                                 text_menu[i].SetColor(TextObject::RED_TEXT);
//                             }
//                         }
//                         else
//                         {
//                             if(selected[i] == true)
//                             {
//                                 selected[i] = false;
//                                 text_menu[i].SetColor(TextObject::BLACK_TEXT);
//                             }
//                         }
//                     }
//                 break;
//                 }
//                 case SDL_MOUSEBUTTONDOWN:
//                 {
//                     xm = m_event.button.x;
//                     ym = m_event.button.y;
//                     for(int i = 0; i < n_menu; i++)
//                     {
//                         if(SDLCommonFunc::CheckFocusWithRect(xm, ym, text_menu[i].GetRect()))
//                         {
//                             return i;
//                         }
//                     }
//                 break;
//                 }
//                 case SDL_KEYDOWN:
//                 {
//                     if(m_event.key.keysym.sym == SDLK_ESCAPE)
//                     {
//                         return 1;
//                     }
//                 }
//                 default:
//                 break;
//             }
//         }
//         SDL_RenderPresent(des);
//     }
    
//     return 1;// thoát khỏi menu
// }

