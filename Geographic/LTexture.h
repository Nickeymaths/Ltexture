#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class LTexture
{
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
public:
	LTexture();
	~LTexture();
	int getWidth();
	int getHeigth();
	void Free();
	void render(int x, int y);
	bool loadFromFile(const std::string& path);
};

