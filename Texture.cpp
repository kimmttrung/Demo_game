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

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        std::cout << "khong the tao texture " << SDL_GetError() << std:: endl;
        return false;
    }
    m_TextureMap[id] = texture;

    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect src = {0, 0, width, height};
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect src = {width*frame, height*(row-1), width, height};
    SDL_Rect dst = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &src, &dst, 0, nullptr, flip);
}


void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}
void TextureManager::Clean()
{
    std::map <std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin();it != m_TextureMap.end();it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    std::cout << "texture map clean" << std::endl;
}