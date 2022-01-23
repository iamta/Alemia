#include "Sunflower.h"
#include "Sun.h"
#include "EntityResolver.h"

Sunflower::Sunflower(SHORT x, SHORT y):Plant(x, y)
{
	set_cost(50);
	set_hp(70);
	set();
}

void Sunflower::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	if (Sun::get_rate() != 2 && !rate)
	{
		Sun::set_rate(Sun::get_rate() - 1);
		rate = true;
	}
}

void Sunflower::set()
{
	if (box_content()->size() == 0) {
		std::string line = " \\"; line += (char)245; line += "/";
		box_content()->push_back({ line, 14 });
		line = (char)196; line += " "; line += (char)250; line += (char)250; line += "-";
		box_content()->push_back({ line, 14 });
		line = " /"; line += (char)245; line += "\\";
		box_content()->push_back({ line, 14 });
		line = " _"; line += (char)186; line += "_";
		box_content()->push_back({ line, 10 });
		box_content()->push_back({ "",15 });
	}
}
