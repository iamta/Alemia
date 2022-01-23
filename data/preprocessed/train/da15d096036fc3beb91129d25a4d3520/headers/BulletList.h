#pragma once
#include "Bullet.h"
#include "Bullet_normal.h"
#include "Bullet_frozen.h"
#include "Exception.h"
class BulletList
{
	Bullet* bullets[2];
	Bullet* active_bullets[300];
	int contor;
	int bullet_type[300];

public:
	BulletList();
	Bullet** get_active_bullets() { return active_bullets; }
	void add_bulet_to_list(Bullet * aux);
	void add_bullet_type_to_list(int i);
	void update_curent_bullet_position();
	void increase_contor() { contor++; }
	void print_bullet_list();
	void delete_bullet_list();
	void check_bullet_pos();
	void update_active_bullets(int i);
	int get_bullet_type(int index) { return bullet_type[index]; };
	int get_contor() { return contor; }
	virtual~BulletList();
};