#include "CExceptii.h"

CExceptii::CExceptii(std::string msg)
{
	mesaj = msg;
}

std::string CExceptii::returnErr()
{
	return mesaj;
}
