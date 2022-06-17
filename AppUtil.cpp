#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <vector>

namespace AppSettings {
	bool colorshift = false;
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
		}
	}
}
