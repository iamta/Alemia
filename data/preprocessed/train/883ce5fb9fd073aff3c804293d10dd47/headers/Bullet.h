#pragma once
#include <iostream>
#include <windows.h>

class Bullet
{
	COORD bullet_pos;
	char B;
	COORD reset_bullet_pos;
public:
	Bullet();
	Bullet(short x, short y,char c);
	virtual void print();
	virtual void sterge();
	virtual COORD get_bullet_pos() { return bullet_pos; }
	virtual void set_bullet_pos(COORD aux);
	virtual void set_bullet_pos_from_plant(COORD aux);
	virtual void reset_bullet_poss();
	virtual void increase_X_coord() { bullet_pos.X++; }
	virtual int get_damage();
	virtual int get_slow();
	virtual~Bullet();
};

