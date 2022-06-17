#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>
#include <random>

int main() {
	std::time_t now;
	srand(time(0));
	while(true){
		now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "\e[48;5;16m\e[" << 31 + (rand() % 8) << "m";
		std::cout << "\e[2J\e[1;1H";
		std::cout << std::put_time( std::localtime( &now ), "%FT%T%z" );
		std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
