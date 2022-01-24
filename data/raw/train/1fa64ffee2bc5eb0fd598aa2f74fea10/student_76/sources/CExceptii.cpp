#include "CExceptii.h"
#include <Windows.h>

CExceptii::CExceptii(string mesaj, int cod):mesaj(mesaj),code(cod)
{
}

void CExceptii::PrintError()
{
	string Toprint=mesaj+" cu codul "+to_string(code);
	LogsMonitor::SaveError(Toprint);
	if (code == 0)//eroare ce necesita oprirea aplicatiei
		MessageBox(0, Toprint.c_str(), "Eroare", MB_OK);
}
