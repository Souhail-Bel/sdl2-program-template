#include "display.h"

int main(int argc, char** argv){
	init_SDL();
	
	is_running = true;
	
	while(is_running){
		handle_INPUT();
	}
	
	close_SDL();
}