#include "Nut.h"

Nut::Nut(SHORT X, SHORT Y):Plant(X, Y)
{
	set_cost(50);
	set_hp(200);
	set();
}

void Nut::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ " ____",6 });
		std::string line = "//"; line += (char)233; line += " "; line += (char)233;  line += "\\";
		box_content()->push_back({ line, 6 });
		line = ""; line += (char)221; line += (char)221; line += " - "; line += (char)222;
		box_content()->push_back({ line, 6 });
		box_content()->push_back({ "\\\\___/" , 6 });
		box_content()->push_back({ "",15 });
	}
}
