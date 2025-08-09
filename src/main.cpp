#define SDL_MAIN_HANDLED // Fixes 99.9% of bugs

#include <chrono>
#include <thread>
#include <iostream>

#include "display.h"

using namespace std;
using namespace std::chrono;

const int FRAMERATE = 30;
constexpr int FRAME_DELAY_MS = 1e3/FRAMERATE;


int main(int argc, char** argv){
	init_SDL();
	
	is_running = true;
	
	while(is_running){
		auto start_time = high_resolution_clock::now();
		
		handle_INPUT();
		
		compute_FRAME();
		
		update_RENDER();
		
		auto end_time	= high_resolution_clock::now();

		auto delta_time = duration_cast<microseconds>(end_time - start_time);
		
		// cout << "FPS: " << 1e6/delta_time.count() << endl;
		
		// this_thread::sleep_for(chrono::milliseconds(FRAME_DELAY_MS));
	}
	
	close_SDL();
}