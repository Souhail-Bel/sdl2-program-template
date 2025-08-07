#include <chrono>
#include <thread>

#include "display.h"

using namespace std;

const int FRAMERATE = 30;
constexpr int FRAME_DELAY_MS = 1e3/FRAMERATE;

int main(int argc, char** argv){
	init_SDL();
	
	is_running = true;
	
	while(is_running){
		handle_INPUT();
		
		update_RENDER();
		
		this_thread::sleep_for(chrono::milliseconds(FRAME_DELAY_MS));
	}
	
	close_SDL();
}