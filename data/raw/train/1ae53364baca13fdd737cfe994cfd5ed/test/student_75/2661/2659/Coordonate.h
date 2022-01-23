#pragma once
enum ENTITATE { PLANTA, SOARE, TEREN, PROIECTIL, ZOMBIE, NONE };
enum PLANTE { FLOAREA_SOARELUI, BEAN, ICEBEAN, CHEERY, WALL_NUT, NO };
enum PROIECTILE {OFF, ON };

struct coordonate {
	int x, y;
	ENTITATE what;
	PLANTE seminte;
	PROIECTILE pr;
	coordonate();
	coordonate(int x, int y, ENTITATE Z, PLANTE T) :x(x), y(y), what(Z), seminte(T) {}
	coordonate(const coordonate&);
	coordonate(PROIECTILE pr) :pr(pr) {}
	coordonate(int x, int y, ENTITATE ent): x(x), y(y), what(ent){}
};