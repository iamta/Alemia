#include "Bucket_Head_Zombie.h"

using namespace Oaspete;

Bucket_Head_Zombie::Bucket_Head_Zombie()
{
	get_viata() = 25;
	set_Culoare("\u001b[35m");
	set_Desen("\\~(.-.)~/ ");
	set_Type(H_B);
	get_Coord() = { 0, 225, ZOMBIE, NO };
}


Bucket_Head_Zombie::~Bucket_Head_Zombie()
{
}
