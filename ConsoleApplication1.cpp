#include "faceDetector.h"
#include "user.h"

using namespace std;
using namespace cv;


int main(int argc, char** argv) {
    String userName;
    String password;
    bool unsatisfied = true;
    String answer;
    int functionReturnValue = 0;
    user User;

    cout << "Welcome to the Facial Detection Application! \n ";

    do {
        cout << "Please provide a username : \n";
        User.setUserName();
    } while (User.checkUserName());

    do {
        cout << "Please provide a password in order to register: \n";
        User.setPassword();
    } while (User.checkPassword());

    cout << "User registered in our system! \n Do you want to detect a face using an image or a video source?";
    cout << "Press [V] for Video and [I] for image: ... \n";
    cin >> answer;


    User.encryptUserName();
    User.encryptPassword();
    User.writeUserInfoToFile();

    while (unsatisfied) {
        if (answer == "V" || answer == "v") {
            unsatisfied = false;
            functionReturnValue = videoDetection();
        }
        else if (answer == "I" || answer == "i") {
            unsatisfied = false;
            functionReturnValue = imageDetection();
        }
        else {
            cout << "Press [V] for Video and [I] for image: ... \n";
            cin >> answer;
        }
    }

    if (functionReturnValue == 0) {
        return 0;
    }
    else if (functionReturnValue == -1) {
        return -1;
    }
    else if (functionReturnValue == 1) {
        return 1;
    }
}
