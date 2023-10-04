#include <iostream>
#include <string>
#include<cstdlib>
#include <ctime>
#include <list>
#include<algorithm>
#include <unistd.h>
#include <sstream>
#include <unordered_set>

using namespace std;

//Opens an image of the current Hangman.
int Graphic(int peices){
    string bodyParts[] {"None.jpg", "Head.jpg", "Body.jpg", "RightLeg.jpg", "LeftLeg.jpg", "RightArm.jpg", "LeftArm.jpg"};
    ostringstream fullCommand;
    fullCommand << "jp2a /home/ursomrano71/Documents/Programs/C++/HangmanProject/" << bodyParts[peices] << " --invert --height=25 --border";
    string fullCommandString = fullCommand.str();
    system(fullCommandString.c_str());
    return 0;
}
//Prints the game title, the possible letters that haven't been used, the correctly guessed letters, the remaining letters of the word,
//and calls the Graphic function if the previous guessed letter was wrong.
int PrintInfo(string alphabet, string word, unordered_set<char> letters, int manPeices) {
    system("clear");
    cout << "HANGMAN" << endl << endl;
    cout << "The possible letters you can choose are:" << endl;
    for (int a = 0; a<alphabet.length(); a++){
        if (a+1<alphabet.length())
            cout << alphabet[a] << ", ";
        else
            cout << alphabet[a] << endl;
    }
    for (int b = 0; b<word.length(); b++){
        if (letters.find(word[b])!= letters.end())
            cout << word[b];
        else
            cout << "-";
    }
    cout << endl;
    Graphic(manPeices);
    cout << "Guess a letter:" << endl;
    return 0;
}
//Defines all the variables, has the while loop, calls the PrintInfo function, calls for the user to guess a letter, checks if the word contains the letter guessed,
//removes the guessed letter from the unguessed letter list, and then checks for victory or defeat.
int main() {
    bool playing = true;
    char continuePlaying;

    while (playing == true) {
        string possibleWords[] {"bool", "char", "int", "float", "double", "void", "array", "vector"};
        srand((unsigned) time(NULL));
        int random = rand()%8;
        string chossenWord = possibleWords[random];
        string notGuessedLetters = "abcdefghijklmnopqrstuvwxyz";
        char guessedLetter;
        unordered_set<char> usedLetters;
        unordered_set<char> failedLetters;
        int hangManPeices = 0;
        int correctLettersInWord = 0;

        while (hangManPeices<6){
            PrintInfo(notGuessedLetters, chossenWord, usedLetters, hangManPeices);
            cin >> guessedLetter;
            if(usedLetters.find(guessedLetter) != usedLetters.end() || failedLetters.find(guessedLetter) != failedLetters.end())
                cout << "You already guessed that letter" << endl;
            else if (chossenWord.find(guessedLetter) != std::string::npos){
                usedLetters.insert(guessedLetter);
                for (int c = 0; c<count(chossenWord.begin(), chossenWord.end(), guessedLetter); c++)
                    correctLettersInWord++;
                cout << "Correct, That word does have that letter!" << endl;
            }
            else{
                failedLetters.insert(guessedLetter);
                cout << "Oops, the word does not contain that letter!" << endl;
                hangManPeices++;
            }
            notGuessedLetters.erase(remove(notGuessedLetters.begin(), notGuessedLetters.end(), guessedLetter), notGuessedLetters.end());
            if (correctLettersInWord == chossenWord.length()){
                system("clear");
                cout << "CONGRATS!! YOU WON!!" << endl << "The word was: " << chossenWord << endl;
                Graphic(hangManPeices);
                break;
            }
            else if (failedLetters.size() == 6){
                system("clear");
                cout << "DEFEAT!!" << endl << "The word was: " << chossenWord << endl;
                Graphic(hangManPeices);
                break;
            }
            sleep(2);
        }
        cout << "If you wish to play again press 'y', if not press 'n':" << endl;
        while (true){
            cin >> continuePlaying;
            if (continuePlaying == 'y'){
                break;
            }
            else if (continuePlaying == 'n'){
                return 0;
            }
            else{
                cout << "Wrong input, try again" << endl;
            }
        }
    }
}
