#include "LifeForm.h"

bool LifeForm::died()
{
	if (hp >= 0)
		return false;
	return true;
}

void LifeForm::clear()
{
	box_content()->clear();
}
