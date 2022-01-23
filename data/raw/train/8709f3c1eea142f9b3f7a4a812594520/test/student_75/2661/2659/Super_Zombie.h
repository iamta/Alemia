#pragma once
#include "Pole_Vaulting_Zombie.h"
#include "Bucket_Head_Zombie.h"

namespace Oaspete {
	class Super_Zombie :
		public Pole_Vaulting_Zombie, Bucket_Head_Zombie
	{
	public:
		Super_Zombie();
		~Super_Zombie();
	};
}

