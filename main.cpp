#include <iostream>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "enigma.h"

using namespace std;

int getChar();
int getInt(int lower, int upper);
bool isAllowed(char a);

int main()
{
    int mode;
    char plugMap[] = "abcdefghijklmnopqrstuvwxyz";
    int lRotNum = 2, mRotNum = 1, rRotNum = 0;
    int lStartPosition = 0, mStartPosition = 0, rStartPosition = 0;
    int refNum = 0;

    cout << "\nWelcome to Enigma.\n";
    while (true){
        cout << "\n 1) Transform message\n";
        cout << " 2) View settings\n";
        cout << " 3) Alter settings\n";
        cout << " 0) Quit\n";
        mode = getInt(0, 3);

        if (mode == 1){
            string message;
            int messageLength;
            Enigma enigma(plugMap, lRotNum, lStartPosition, mRotNum,
                          mStartPosition, rRotNum, rStartPosition, refNum);

            cout << "Enter a lowercase message without whitespace: \n";
            cin >> message;
            messageLength = message.length();

            for (int i = 0; i < messageLength; i++){
                char letter = message[i];
                if (isAllowed(letter)){
                    letter = enigma.transform(letter);
                    cout << letter;
                }
            }
            cout << endl;
        }

        else if (mode == 2){
            cout << "\nLeft rotor: " << lRotNum + 1 << " / Start position: " << lStartPosition + 1 << endl;
            cout << "Middle rotor: " << mRotNum + 1 << " / Start position: " << mStartPosition + 1 << endl;
            cout << "Right rotor: " << rRotNum + 1 << " / Start position: " << rStartPosition + 1 << endl;
            cout << "Reflector: " << refNum + 1 << "\n";
            cout << "Plugboard map: ";
            for (int i = 0; i < 26; i++) {
                cout << plugMap[i];
            }
            cout << endl;
        }

        else if (mode == 3) {
            int setting;
            while (true){
                cout << "\n 1) Rotors\n";
                cout << " 2) Rotor offsets\n";
                cout << " 3) Reflector\n";
                cout << " 4) Plugboard pairs\n";
                cout << " 0) Back\n";
                setting = getInt(0, 4);

                if (setting == 1) {
                    cout << "Select rotors from 1 - 5.\n";

                    cout << "Left: ";
                    lRotNum = getInt(1, 5) - 1;
                    cout << "Middle: ";
                    mRotNum = getInt(1, 5) - 1;
                    cout << "Right: ";
                    rRotNum = getInt(1, 5) - 1;
                }

                if (setting == 2) {
                    cout << "Set the rotor start positions from 1 - 26. \n";

                    cout << "Left: ";
                    lStartPosition = getInt(1, 26) - 1;
                    cout << "Middle: ";
                    mStartPosition = getInt(1, 26) - 1;
                    cout << "Right: ";
                    rStartPosition = getInt(1, 26) - 1;
                }

                if (setting == 3) {
                    cout << "Choose reflector 1 or 2: ";
                    refNum = getInt(1,2) - 1;
                }

                if (setting == 4) {
                    int toSwap;
                    cout << "How many pairs of characters would you like to swap?\n";
                    cout << "(You may swap up to 6)\n";
                    toSwap = getInt(0,6);

                    for (int i = 0; i < toSwap; i++) {
                        char a, b;
                        cout << "Pair " << i + 1 << ". Swap: ";
                        a = getChar();
                        cout << " and: ";
                        b = getChar();
                        plugMap[a - 'a'] = b;
                        plugMap[b - 'a'] = a;
                    }
                }

                if (setting == 0) {
                    break;
                }

            }

        }

        else if (mode == 0) {
            break;
        }

    }

    return 0;
}


int getChar() {
    char input;
    while(true) {
        cin >> input;
        if (isAllowed(input)) {break;}
    }
    return input;
}


int getInt(int lower, int upper) {
    int input;
    while (!(cin >> input) || input < lower || input > upper) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // cout << "Enter an integer from " << lower << " - " << upper << ":\n";
    }
    return input;
}

bool isAllowed(char a) {
    int aNum = a - 'a';
    if (aNum >= 0 && aNum < 26) {return true;}
    else {return false;}
}
