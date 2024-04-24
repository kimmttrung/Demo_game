#include <iostream>
#include "ComFun.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "Timer.h"
#include "NguyHiem.h"
#include "TextGame.h"


BaseObject g_background;
TTF_Font* font_time = NULL;

bool InitData()
{
    bool success = true;
    // khoi tao SDL
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;
    
    g_Window = SDL_CreateWindow("Game treasure std - kim1",
                                SDL_WINDOWPOS_UNDEFINED,   // vi tri cua screen
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);

    if(g_Window == NULL)
    {
        std::cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // SDL_RENDERER_ACCELERATED: tang toc do phan ung
        g_screen = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) success = false;
        else
        {
            // sd mau cho thao tac ve
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);// set màu cho renderer
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
                success = false;    
        }

        if(TTF_Init() == -1) success = false;
    
        font_time = TTF_OpenFont("Front/font-times-new-roman.ttf", 40);// load font

        if(font_time == NULL) success = false;
        
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/Bground2.jpg", g_screen);
    if(ret == false)
        return false;
    return true;
}
ThertsObject* CreateThertsObject(const std::string& img_path, SDL_Renderer* renderer, int x_pos, int y_pos)
{
    ThertsObject* therts_object = new ThertsObject();
    therts_object->LoadImg(img_path, renderer);
    therts_object->set_clip();
    therts_object->set_x_pos(x_pos);
    therts_object->set_y_pos(y_pos);

    Dan* dan = new Dan();
    therts_object->InitDan(dan, renderer);

    return therts_object;
}

std::vector<ThertsObject*> MakeTherts()
{
    std::vector<ThertsObject*> list_therts;

    for(int i = 0; i < 30; i++)
    {
        list_therts.push_back(CreateThertsObject("img/threat4.png", g_screen, 1000 + i*400, 400));
        list_therts.push_back(CreateThertsObject("img/threat_level.png", g_screen, 1200 + i*400, 400));
        list_therts.push_back(CreateThertsObject("img/boss1.png", g_screen, 900 + i*1000, 400));

        list_therts.push_back(CreateThertsObject("img/threat_level.png", g_screen, 700 + i*500, 1200));
        list_therts.push_back(CreateThertsObject("img/threat4.png", g_screen, 1000 + i*500, 1200));
        list_therts.push_back(CreateThertsObject("img/boss1.png", g_screen, 900 + i*1000, 1200));
        
        list_therts.push_back(CreateThertsObject("img/threat4.png", g_screen, 700 + i*300, 1700));
        list_therts.push_back(CreateThertsObject("img/boss1.png", g_screen, 1000 + i*300, 1700));
    }

    return list_therts;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    IMG_Quit();
    SDL_Quit();
}



void HandleCollision(ThertsObject* therts, MainObject& p_player, int& sinh_Menh)
{
    SDL_Rect rect_player = p_player.GetRectFrame();
    bool bCol = false;
    std::vector<Dan*> dan_list = therts->get_dan_list();
    for(int z=0;z<dan_list.size();z++)
    {
        Dan* p_dan = dan_list.at(z);
        if(p_dan != NULL)
        {
            bCol = SDLCommonFunc::CheckVaCham(p_dan->GetRect(), rect_player);
            if(bCol)
            {
                therts->RemoveDan(z);
                break;
            }
        }
    }

    SDL_Rect rect_threat = therts->GetRect();
    bool bCol1 = SDLCommonFunc::CheckVaCham(rect_player, rect_threat);

    if(bCol1 || bCol)
    {
        sinh_Menh--;
        if(sinh_Menh < 5 && sinh_Menh > 0)
        {
            if(MessageBoxW(NULL, L"You have lost 1 life. Do you want to play again?", L"Thong bao",  MB_YESNO) == IDNO)
            {
                therts->Free();
                close();
                SDL_Quit();
                exit(0);
            }
            else{
                p_player.SetRect(0, 0);
                p_player.SetMapXY(0, 0);
                p_player.set_come_back_time(60);
            }
        }
        else if(sinh_Menh == 0)
        {
            if(MessageBoxW(NULL, L"GAME OVER", L"Thong bao",  MB_OK | MB_ICONSTOP) == IDOK)
            {
                therts->Free();
                close();
                SDL_Quit();
                exit(0);
            }
        }
    }
}

void UpdateAndRenderInfo(TextObject& text_obj, const std::string& info, int value, TTF_Font* font, SDL_Renderer *g_screen, int x, int y)
{
    std::string str_info = info + std::to_string(value);
    text_obj.SetText(str_info);
    text_obj.LoadFromRenderText(font, g_screen);
    text_obj.RenderText(g_screen, x, y);
}

