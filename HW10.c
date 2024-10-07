#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Function to set the difficulty level and initiate the game
int difficultyLevel();

// Function to check the guesses made by the player based on the chosen difficulty level
void checkguesses(int option);

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Flag to control whether to keep playing or not
    bool keepPlay = true;

    // Main game loop
    while (keepPlay)
    {
        // Displaying game introduction and rules
        printf("Welcome to ""MAGSHIMIM CODE-BREAKER""!!!\n");

        printf("Please choose the game level:\n");
        printf("1 - Easy (20 rounds)\n");
        printf("2 - Moderate (15 rounds)\n");
        printf("3 - Hard (10 rounds)\n");
        printf("4 - Crazy (random number of rounds 5-25)\n");
        printf("Make a choice: ");

        // Function call to set the difficulty level and initiate the game
        int option = difficultyLevel();

        // Function call to check the guesses based on the set difficulty level
        checkguesses(option);

        // Ask if the player wants to play again
        printf("Would you like to play again? (y/n): ");
        char play_again;
        scanf(" %c", &play_again);
        while (getchar() != '\n');  // Consume remaining characters including newline
        if (play_again != 'y')
        {
            printf("Bye Bye!\n");
            printf("Press any key to continue . . . ");
            getchar();
            keepPlay = false;
        }
    }

    return 0;
}

// Function to check the guesses made by the player based on the chosen difficulty level
void checkguesses(int option)
{
    // Secret password consisting of four unique random numbers between 1 and 6
    int digit_1, digit_2, digit_3, digit_4;

    // Generate the digits ensuring uniqueness
    do
    {
        digit_1 = 1 + rand() % 6;
        digit_2 = 1 + rand() % 6;
        digit_3 = 1 + rand() % 6;
        digit_4 = 1 + rand() % 6;
    } while (digit_2 == digit_1 || digit_3 == digit_1 || digit_3 == digit_2 || digit_4 == digit_1 || digit_4 == digit_2 || digit_4 == digit_3);

    // Set the number of rounds based on the chosen difficulty level
    int guessesNumber;
    switch (option)
    {
        case 1:
            guessesNumber = 20;
            break;
        case 2:
            guessesNumber = 15;
            break;
        case 3:
            guessesNumber = 10;
            break;
        case 4:
            guessesNumber = 5 + rand() % 21; // Random number of rounds between 5 and 25
            break;
        default:
            guessesNumber = 0; // Default value, handle as needed
            break;
    }

    // Loop to handle the player's guesses
    for (int i = 0; i < guessesNumber; ++i)
    {
        int guess = 0;

        // Prompting the user to input their guess
        printf("Write your guess (four digits between 1-6, no ENTER is needed)\n");
        if (option != 4)
        {
            printf("%d guesses left\n", guessesNumber - i);
        }

        // Read each digit individually
        int userDigit_1, userDigit_2, userDigit_3, userDigit_4;
        userDigit_1 = getchar() - '0';
        userDigit_2 = getchar() - '0';
        userDigit_3 = getchar() - '0';
        userDigit_4 = getchar() - '0';

        while (getchar() != '\n');  // Consume remaining characters including newline

        // Check for repeated digits
        if (userDigit_1 == userDigit_2 || userDigit_1 == userDigit_3 || userDigit_1 == userDigit_4 ||
            userDigit_2 == userDigit_3 || userDigit_2 == userDigit_4 || userDigit_3 == userDigit_4)
        {
            printf("Invalid input. Please enter four unique digits between 1-6.\n\n");
            --i; // Retry the current iteration
            continue;
        }

        // Initialize HITS and MISSES for each guess
        int HITS = 0;
        int MISSES = 0;

        // Check the guess against the secret password
        if (userDigit_1 == digit_1)
            HITS++;
        if (userDigit_2 == digit_2)
            HITS++;
        if (userDigit_3 == digit_3)
            HITS++;
        if (userDigit_4 == digit_4)
            HITS++;

        // Check for MISSES
        if (userDigit_1 != digit_1 && (userDigit_1 == digit_2 || userDigit_1 == digit_3 || userDigit_1 == digit_4))
            MISSES++;
        if (userDigit_2 != digit_2 && (userDigit_2 == digit_1 || userDigit_2 == digit_3 || userDigit_2 == digit_4))
            MISSES++;
        if (userDigit_3 != digit_3 && (userDigit_3 == digit_1 || userDigit_3 == digit_2 || userDigit_3 == digit_4))
            MISSES++;
        if (userDigit_4 != digit_4 && (userDigit_4 == digit_1 || userDigit_4 == digit_2 || userDigit_4 == digit_3))
            MISSES++;

        // Displaying the result of the current guess
        if (HITS == 4)
        {
            printf("    4 HITS YOU WON!!!\n\n");
            printf("It took you only %d guesses, you are a professional code breaker!\n\n", i + 1);
            return;
        }
        else
        {
            printf("You got    %d HITS    %d MISSES.\n", HITS, MISSES);
        }
    }

    // Displaying the result if the player couldn't guess the password in the allotted rounds
    printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\n");
    printf("Nothing left for you...\n");
    printf("The secret password was %d%d%d%d\n\n", digit_1, digit_2, digit_3, digit_4);
}

// Function to set the difficulty level based on user input
int difficultyLevel()
{
    enum difficulty
    {
        easy = 1,
        medium,
        hard,
        crazy
    };
    bool normalOption = false;
    int option = 0;

    // Loop to handle user input and set the difficulty level
    while (!normalOption)
    {
        scanf("%d", &option);
        while (getchar() != '\n');  // Consume remaining characters including newline
        switch (option)
        {
        // Setting the number of rounds based on the chosen difficulty level
        case easy:
        case medium:
        case hard:
            normalOption = true;
            break;
        case crazy:
            normalOption = true;
            break;
        default:
            printf("Make a choice: ");
            break;
        }
    }

    return option;
}
