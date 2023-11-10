/*
 *     Assignment 1b, Bulls and cows
 *
 *     (Read ASSIGNMENT1b.txt carefully before you start coding)
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/// @brief Count the number of digits in a integer.
/// @param numberToCheck Integer to count
/// @return The number of digits
int n_digits(int numberToCheck);

/// @brief Get a certain digit index from a integer.
/// @param numberToCheck The number you want to select the digit from.
/// @param digitIndex The digit number you want to retrieve (starts at 0)
/// @return The digit at the selected position. (-1 if not possible)
int get_digit_at_position(int numberToCheck, int digitIndex);

/// @brief Checks wheter a certain digit exists in an integer
/// @param numberToCheck The integer to check within
/// @param digit The digit to check inside of the integer.
/// @return true or false, depending on if the digit exists.
bool digit_is_in(int numberToCheck, int digit);

/// @brief Checks if a integer has a unique amount of digits.
/// @param numberToCheck The integer to check.
/// @return True or false depending on if it's has a unique amount of digits.
bool is_unique_digits(int numberToCheck);

/// @brief Gives a random unique number with the length of amountOfDigits.
/// @param amountOfDigits The length of the number, cannot exceed 9 and must be > 0.
/// @return The randomized unique number.
int get_random_digits(int amountOfDigits);

/// @brief Counts the digit matches between to integers.
/// @param numberA Integer 1
/// @param numberB Integer 2
/// @return The matches that occurred in the two numbers.
int n_exact_digit_matches(int numberA, int numberB);

/// @brief Checks how many digit matches the integers have, discarding the positioning.
/// @param numberA The first integer to check
/// @param numberB The second integer to check
/// @return The amount of digits that match.
int n_digit_matches(int numberA, int numberB);

// Get input from player
int get_player_guess();

void show_bulls_and_cows(int guess, int answer);

int main(void)
{
    srand((unsigned int)time(NULL)); // Init random number generator

    while (1)
    {

        int answer = get_random_digits(4);

        printf("Welcome to Bulls and Cows\n");
        printf("Try to guess a 4 digit number with digits 1-9\n");
        printf("and no repeating digits (-1 to abort).\n\n");
        printf("Bulls = correct digit(s) in correct positions.\n");
        printf("Cows = correct digit(s).\n\n");

        bool aborted = false;
        int n_guess = 0;
        int guess = 0;
        int bulls = 0;

        printf("Answer: %d\n", answer);

        int lengthOfAnswer = n_digits(answer);

        while (!aborted)
        {
            guess = get_player_guess();

            int lengthOfGuess = n_digits(guess);

            if (guess == -1)
            {
                aborted = true;

                break;
            }
            else if (lengthOfGuess < lengthOfAnswer)
            {
                printf("Your guess needs to be atleast %d numbers.\n", lengthOfAnswer);

                continue;
            }
            else if (!is_unique_digits(guess))
            {
                printf("Your guess must have unique digits.\n");

                continue;
            }

            bulls = n_exact_digit_matches(guess, answer);

            n_guess++;

            if (bulls >= lengthOfAnswer)
            {
                break;
            }
            else
            {
                show_bulls_and_cows(guess, answer);
            }
        }

        if (aborted)
        {
            printf("Game aborted\n");

            break;
        }
        else
        {
            printf("Done, number was %d and you needed %d guesses\n", answer, n_guess);
        }
    }

    // TODO Ask the player if they want to play again (by selecting either 0 or 1)

    return 0;
}

int get_player_guess()
{
    int playerGuess;

    printf("Guess > ");
    scanf("%d", &playerGuess);

    return playerGuess;
}

int n_digits(int numberToCheck)
{
    int numberOfDigits = 0;

    while (numberToCheck > 0)
    {
        numberToCheck /= 10;

        numberOfDigits++;
    }

    return numberOfDigits;
}

int get_digit_at_position(int numberToCheck, int digitIndex)
{
    int numberOfDigits = n_digits(numberToCheck);

    // If you try to retrieve a digit that doesn't exist, return -1.
    if (numberOfDigits < digitIndex)
        return -1;

    while (digitIndex > 0)
    {
        numberToCheck = numberToCheck / 10;

        digitIndex--;
    }

    return numberToCheck % 10;
}

bool digit_is_in(int numberToCheck, int digit)
{
    int numberOfDigits = n_digits(numberToCheck);

    while (numberOfDigits > 0)
    {
        int numberAtPosition = get_digit_at_position(numberToCheck, numberOfDigits - 1);

        if (numberAtPosition == digit)
        {
            return true;
        }

        numberOfDigits--;
    }

    return false;
}

bool is_unique_digits(int numberToCheck)
{
    // The amount of numbers to check 1-9
    const int Base = 10;

    int numberOfDigits = n_digits(numberToCheck);

    // No bother checking if it's above the accepted range (1-9)
    if (numberOfDigits >= Base)
    {
        return false;
    }

    int unique = true;

    while (unique && numberToCheck)
    {
        int digit = numberToCheck % Base;
        int tempInt = numberToCheck /= Base;

        while (tempInt && digit != tempInt % Base)
        {

            tempInt /= Base;
        }

        unique = tempInt == 0;
    }

    return unique;
}

int get_random_digits(int amountOfDigits)
{
    if (amountOfDigits > 9 || amountOfDigits <= 0)
    {
        return 0;
    }

    int randomizedInteger = 0;

    while (amountOfDigits > 0)
    {
        int randomNumber = rand() % 9 + 1;

        if (!digit_is_in(randomizedInteger, randomNumber))
        {
            randomizedInteger = randomizedInteger * 10 + randomNumber;

            amountOfDigits--;
        }
    }

    return randomizedInteger;
}

int n_exact_digit_matches(int numberA, int numberB)
{
    int matches = 0;

    int numberADigits = n_digits(numberA);
    int numberBDigits = n_digits(numberB);

    int amountOfChecks = numberADigits > numberBDigits ? numberBDigits : numberADigits;

    while (amountOfChecks > 0)
    {
        int digitAtA = get_digit_at_position(numberA, amountOfChecks - 1);
        int digitAtB = get_digit_at_position(numberB, amountOfChecks - 1);

        if (digitAtA == digitAtB)
        {
            matches++;
        }

        amountOfChecks--;
    }

    return matches;
}

int n_digit_matches(int numberA, int numberB)
{
    int matches = 0;

    int numberADigits = n_digits(numberA);
    int numberBDigits = n_digits(numberB);

    if (numberADigits != numberBDigits)
    {
        return 0;
    }

    if (!is_unique_digits(numberA) || !is_unique_digits(numberB))
    {
        return 0;
    }

    while (numberADigits > 0)
    {
        int digitAtIndex = get_digit_at_position(numberA, numberADigits - 1);

        if (digit_is_in(numberB, digitAtIndex))
        {
            matches++;
        }

        numberADigits--;
    }

    return matches;
}

void show_bulls_and_cows(int guess, int answer)
{
    int guessLength = n_digits(guess);

    char bullsString[guessLength + 1];

    for (int currentGuessIndex = 0; currentGuessIndex < guessLength; currentGuessIndex++)
    {
        int guessDigit = get_digit_at_position(guess, currentGuessIndex);
        int answerDigit = get_digit_at_position(answer, currentGuessIndex);

        if (guessDigit == answerDigit)
        {
            bullsString[guessLength - currentGuessIndex] = 'B';
        }
        else if (digit_is_in(answer, guessDigit))
        {
            bullsString[guessLength - currentGuessIndex] = 'C';
        }
        else
        {
            bullsString[guessLength - currentGuessIndex] = '0';
        }
    }

    printf("\nBulls = B\n");
    printf("Cows = C\n");
    printf("%s\n\n", bullsString);
}