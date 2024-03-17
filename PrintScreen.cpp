
// #include "PrintScreen.h"

// SDL_Window* g_Window = NULL;
// SDL_Surface* gScreenSurface = NULL;
// SDL_Surface* gHelloWorld = NULL;


// // SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// // SDL_Surface* gCurrentSurface = NULL;

// bool init()
// {
//     bool success = true;
//     int ret = SDL_Init(SDL_INIT_VIDEO);
//     if(ret < 0)
//         return false;
//     else
//     {
//         g_Window = SDL_CreateWindow("huong dan SDL",
//                                     SDL_WINDOWPOS_UNDEFINED,
//                                     SDL_WINDOWPOS_UNDEFINED, 
//                                     SCREEN_WIDTH, SCREEN_HEIGHT, 
//                                     SDL_WINDOW_SHOWN);

//         if(g_Window == NULL)
//         {
//             printf( "Không thể tạo cửa sổ! SDL_Error: %s\n", SDL_GetError() );
//             success = false;
//         }
//         else
//         {
//             gScreenSurface = SDL_GetWindowSurface(g_Window);
//         }
//     }
//     return success;
// }

// bool LoadMedia()
// {
    
//     bool success = true;
//     gHelloWorld = IMG_Load("img//chess1.png");
//     if (gHelloWorld == NULL)
//     {
//         printf( "Không the tai hinh anh %s! Lỗi SDL: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
//         success = false;
//     }
//     return success;
// }

// void close()
// {
//     // phan bo be mat
//     SDL_FreeSurface(gHelloWorld);
//     gHelloWorld = NULL;

//     // pha huy cua so
//     SDL_DestroyWindow(g_Window);
//     g_Window = NULL;

//     SDL_Quit();
// }

// int main(int argc, char* argv[])
// {
//     if(!init())
//         return -1;
//     else
//     {
//         if(!LoadMedia())
//         {
//             return -1;
//         }
//         else
//         {
//             SDL_Event e;

//             bool quit = false;

//             while(!quit)
//             {
//                 while(SDL_PollEvent(&e))
//                 {
//                     if(e.type == SDL_QUIT)
//                     {
//                         quit = true;
//                     }
//                 }
//                 SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

//                 SDL_UpdateWindowSurface( g_Window );
//             }
//         }
//     }
//     close();
//     return 0;
// }