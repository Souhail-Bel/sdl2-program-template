#include <cerrno>
#include <iostream>
#include <algorithm>
#include <cmath>

#include <SDL2/SDL.h>

#include <vector>
#include <cstdint>

using namespace std;

#include "display.h"


SDL_Window* 	g_window;
SDL_Renderer* 	g_renderer;
SDL_Texture*	g_texture;
SDL_Event 		g_event;

bool is_running;


vector<bool> display_buffer(HEIGHT*WIDTH, 1);
vector<uint8_t> CANAL_R(WIN_SIZE, 0);
vector<uint8_t> CANAL_G(WIN_SIZE, 0);
vector<uint8_t> CANAL_B(WIN_SIZE, 0);


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
	
	g_renderer = SDL_CreateRenderer(
		g_window,
		-1,
		SDL_RENDERER_ACCELERATED
	);
	
	g_texture = SDL_CreateTexture(
		g_renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT
	);
	
	
	if(!g_window || !g_renderer || !g_texture){
		perror(SDL_GetError());
		SDL_Quit();
		exit(-1);
	}
}

void close_SDL(void){
	SDL_DestroyTexture(g_texture);
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
	
	// SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	// SDL_RenderClear(g_renderer);
	
	// for(int x = 0; x < WIDTH; x++) {
		// for(int y = 0; y < HEIGHT; y++) {
			// int idx = get_idx(x, y);
			
			// SDL_SetRenderDrawColor(g_renderer,
				// CANAL_R[idx],
				// CANAL_G[idx],
				// CANAL_B[idx],
			// 255);
			// if(display_buffer[idx]) SDL_RenderDrawPoint(g_renderer, x, y);
		// }
	// }
	
	// SDL_RenderPresent(g_renderer);
	
	
	// Optimized approach
	// using Lock/Unlock texture on GPU
	
	void* texture_pixels;
	int pitch;
	
	SDL_LockTexture(g_texture, NULL, &texture_pixels, &pitch);
	
	// Per pixel (32-bit) manipulation
	// ARGB format
	uint32_t* pixels = static_cast<uint32_t*>(texture_pixels);
	
	for(int idx = 0; idx < WIN_SIZE; idx++){
		if(display_buffer[idx])
			pixels[idx] = (255 << 24) | (CANAL_R[idx] << 16) | (CANAL_G[idx] << 8) | CANAL_B[idx];
		else
			pixels[idx] = 0;
	}
	
	SDL_UnlockTexture(g_texture);
	
	SDL_RenderClear(g_renderer);
	
	SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
}



float t = 0;
int amp = WIDTH/2;
int offset = amp;
int thickness = 60;

void compute_FRAME(void){
	
	fill(CANAL_B.begin(), CANAL_B.end(), 0);
	
	for(int x = amp*sin(t) + offset; x < min(static_cast<int>(amp*sin(t)) + offset + thickness, WIDTH); x++) {
		for(int y = HEIGHT/3; y < HEIGHT*2/3; y++) {
			int idx = get_idx(x,y);
			CANAL_B[idx] = 128;
		}
	}
	
	t += 0.1;
}