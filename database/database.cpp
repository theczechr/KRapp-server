#include "database.hpp"

std::string db_name = "KRappDB.db3";
std::string tb_name = "users";

void database::create()
{
    LOG_INFO << "DATABASE CREATE: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
    LOG_INFO << "DATABASE CREATE: SQliteC++ version " << SQLITECPP_VERSION;
    LOG_INFO << "DATABASE CREATE: Creating new database file '" << db_name << "'";

	if (utils::file_exist(db_name))
	{
		LOG_ERROR << "DATABASE CREATE: SQLite database file '" << db_name << "' already exist, quitting";
		return;
	}

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
	LOG_INFO << "DATABASE CREATE: SQLite database file '" << db_name << "' created successfully";

	LOG_INFO << "DATABASE CREATE: Creating database table '" << tb_name << "'";
	db.exec("CREATE TABLE " + tb_name + " (id ID, username USERNAME, email_hash EMAIL_HASH, password_hash PASSWORD_HASH, phone_hash PHONE_HASH, recovery_phrase RECOVERY_PHRASE)");
	LOG_INFO << "DATABASE CREATE: Inserting NULL values";
	db.exec("INSERT INTO " + tb_name + " VALUES (NULL, NULL, NULL, NULL, NULL, NULL)"); // ??

	LOG_INFO << "DATABASE CREATE: Database created successfully, quitting";
}

void database::display()
{
	LOG_INFO << "DATABASE DISPLAY: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE DISPLAY: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE DISPLAY: Reading database file '" << db_name << "'";

	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "DATABASE DISPLAY: SQLite database file '" << db_name << "' opened successfully";

	SQLite::Statement query(db, "SELECT * FROM " + tb_name);
	LOG_INFO << "DATABASE DISPLAY: id username email_hash password_hash phone_hash recovery";
	while (query.executeStep())
	{
		std::cout << "Row (\"" << query.getColumn(0) << "\", \"" << query.getColumn(1) << "\", \"" << query.getColumn(2) << "\", \"" << query.getColumn(3) << "\", \"" << query.getColumn(4) << "\", \"" << query.getColumn(5) << "\")\n";
	}
	LOG_INFO << "DATABASE DISPLAY: Database displayed successfully, quitting";
}

bool database::item_exist(std::string name, std::string value)
{
	LOG_INFO << "DATABASE item_exist: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE item_exist: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE item_exist: Checking if user exist";

	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "DATABASE item_exist: SQLite database file '" << db_name << "' opened successfully";

	SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM " + tb_name + " WHERE " + name + " = \"" + value + "\")");
	while (query.executeStep())
	{
		if (!query.getColumn(0).getInt())
		{
			LOG_INFO << "DATABASE item_exist: Item doesnt exist";
			return false;
		}
	}
	LOG_INFO << "DATABASE item_exist: Item does exist";
	return true;
}

void database::create_account(std::string uuid, std::string username, std::string email_hash, std::string password_hash, std::string phone_hash, std::string recovery_phrase)
{
	LOG_INFO << "DATABASE create_account: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE create_account: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE create_account: Creating new user account";

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	LOG_INFO << "DATABASE create_account: SQLite database file '" << db_name << "' opened successfully";

	if (user_exist_full(uuid, username, email_hash, password_hash, phone_hash))
	{
		LOG_INFO << "DATABASE create_account: User already exist";
		return;
	}

	db.exec("INSERT INTO " + tb_name + " VALUES (\"" + uuid + "\", \"" + username + "\", \"" + email_hash + "\", \"" + password_hash + "\", \"" + phone_hash + "\", \"" + recovery_phrase + "\")");
	
	LOG_INFO << "DATABASE create_account: Account created successfully, quitting";
}

bool database::user_exist_full(std::string uuid, std::string username, std::string email_hash, std::string password_hash, std::string phone_hash)
{
	LOG_INFO << "DATABASE user_exist_full: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE user_exist_full: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE user_exist_full: Checking if user exist";

	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "DATABASE user_exist_full: SQLite database file '" << db_name << "' opened successfully";

	SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM " + tb_name + " WHERE id = \"" + uuid + "\" username = \"" + username + "\" AND email_hash = \"" + email_hash + "\" AND password_hash = \"" + password_hash + "\" AND phone_hash = \"" + phone_hash + "\")");
	while (query.executeStep())
	{
		if (!query.getColumn(0).getInt())
		{
			LOG_INFO << "DATABASE user_exist_full: User doesnt exist";
			return false;
		}
	}
	LOG_INFO << "DATABASE user_exist_full: User does exist";
	return true;
}

bool database::user_exist(std::string username, std::string password_hash)
{
	LOG_INFO << "DATABASE user_exist: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE user_exist: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE user_exist: Checking if user exist";

	SQLite::Database db(db_name, SQLite::OPEN_READONLY);
	LOG_INFO << "DATABASE user_exist: SQLite database file '" << db_name << "' opened successfully";

	SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM " + tb_name + " WHERE username = \"" + username + "\" AND password_hash = \"" + password_hash + "\")");
	while (query.executeStep())
	{
		if (!query.getColumn(0).getInt())
		{
			LOG_INFO << "DATABASE user_exist: User doesnt exist";
			return false;
		}
	}
	LOG_INFO << "DATABASE user_exist: User does exist";
	return true;
}

void database::update_user(std::string data_type, std::string old_data, std::string new_data)
{
	LOG_INFO << "DATABASE update_user: SQlite3 version " << SQLite::VERSION << " (" << SQLite::getLibVersion() << ")";
	LOG_INFO << "DATABASE update_user: SQliteC++ version " << SQLITECPP_VERSION;
	LOG_INFO << "DATABASE update_user: Updating user " << data_type;

	SQLite::Database db(db_name, SQLite::OPEN_READWRITE);
	LOG_INFO << "DATABASE update_user: SQLite database file '" << db_name << "' opened successfully";
	
	SQLite::Statement query(db, "UPDATE " + tb_name + " SET " + data_type + " = \"" + new_data + "\" WHERE " + data_type + " = \"" + old_data + "\"");
	while (query.executeStep());

	LOG_INFO << "DATABASE update_user: Successfully updated " << data_type;
}
