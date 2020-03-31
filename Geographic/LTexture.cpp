#include "LTexture.h"

extern SDL_Renderer* gscreen;

LTexture::LTexture() {
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	Free();
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeigth() {
	return mHeight;
}

void LTexture::render(int x, int y) {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = mWidth;
		rect.h = mHeight;
		SDL_RenderCopy(gscreen, mTexture, nullptr, &rect);
}

bool LTexture::loadFromFile(const std::string& path) {
	Free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == nullptr) {
		std::cerr << "Error load Surface" << std::endl;
	}
	else {
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0FF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gscreen, loadSurface);
		if (newTexture == nullptr) {
			std::cerr << "Error create texture" << std::endl;
		}
		else {
			mWidth = loadSurface->w;
			mHeight = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}
	mTexture = newTexture;
	return (mTexture != nullptr);
}

void LTexture::Free() {
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}