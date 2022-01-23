#pragma once
#include "Zombie.h"

namespace Oaspete {
	class Bucket_Head_Zombie :
		virtual public Oaspete::Zombie
	{
	public:
		Bucket_Head_Zombie();
		virtual ~Bucket_Head_Zombie();
	};
}