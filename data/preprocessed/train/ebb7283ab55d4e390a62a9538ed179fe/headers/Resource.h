#pragma once
class Resource
{
public:
	virtual int Value() = 0;
};

class Sun : public Resource 
{

public:
	int Value() override
	{
		return 50;
	}
};

