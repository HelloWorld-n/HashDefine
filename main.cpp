#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include "AppUtil.cpp"
#include "ShadeThing.cpp"

int gradientalThing(){
	static ShadeThing shadeThing = * new ShadeThing((int[2]){240, 255}, 1, 0);
	return shadeThing.iterate();
}


int *gradientalColorThing(){
	static ShadeThing shadeThing[3] = {
		/* red */ * new ShadeThing((int[2]){128, 255}, 0, 10),
		/* green */ * new ShadeThing((int[2]){128, 255}, 0, 10),
		/* blue */ * new ShadeThing((int[2]){128, 255}, 0, 10),
	};
	static int values[3];
	for (int i = 0; i < 3; i++){
		values[i] = shadeThing[i].iterate();
	}
	return values;
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
			int *rgb_values = gradientalColorThing();
			std::cout << "\e[48;2;0;0;0m";
			std::cout << "\e[38;2;" << rgb_values[0] << ";" << rgb_values[1] << ";" << rgb_values[2] << "m";
		} else {
			std::cout << "\e[38;5;" << gradientalThing() << "m";
		}
		std::cout << "\e[2J\e[1;1H";
		if ((not AppSettings::localTimezone) or AppSettings::dualTimezone){
			std::cout << std::put_time( std::gmtime( &now ), "%FT%TZ" ) << "\n";
		}
		if (AppSettings::localTimezone or AppSettings::dualTimezone){
			std::cout << std::put_time( std::localtime( &now ), "%FT%T%z" ) << "\n";
		} 
		std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
