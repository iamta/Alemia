#include "Box.h"

void Box::empty_box()
{
	if (content.size() > 1) {
		for (auto i = 0; i < 5; i++) {
			std::string line = "";
			for (auto j = 0; j < 7; j++) {
				line += " ";
			}
			content.at(i) = { line, 15 };
		}
	}
}
