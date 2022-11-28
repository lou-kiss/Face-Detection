#include "user.h"

string user::getUserName() {
    return user::userName;
}
string user::getPassword() {
    return user::password;
}
void user::setUserName() {
    cin >> user::userName;
}
void user::setPassword() {
    cin >> user::password;
}

bool user::checkUserName() {
    if (user::userName.length() < MIN_USERNAME_LENGTH) {
        cout << "UserName must be at least 5 charachters long. Try again... \n";
        return true;
    }
    if (user::userName.length() > MIN_USERNAME_LENGTH) {
        return false;
    }
}

bool user::checkPassword() {
    if (user::password.length() < MIN_PASSWORD_LENGTH) {
        cout << "Password must be at least 8 charachters long. Try again... \n";
        return true;
    }
    if (user::password.length() > MIN_PASSWORD_LENGTH) {
        return false;
    }
}

void user::encryptUserName() {
    encryptedUserName = getUserName();

    for (int i = 0; (i < 100 && encryptedUserName[i] != '\0'); i++)
        encryptedUserName[i] = encryptedUserName[i] + 2; //the key for encryption is 3 that is added to ASCII value
}

void user::encryptPassword() {
    encryptedPassword = getPassword();

    for (int i = 0; (i < 100 && encryptedPassword[i] != '\0'); i++)
        encryptedPassword[i] = encryptedPassword[i] + 2; //the key for encryption is 3 that is added to ASCII value

}

void user::writeUserInfoToFile() {
    ofstream userInfoFile;
    userInfoFile.open("userInfoFile.txt", fstream::app);

    if (userInfoFile.is_open()) {
        userInfoFile << encryptedUserName << "|" << encryptedPassword << "| \n";
        userInfoFile.close();
    }
    else {
        cout << "Unable to open file";
    }
}
