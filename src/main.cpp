#define SDL_MAIN_HANDLED // Fixes 99.9% of bugs

#include <chrono>
#include <thread>

#include "display.h"

using namespace std;

const int FRAMERATE = 60;
constexpr int FRAME_DELAY_MS = 1e3/FRAMERATE;

int main(int argc, char** argv){
	init_SDL();
	
	is_running = true;
	
	while(is_running){
		handle_INPUT();
		
		compute_FRAME();
		
		update_RENDER();
		
		this_thread::sleep_for(chrono::milliseconds(FRAME_DELAY_MS));
	}
	
	close_SDL();
}