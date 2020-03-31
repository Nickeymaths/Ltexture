#include <iostream>
#include "LTexture.h"
#undef main

const int ScreenWidth = 640;
const int ScreenHeight = 480;
LTexture gFooTexture;
LTexture gBackground;

SDL_Window* gwindow = nullptr;
SDL_Renderer* gscreen = nullptr;

bool init();
void close();
bool loadMedia();

int main() {
	int pos = 0;
	bool control_move_right = true;
	bool quit = false;
	SDL_Event e;
	if (init()) {
		if (loadMedia()) {
			while (!quit) {
				gBackground.render(240, 190);
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gscreen);
				gBackground.render(0, 0);
				gFooTexture.render(pos,190);
				SDL_RenderPresent(gscreen);
				if (pos > ScreenWidth) {
					pos = ScreenWidth;
					control_move_right = false;
				}
				else if (pos < 0) {
					pos = 0;
					control_move_right = true;
				}
				else {
					if (control_move_right)
						pos += 4;
					else
						pos -= 4;
				}
				SDL_Delay(100);
			}
		}
	}
	return 0;
}

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error init vieo" << std::endl;
		success = false;
	}
	else {
		gwindow = SDL_CreateWindow("Pham Thanh Vinh",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (gwindow == nullptr) {
			std::cerr << "Error create window" << std::endl;
			success = false;
		}
		else {
			gscreen = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
			if (gscreen == nullptr) {
				std::cerr << "Error create Render" << std::endl;
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gscreen, 0xFF, 0xFF, 0xFF, 0xFF);
				if (!IMG_Init(IMG_INIT_PNG)) {
					std::cerr << "Error init IMG PNG" << std::endl;
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	if (!gFooTexture.loadFromFile("foo.png")) {
		std::cerr << "Error load foo" << std::endl;
			success = false;
	}
	if (!gBackground.loadFromFile("background.png")){
		std::cerr << "Error load background" << std::endl;
			success = false;
	}
	return success;
}

void close() {
	gFooTexture.Free();
	gBackground.Free();
	SDL_DestroyRenderer(gscreen);
	gscreen = nullptr;
	SDL_DestroyWindow(gwindow);
	gwindow = nullptr;
	IMG_Quit();
	SDL_Quit();
}