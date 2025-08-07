#include <cerrno>
#include <iostream>

#define SDL_MAIN_HANDLED // Fixes 99.9% of bugs
#include <SDL2/SDL.h>

#include <vector>
#include <cstdint>

using namespace std;

#include "display.h"


SDL_Window* 	g_window;
SDL_Renderer* 	g_renderer;
SDL_Event 		g_event;

bool is_running;


vector<bool> display_buffer(HEIGHT*WIDTH, 1);
vector<uint8_t> CANAL_R(HEIGHT*WIDTH, 255);
vector<uint8_t> CANAL_G(HEIGHT*WIDTH, 255);
vector<uint8_t> CANAL_B(HEIGHT*WIDTH, 125);


constexpr int get_idx(int x, int y) {
	return y * WIDTH + x;
}


void init_SDL(void){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
		perror(SDL_GetError());
		exit(-1);
	}
	
	
	g_window = SDL_CreateWindow(
		"SDL2 Template",
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_SHOWN
	);
	
	if(!g_window){
		perror(SDL_GetError());
		SDL_Quit();
		exit(-1);
	}
	
	
	g_renderer = SDL_CreateRenderer(
		g_window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	
	if(!g_renderer){
		perror(SDL_GetError());
		SDL_DestroyWindow(g_window);
		SDL_Quit();
		exit(-1);
	}
}

void close_SDL(void){
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	
	SDL_Quit();
}


void handle_INPUT(void){
	while(SDL_PollEvent(&g_event)){
		if(g_event.type == SDL_QUIT) is_running = false;
		
		if(g_event.type == SDL_KEYDOWN){
			cout << "Key down:" << SDL_GetKeyName(g_event.key.keysym.sym) << endl;
			cout.flush();
		}
	}
}

void update_RENDER(void){
	
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);
	
	for(int x = 0; x < WIDTH; x++) {
		for(int y = 0; y < HEIGHT; y++) {
			int idx = get_idx(x, y);
			
			SDL_SetRenderDrawColor(g_renderer,
				CANAL_R[idx]%(y+1),
				CANAL_G[idx]%(x+1),
				CANAL_B[idx]%(x*y+1),
			255);
			
			if(display_buffer[idx]) SDL_RenderDrawPoint(g_renderer, x, y);
		}
	}
	
	SDL_RenderPresent(g_renderer);
}