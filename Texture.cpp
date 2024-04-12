#include "Texture.h"
#include "Engine.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        std::cout << "khong the tai texture" << SDL_GetError();
        return false;
    }

    //SDL_CreateTextureFromSurface: tạo kết cấu từ 1 bề mặt có sẵn
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        std::cout << "khong the tao texture " << SDL_GetError() << std:: endl;
        return false;
    }
    m_TextureMap[id] = texture; // id là key, texture là value

    return true;
}

    // SDL_RenderCopyEx: Sao chép một phần kết cấu vào kết xuất hiện tại, với khả năng xoay và lật tùy chọn.
    
void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect src = {0, 0, width, height}; // vùng nguồn: phủ kín texture là 0, 0;
    SDL_Rect dst = {x, y, width, height}; // vùng đích
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    //width, height: kích thước khung cần vẽ
    SDL_Rect src = {width*frame, height*(row -1), width, height};
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}


void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]); // huy texture có id tương ứng
    m_TextureMap.erase(id);// xoa id
}

void TextureManager::Clean()
{
    std::map <std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin();it != m_TextureMap.end();it++)
    {
        SDL_DestroyTexture(it->second);// huy texture
    }
    m_TextureMap.clear();
    std::cout << "texture map clean" << std::endl;
}