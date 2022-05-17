#include "../vendor/aixlog.hpp"

#include "menu.hpp"
#include "account.hpp"

void menu::start()
{
	int choice;
	bool choosing_path = true;

	while (choosing_path)
	{
		LOG(INFO) << "INFO: " << "[1] Login\n";
		LOG(INFO) << "INFO: " << "[2] Register\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			login();
			choosing_path = false;
			break;
		case 2:
			create();
			choosing_path = false;
			break;
		default:

			LOG(ERROR) << "ERROR: " << "Spatne cislo\n";

			choosing_path = false;
			break;
		}
	}
}

void menu::create()
{
	Account a{};

	std::string username;
	std::string email;
	std::string password;
	std::string phone_number;

	LOG(INFO) << "INFO: " << "* - required\n";
	std::cout << "Enter username (1-50)*: ";
	std::cin >> username;
	std::cout << "Enter email (5-50): ";
	std::cin >> email;
	std::cout << "Enter password (12-50)*: ";
	std::cin >> password;
	std::cout << "Enter phone number (9-10): ";
	std::cin >> phone_number;

	a.create(username, email, password, phone_number);
}

void menu::login()
{
	constexpr Account a{};

	std::string username;
	std::string password;

	LOG(ERROR) << "ERROR: " << "Leave blank if none\n";
	std::cout << "Enter username: ";
	std::cin >> username;
	std::cout << "Enter password: ";
	std::cin >> password;

	a.login(username, password);
}
