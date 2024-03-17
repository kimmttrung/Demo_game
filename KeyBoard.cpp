// #include "KeyBoard.h"

// SDL_Window* g_Window = NULL;
// SDL_Surface* gScreenSurface = NULL;
// SDL_Surface* gHelloWorld = NULL;
// SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// SDL_Surface* gCurrentSurface = NULL;

// enum KeyPressSurfaces
// {
//     KEY_PRESS_SURFACE_DEFAULT,
// 	KEY_PRESS_SURFACE_UP,
// 	KEY_PRESS_SURFACE_DOWN,
// 	KEY_PRESS_SURFACE_LEFT,
// 	KEY_PRESS_SURFACE_RIGHT,
// 	KEY_PRESS_SURFACE_TOTAL
// };

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

// bool loadMedia()
// {
// 	bool success = true;

// 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "img//chess1.png" );
// 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
// 	{
// 		printf( "Failed to load default image!\n" );
// 		success = false;
// 	}

// 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "img//chess3.jpg" );
// 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
// 	{
// 		printf( "Failed to load up image!\n" );
// 		success = false;
// 	}

// 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "img//chess4.jpg" );
// 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
// 	{
// 		printf( "Failed to load down image!\n" );
// 		success = false;
// 	}

// 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "img//chess5.jpg" );
// 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
// 	{
// 		printf( "Failed to load left image!\n" );
// 		success = false;
// 	}

// 	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "img//chess1.png" );
// 	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
// 	{
// 		printf( "Failed to load right image!\n" );
// 		success = false;
// 	}

// 	return success;
// }

// void close()
// {
// 	//Deallocate surfaces
// 	for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
// 	{
// 		SDL_FreeSurface( gKeyPressSurfaces[ i ] );
// 		gKeyPressSurfaces[ i ] = NULL;
// 	}

// 	//Destroy window
// 	SDL_DestroyWindow( g_Window );
// 	g_Window = NULL;

// 	//Quit SDL subsystems
// 	SDL_Quit();
// }

// SDL_Surface* loadSurface( std::string path )
// {
// 	//Load image at specified path
// 	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
// 	if( loadedSurface == NULL )
// 	{
// 		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// 	}

// 	return loadedSurface;
// }


// int main( int argc, char* args[] )
// {
// 	//Start up SDL and create window
// 	if( !init() )
// 	{
// 		printf( "Failed to initialize!\n" );
// 	}
// 	else
// 	{
// 		//Load media
// 		if( !loadMedia() )
// 		{
// 			printf( "Failed to load media!\n" );
// 		}
// 		else
// 		{	
// 			//Main loop flag
// 			bool quit = false;

// 			//Event handler
// 			SDL_Event e;

// 			//Set default current surface
// 			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

// 			//While application is running
// 			while( !quit )
// 			{
// 				//Handle events on queue
// 				while( SDL_PollEvent( &e ) != 0 )
// 				{
// 					//User requests quit
// 					if( e.type == SDL_QUIT )
// 					{
// 						quit = true;
// 					}
// 					//User presses a key
// 					else if( e.type == SDL_KEYDOWN )
// 					{
// 						//Select surfaces based on key press
// 						switch( e.key.keysym.sym )
// 						{
// 							case SDLK_UP:
// 							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
// 							break;

// 							case SDLK_DOWN:
// 							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
// 							break;

// 							case SDLK_LEFT:
// 							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
// 							break;

// 							case SDLK_RIGHT:
// 							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
// 							break;

// 							default:
// 							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
// 							break;
// 						}
// 					}
// 				}

// 				//Apply the current image
// 				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
			
// 				//Update the surface
// 				SDL_UpdateWindowSurface( g_Window );
// 			}
// 		}
// 	}

// 	//Free resources and close SDL
// 	close();

// 	return 0;
// }
