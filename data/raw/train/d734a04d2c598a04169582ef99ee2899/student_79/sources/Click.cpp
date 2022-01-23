#include "Click.h"

UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

Click::Click() {

}


Click::~Click()
{
}

void Click::get_click(int x, int y)
{
	if (x >= 3 && x <= 5 && y >= 42 && y <= 45) {
		click_sun(1);
	}
	if (x >= 3 && x <= 5 && y >= 49 && y <= 52) {
		click_sun(2);
	}
	if (x >= 3 && x <= 5 && y >= 56 && y <= 59) {
		click_sun(3);
	}
	if (x >= 3 && x <= 5 && y >= 63 && y <= 66) {
		click_sun(4);
	}
	if (x >= 3 && x <= 5 && y >= 70 && y <= 73) {
		click_sun(5);
	}
	if (x >= 3 && x <= 5 && y >= 77 && y <= 80) {
		click_sun(6);
	}
	if (x >= 3 && x <= 5 && y >= 84 && y <= 87) {
		click_sun(7);
	}
	if (x >= 3 && x <= 5 && y >= 91 && y <= 94) {
		click_sun(8);
	}
	if (x >= 11 && x <= 14 && y >= 21 && y <= 25) {
		click_plant(1);
	}
	if (x >= 16 && x <= 19 && y >= 21 && y <= 25) {
		click_plant(2);
	}
	if (x >= 21 && x <= 24 && y >= 21 && y <= 25) {
		click_plant(3);
	}
	if (x >= 26 && x <= 29 && y >= 21 && y <= 25) {
		click_plant(4);
	}
	if (x >= 31 && x <= 34 && y >= 21 && y <= 25) {
		click_plant(5);
	}
}

void Click::click_sun(int poz)
{
	SunField* sf; sf = sf->GetInstance();
	if (sf->get_available_sun(poz)) {

		sf->set_available_sun(poz);

		switch (poz)
		{
		case 1:
			conOut(4, 43) << "  ";
			conOut(5, 43) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 2:
			conOut(4, 50) << "  ";
			conOut(5, 50) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 3:
			conOut(4, 57) << "  ";
			conOut(5, 57) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 4:
			conOut(4, 64) << "  ";
			conOut(5, 64) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 5:
			conOut(4, 71) << "  ";
			conOut(5, 71) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 6:
			conOut(4, 78) << "  ";
			conOut(5, 78) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 7:
			conOut(4, 85) << "  ";
			conOut(5, 85) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		case 8:
			conOut(4, 92) << "  ";
			conOut(5, 92) << "  ";
			this->sun_value += 50;
			conOut(5, 20) << this->sun_value << "  ";
			break;
		default:
			break;
		}
	}
}

void Click::click_plant(int nr)
{

	switch (nr)
	{
	case 1:
		if (sun_value >= 100) {
			sun_value -= 100;
			conOut(5, 20) << this->sun_value << "  ";
			put_plant(1);
		}
		else
			ExceptionHandler e("Bani insuficienti!");
		break;
	case 2:
		if (sun_value >= 50) {
			put_plant(2);
			sun_value -= 50;
			conOut(5, 20) << this->sun_value << "  ";
		}
		else
			ExceptionHandler e("Bani insuficienti!");
		break;
	case 3:
		if (sun_value >= 150) {
			put_plant(3);
			sun_value -= 150;
			conOut(5, 20) << this->sun_value << "  ";
		}
		else
			ExceptionHandler e("Bani insuficienti!");
		break;
	case 4:
		if (sun_value >= 50) {
			put_plant(4);
			sun_value -= 50;
			conOut(5, 20) << this->sun_value << "  ";
		}
		else
			ExceptionHandler e("Bani insuficienti!");
		break;
	case 5:
		if (sun_value >= 175) {
			put_plant(5);
			sun_value -= 175;
			conOut(5, 20) << this->sun_value << "  ";
		}
		else
			ExceptionHandler e("Bani insuficienti!");
		break;
	default:
		break;
	}
}

void Click::put_plant(int plant_id)
{
	UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();
	BattleField* bf; bf = bf->GetInstance();
	conOut(7, 40) << "Alegeti pozitia plantei: ";
	while (true) {
		std::string action = conIn.getUserActions();
		if (action.find("Mouse", 0) != std::string::npos) {

			if (action.find("click", 0) != std::string::npos) {
				if (bf->get_field_position(conIn.get_y(), conIn.get_x()) == -1)
					ExceptionHandler e("Pozitie invalida");
				if (bf->get_field_position(conIn.get_y(), conIn.get_x()) == 0) {
					conOut(conIn.get_y(), conIn.get_x()) << "p";
					bf->set_field_position(conIn.get_y(), conIn.get_x());
					break;
				}
				else {
					ExceptionHandler e("Pozitie ocupata");
				}
			}
		}
	}
}


