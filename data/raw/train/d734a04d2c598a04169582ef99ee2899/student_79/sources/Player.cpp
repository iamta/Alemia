#include "Player.h"


Player::Player()
{
}

Player::Player(std::string username, std::string password)
{
	read_file.open("list_of_players.txt", std::ios::beg);
	if (read_file.is_open() == false) {
		write_file.open("list_of_players.txt");
		write_file << username.c_str() << std::endl;
		write_file << password.c_str() << std::endl;
		write_file << " " << std::endl;
	}
	else {
		if (check_existing(read_file, username) == true) {
			write_file.open("list_of_players.txt", std::ofstream::app);
			write_file << username.c_str()  << std::endl;
			write_file << password.c_str()  << std::endl;
			write_file << " " << std::endl;
		}
		else {
			ExceptionHandler e("Userul a fost introdus deja");
			this->ok = false;
		}
	}
}



Player::~Player()
{
}

bool Player::check_existing(std::ifstream& file, std::string username)
{
	std::string s;
	while (std::getline(file, s)) {
		if (s == username) {
			return false;
		}
	}
	return true;
}

bool Player::isOk()
{
	return ok;
}
