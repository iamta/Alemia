#include "NormalB.h"

NormalB::NormalB(SHORT X, SHORT Y, int dmg):Bulet(X, Y, dmg)
{
	set();
}

void NormalB::set()
{
	if (box_content()->size() == 0) {
		std::string dot = ""; dot += (char)167;
		box_content()->push_back({ dot , 10 });
	}
}
