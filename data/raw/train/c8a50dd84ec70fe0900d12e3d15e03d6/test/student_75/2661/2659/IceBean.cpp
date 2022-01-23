#include "IceBean.h"



IceBean::IceBean()
{
	get_viata() = 7;
	get_necesar_resurse() = 175;
	get_Coord() = { 28, 0, PLANTA, ICEBEAN};
	set_Culoare("\u001b[36m");
	set_Desen("%%");
	proiectil.set_Desen("\u001b[36m  ->\u001b[37m");
	proiectil.set_tip(I_B);
}


IceBean::~IceBean()
{
}
