/* Hangman */

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>

void displayGame(int &bodyParts, std::string pickedWord, std::vector<char> blanksVector);

int main()
{
    int randInt;
    int bodyParts;
    bool wordIsComplete;
    std::string pickedWord;
    std::string fileInput;
    std::fstream file ("words.txt");

    std::vector<char> wordVector;
    std::vector<char> blanksVector;
    std::vector<char> pickedLetters;
    std::vector<std::string> listOfWords;

    // Read each word from file and insert into vector.
    while (file >> fileInput)
    {
        listOfWords.push_back(fileInput);
    }

    // Pick random word from vector.
    srand(time(NULL));
    randInt = rand() % listOfWords.size();
    pickedWord = listOfWords[randInt];

    // Slice each word into individual characters and store it into a vector.
    // Also fill in empty vector with blanks for every char in first vector.
    for (int i = 0; i < pickedWord.size(); i++)
    {
        wordVector.push_back(pickedWord[i]);
        blanksVector.push_back('_');
    }

    wordIsComplete = false;
    bodyParts = 0;

    // Entirety of game loops until user quits or guesses word.
    while (!wordIsComplete && bodyParts < 6)
    {
        std::string userInput;
        bool letterIsInWord;
        bool letterIsAlreadyPicked;

        std::cout << std::endl;

        // Uncomment to see word to be outputted to the console.
        // std::cout << "Word: ";
        // for (int i = 0; i < pickedWord.size(); i++)
        // {
        //     std::cout << wordVector[i];
        // }
        // std::cout << std::endl;

        displayGame(bodyParts, pickedWord, blanksVector);

        std::cout << "Picked letters: ";
        for (int i = 0; i < pickedLetters.size(); i++)
        {
            std::cout << pickedLetters[i] << " ";
        }
        std::cout << std::endl;

        // Handle user input, accepting word guess or a letter.
        std::cout << "Guess the word or pick a letter from a-z: ";
        std::cin >> userInput;

        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower); // Lower the cases for userInput.
        
        if (userInput.size() > 1)  // If user input length is greater than 1, check if it is a guessed word.
        {
            if (userInput == pickedWord)  // Let user continue if input matches a word.
            {
                wordIsComplete = true;
            }
            else  // Else, add a body part.
            {
                std::cout << "\nIncorrect guess." << std::endl;
                bodyParts++;
            }
        }
        else if (userInput.size() == 1)  // Else if user input length is 1, check if it is a letter.
        {
            letterIsInWord = std::count(wordVector.begin(), wordVector.end(), userInput[0]);
            letterIsAlreadyPicked = std::count(pickedLetters.begin(), pickedLetters.end(), userInput[0]);

            if (letterIsAlreadyPicked) // If user input is already found in picked letters vector, let loop fetch input again.
            {
                std::cout << "\nLetter is already picked." << std::endl;
            }
            else if (letterIsInWord)  // Else if user input is a letter in the word, replace respective blanks with letter.
            {
                for (int i = 0; i < blanksVector.size(); i++)
                {
                    if (userInput[0] == wordVector[i])
                    {
                        blanksVector[i] = userInput[0];
                    }
                }

                if (blanksVector == wordVector)
                {
                    wordIsComplete = true;
                }

                pickedLetters.push_back(userInput[0]);
            }
            else  // Else, add a body part and insert letter to picked letters vector.
            {
                std::cout << "\nIncorrect guess." << std::endl;
                bodyParts++;
                pickedLetters.push_back(userInput[0]);
            }
        }
        else  // Else, it is invalid.
        {
            std::cout << "\nInvalid input" << std::endl;
        }
    }

    // Check ending conditions: user guesses word or gets all body parts.
    if (!wordIsComplete)
    {
        std::cout << "Hangman!" << std::endl;
    }
    else
    {
        std::cout << "\nYou win! The word was: " << pickedWord << std::endl;
    }

    return 0;
}

// Update screen every time user inputs letter.
void displayGame(int &bodyParts, std::string pickedWord, std::vector<char> blanksVector)
{
    // Display body parts based on how many the user got wrong.
    std::cout << "Body parts: ";
    switch (bodyParts)
    {
        case 1:
            std::cout << "head" << std::endl;
            break;
        case 2:
            std::cout << "head, body" << std::endl;
            break;
        case 3:
            std::cout << "head, body, left arm" << std::endl;
            break;
        case 4:
            std::cout << "head, body, left arm, right arm" << std::endl;
            break;
        case 5:
            std::cout << "head, body, left arm, right arm, left leg" << std::endl;
            break;
        case 6:
            std::cout << "head, body, left arm, right arm, left leg, right leg" << std::endl;
            break;
        default:
            std::cout << "none" << std::endl;
    }

    // Display updated blank letters to screen.
    for (int i = 0; i < pickedWord.size(); i++)
    {
        std::cout << blanksVector[i] << " ";
    }
    std::cout << "\n" << std::endl;
}
