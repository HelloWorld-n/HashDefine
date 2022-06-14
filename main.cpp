#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>

int main() {
	std::time_t now;
	while(true){
		now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "\033[2J\033[1;1H";
		std::cout << std::put_time( std::localtime( &now ), "%FT%T%z" );
		std::cout << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
} 
