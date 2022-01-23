#pragma once

#include <string>


class CExceptii
{
	std::string mesaj;

public:

	CExceptii(std::string);

	std::string returnErr();

};

