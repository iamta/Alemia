#include "ZombiFactory.h"


ZombiFactoryStrategy ZombiFactory::_current_stretegy;
chrono::high_resolution_clock::time_point ZombiFactory::_time;
int ZombiFactory::_level = 0;

std::map<int, int> ZombiFactory::_map_cycles_L1 = { {15000,1}, {9900,7} , {5000,3 }, {3000,3},{2000,4}, { 1000,20000} };
std::map<int, int>::iterator ZombiFactory::index = std::prev(_map_cycles_L1.end());

map<int,vector< Zombi*>> ZombiFactory::_map_predefined_zombi= { 
	{ 1, { new BasicZombi() } },
	{ 2 , {new BasicZombi(), new BuckedHeadZombi() } },
	{ 3  , {new BasicZombi(), new BuckedHeadZombi(), new PoleVaultingZombi() }}
};