int main(int argc, char* argv[])
{ 
    ImpTimer fps_time;

    if(InitData() == false) return -1;
    if(LoadBackground() == false) return -1;

    GameMap game_map;// khai bao map
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    game_map.LoadMap("map1/map012.dat");// load map
    #pragma GCC diagnostic warning "-Wwrite-strings"
    game_map.LoadTiles(g_screen);// load hinh anh cho map

    MainObject p_player;// khai bao animation
    p_player.LoadImg("img/player_right1.png", g_screen);
    p_player.set_clips();

    std::vector<ThertsObject*> therts_list = MakeTherts();// khai bao va tao threat

    int sinh_Menh = 5;

    TextObject p_hp;
    p_hp.SetColor(TextObject::XANH_TEXT);
    TextObject time_game;
    time_game.SetColor(TextObject::XANH_TEXT);
    TextObject mark_game;
    mark_game.SetColor(TextObject::RED_TEXT);
    Uint32 mark_val = 0;
    TextObject money_game;
    money_game.SetColor(TextObject::BLACK_TEXT);
    TextObject key_game;
    key_game.SetColor(TextObject::XANH_TEXT);

    bool is_quit = false;

    

    while(!is_quit)
    {
        fps_time.start();
        while(SDL_PollEvent(&g_Event) != 0)
        {
            if(g_Event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandelInputAction(g_Event, g_screen);// xử lý di chuyển nhân vật
        }
        
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);// xóa màn hình

    
        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();// lấy thông tin map

        p_player.HandelDan(g_screen); // xử lý đạn
        p_player.SetMapXY(map_data.start_x, map_data.start_y);// thiết lập vị trí map
        p_player.DoPlayer(map_data);// di chuyển nhân vật thông qua dữ liệu map truyền vào
        p_player.Show(g_screen);// hiển thị nhân vật

        game_map.SetMap(map_data);// thiết lập thông tin map
        game_map.DrawMap(g_screen);// vẽ map

        // kiểm tra nhân vật và đạn threat
        for(int i = 0; i < therts_list.size(); i++)// duyệt qua danh sách quái
        {
            ThertsObject* therts = therts_list.at(i);
            if(therts != NULL)
            {
                therts->set_map_xy(map_data.start_x, map_data.start_y);
                therts->DoPlayer(map_data);// di chuyển threat
                therts->MakeDan(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);// tạo đạn
                therts->Show(g_screen);

                HandleCollision(therts, p_player, sinh_Menh);
            }
        }
        

        //kiểm tra va chạm giữa đạn nhân vật và threat
        std::vector<Dan*> dan_list = p_player.get_dan_list();// lấy danh sách đạn
        for(int i = 0; i < dan_list.size(); i++)// duyệt qua danh sách đạn
        {
            Dan* p_dan = dan_list.at(i);
            if(p_dan != NULL)
            {
                for(int j=0;j<therts_list.size();j++)
                {
                    ThertsObject* therts = therts_list.at(j);
                    if(therts != NULL)
                    {
                        if(therts)
                        {
                            SDL_Rect tRect;
                            tRect.x = therts->GetRect().x;
                            tRect.y = therts->GetRect().y;
                            tRect.w = therts->get_width_frame();
                            tRect.h = therts->get_height_frame();

                            SDL_Rect danRect = p_dan->GetRect();
                            bool isCol = SDLCommonFunc::CheckVaCham(danRect, tRect);

                            if(isCol)
                            {
                                mark_val ++;
                                p_player.RemoveDan(i);
                                p_dan->set_is_move(false);
                                therts->Free();
                                therts_list.erase(therts_list.begin() + j);
                            }
                        }
                    }
                }
            }
        }


        // Time game
        Uint32 last_time_val = 0;
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = 1000 - time_val;

        if(val_time <= 0)
        {
            if(MessageBoxW(NULL, L"GAME OVER", L"Thong bao",  MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
            }
        }
        else if (time_val != last_time_val) 
        {
            last_time_val = time_val;
            UpdateAndRenderInfo(time_game, "Time: ", val_time, font_time, g_screen, SCREEN_WIDTH - 200, 15);
        }

        UpdateAndRenderInfo(mark_game, "Mark: ", mark_val, font_time, g_screen, SCREEN_WIDTH*0.5 - 500, 15);
        UpdateAndRenderInfo(money_game, "Money: ", p_player.get_money_count(), font_time, g_screen, SCREEN_WIDTH*0.5 - 100, 15);
        UpdateAndRenderInfo(p_hp, "HP: ", sinh_Menh, font_time, g_screen, 50, 15);
        UpdateAndRenderInfo(key_game, "Key: ", p_player.get_key_count(), font_time, g_screen, SCREEN_WIDTH - 500, 15);


        SDL_RenderPresent(g_screen);// cập nhật màn hình

        int real_imp_time = fps_time.get_ticks();// thoi gian thuc te
        int time_one_frame = 1000/FRAME_PER_SECOND;// thoi gian 1 frame: 1000ms/25frame = 40ms

        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }
    }

    for(int i = 0; i < therts_list.size(); i++)
    {
        ThertsObject* therts = therts_list.at(i);
        if(therts != NULL)
        {
            therts->Free();
            delete therts;
            therts = NULL;
        }
    }
    
    close();
    return 0;
}
