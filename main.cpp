#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include "AppUtil.cpp"

int gradientalThing(){
	int value_limits[2] = {235, 255};
	static int value = 255;
	static bool isIncrementing = false;

	if (value <= value_limits[0]){
		isIncrementing = true;
	}
	if (value >= value_limits[1]){
		isIncrementing = false;
	}

	value += isIncrementing? (+1):(-1);
	return value;
}

int main(int argc, char **argv) {
	std::vector<std::string> args;
    for(int i = 1; i < argc; i++){
        args.push_back(argv[i]);   
    };
	AppSettings::apply(args);

	std::time_t now;
	srand(time(0));
	
	
	while (true){
		now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "\e[48;5;16m";
		if (AppSettings::colorshift){
			std::cout << "\e[" << 31 + (rand() % 8) << "m";
		} else {
			std::cout << "\e[38;5;" << gradientalThing() << "m";
		}
		std::cout << "\e[2J\e[1;1H";
		std::cout << std::put_time( std::localtime( &now ), "%FT%T%z" );
		std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
