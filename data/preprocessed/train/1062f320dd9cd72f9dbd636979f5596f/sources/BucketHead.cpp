#include "BucketHead.h"
#include "EntityResolver.h"

BucketHead::BucketHead(SHORT x, SHORT y):Zombie(x, y)
{
	set_hp(200);
	set();
}

void BucketHead::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	for (auto i = 0; i < entity.plants_list()->size(); i++) {
		if (get_poz().X <= entity.plants_list()->at(i)->get_poz().X + 6
			&& get_poz().X >= entity.plants_list()->at(i)->get_poz().X
			&& get_poz().Y == entity.plants_list()->at(i)->get_poz().Y) 
		{
			entity.plants_list()->at(i)->set_hp(entity.plants_list()->at(i)->get_hp() - get_damage());
			set_speed(0);
			if (entity.plants_list()->at(i)->died())
			{
				set_speed(get_base_speed());
			}
		}
	}
}

void BucketHead::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "  __" , 12 });
		box_content()->push_back({ " /__\\" , 12 });
		box_content()->push_back({ "(o_b )" , 2 });
		std::string line = " "; line += (char)169; line += " "; line += (char)169; line += "-";
		box_content()->push_back({ line, 2 });
		line = "  "; line += (char)245; line += (char)245; //line += '\0';
		box_content()->push_back({ line, 13 });
	}
}
