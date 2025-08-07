#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

// Window dimensions
const int WIDTH  = 640;
const int HEIGHT = 480;

// Global SDL elements
extern SDL_Window* 		g_window;
extern SDL_Renderer* 	g_renderer;
extern SDL_Event 		g_event;

extern bool is_running;


void init_SDL(void);
void close_SDL(void);
void handle_INPUT(void);

#endif