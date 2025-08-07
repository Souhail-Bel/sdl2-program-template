#include <cerrno>
#include <iostream>

#define SDL_MAIN_HANDLED // Fixes 99.9% of bugs
#include <SDL2/SDL.h>

#include "display.h"


SDL_Window* 	g_window;
SDL_Renderer* 	g_renderer;
SDL_Event 		g_event;

bool is_running;


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
			std::cout << "Key down:" << SDL_GetKeyName(g_event.key.keysym.sym) << std::endl;
			std::cout.flush();
		}
	}
}
