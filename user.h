#pragma once

#define MIN_USERNAME_LENGTH 5
#define MIN_PASSWORD_LENGTH 8

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class user {
private:
	string userName;
	string password;

	string encryptedUserName;
	string encryptedPassword;
public:
	string getUserName();
	string getPassword();
	void setUserName();
	void setPassword();

	bool checkUserName();
	bool checkPassword();

	void encryptUserName();
	void encryptPassword();
	void writeUserInfoToFile();
};

