#pragma once
#include "Coordonate.h"
#include "Deseneaza.h"
#include "ConsoleOutput.h"



enum TIP_DE_ZOMBIE { S, H_B, Z, P_V };//S-simplu, H_B-head_bucket, Z-super, P_V-Pole_Vaulting 

namespace Oaspete {
	class Zombie:public Deseneaza
	{
		int viata;
		coordonate coord;
		char culoare[10];
		char desen[12];
		TIP_DE_ZOMBIE type;
		bool Ice_shot;
	protected:
		bool Jump;
	public:
		Zombie();
		virtual ~Zombie();
		virtual int& get_viata() { return viata; }
		coordonate& get_Coord() { return coord; }
		virtual void Draw(coordonate&) override;
		virtual void set_Culoare(const char*);
		virtual void set_Desen(const char*);
		void set_Type(TIP_DE_ZOMBIE aux) { type = aux; }
		TIP_DE_ZOMBIE get_Type() { return type; }
		bool actualizeaza_Zombie();
		char* get_Culoare() { return culoare; }
		void change_Speed(bool a) { Ice_shot = a; }//stabileste daca in acest zombie trage o mazare de gheata
		bool get_Speed() { return Ice_shot; }
		char* get_Desen() { return desen; }
		friend std::ostream& operator<<(std::ostream out, Zombie aux)
		{
			UserInterface::ConsoleOutput::getInstance()(aux.coord.x + 5, aux.coord.y + 15) << aux.get_Culoare();
			UserInterface::ConsoleOutput::getInstance()(aux.coord.x + 5, aux.coord.y + 15) << aux.get_Desen();
			UserInterface::ConsoleOutput::getInstance()(aux.coord.x + 5, aux.coord.y + 15) << "\u001b[37m";
			return out;
		}
		void jumped() { Jump = false; }
		bool get_Jump() { return Jump; }
		void unDraw(coordonate&);
	};
}
