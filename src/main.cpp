#include <cerrno>
#include <iostream>

#define SDL_MAIN_HANDLED // Fixes 99.9% of bugs
#include <SDL2/SDL.h>

// Window dimensions
const int WIDTH  = 640;
const int HEIGHT = 480;

// Window title
const char* WIN_TITLE = "SDL2 Template"; 

// Global SDL elements
SDL_Window* 	g_window;
SDL_Renderer* 	g_renderer;
SDL_Event 		g_event;

bool is_running;

using namespace std;


void init_SDL(void);
void close_SDL(void);
void handle_INPUT(void);

void init_SDL(void){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
		perror(SDL_GetError());
		exit(-1);
	}
	
	
	g_window = SDL_CreateWindow(
		WIN_TITLE,
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



int main(int argc, char** argv){
	init_SDL();
	
	is_running = true;
	
	while(is_running){
		handle_INPUT();
	}
	
	close_SDL();
}