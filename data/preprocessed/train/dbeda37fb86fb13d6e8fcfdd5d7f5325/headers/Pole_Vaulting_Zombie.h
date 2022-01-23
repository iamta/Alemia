#pragma once
#include "Zombie.h"

namespace Oaspete {
	class Pole_Vaulting_Zombie :
		virtual public Oaspete::Zombie
	{
	public:
		Pole_Vaulting_Zombie();
		virtual ~Pole_Vaulting_Zombie();
	};
}
