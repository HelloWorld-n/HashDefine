#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <vector>

namespace AppSettings {
	bool colorshift = false;
	bool localTimezone = false;
	bool dualTimezone = false;
	bool backgroundColor = false;
	void apply(std::vector<std::string> args){
		for (std::string arg: args){
			std::vector<std::string> option_colorshift = {
				"--color",
				"--colors",
				"--colorfull",
				"--colorshift",
				"--rainbow",
			};
			if (
				std::any_of(
					std::begin(option_colorshift),
					std::end(option_colorshift), 
					[arg](std::string thing){return arg.compare(thing) == 0;}
				)
			){
				colorshift = true;
			}

			std::vector<std::string> option_localTimezone = {
				"--local-timezone",
				"--localTimezone",
				"--ltz",
			};
			if (
				std::any_of(
					std::begin(option_localTimezone),
					std::end(option_localTimezone), 
					[arg](std::string thing){return arg.compare(thing) == 0;}
				)
			){
				localTimezone = true;
			}

			std::vector<std::string> option_dualTimezone = {
				"--dual-timezone",
				"--dualTimezone",
				"--dtz",
			};
			if (
				std::any_of(
					std::begin(option_dualTimezone),
					std::end(option_dualTimezone), 
					[arg](std::string thing){return arg.compare(thing) == 0;}
				)
			){
				dualTimezone = true;
			}

			std::vector<std::string> option_backgroundColor = {
				"--background-color",
				"--backgroundColor",
				"--bgc",
			};
			if (
				std::any_of(
					std::begin(option_backgroundColor),
					std::end(option_backgroundColor), 
					[arg](std::string thing){return arg.compare(thing) == 0;}
				)
			){
				backgroundColor = true;
			}
		}
	}
}
