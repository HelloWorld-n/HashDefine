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
	static ShadeThing shadeThing = * new ShadeThing((int[2]){128, 255}, 25, 0);
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

std::_Put_time<char> getGlobalTime(std::time_t the_time_t){
	return std::put_time( std::gmtime( &the_time_t ), "%FT%TZ" );
}

std::_Put_time<char> getLocalTime(std::time_t the_time_t){
	return std::put_time( std::localtime( &the_time_t ), "%FT%T%z" );
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
			if (AppSettings::backgroundColor){
				std::cout << "\e[48;2;" << (
					(rgb_values[0] % 128) / 8
				) << ";" << (
					(rgb_values[1] % 128) / 8
				) << ";" << (
					(rgb_values[2] % 128) / 8
				) << "m";
			}
		} else {
			int rgb_value = gradientalThing();
			std::cout << "\e[38;2;" << rgb_value << ";" << rgb_value << ";" << rgb_value << "m";
			if (AppSettings::backgroundColor){
				std::cout << "\e[48;2;" << (
					(rgb_value % 128) / 8
				) << ";" << (
					(rgb_value % 128) / 8
				) << ";" << (
					(rgb_value % 128) / 8
				) << "m";
			}
		}
		std::cout << "\e[2J\e[1;1H";
		if (not AppSettings::localTimezone){
			std::cout << getGlobalTime(now) << "\n";
			if (AppSettings::dualTimezone){
				std::cout << getLocalTime(now) << "\n";
			}
		} else {
			std::cout << getLocalTime(now) << "\n";
			if (AppSettings::dualTimezone){
				std::cout << getGlobalTime(now) << "\n";
			}
		} 
		std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
