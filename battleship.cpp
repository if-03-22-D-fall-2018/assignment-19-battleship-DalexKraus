/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

#define invalid(row, col) (row < 0 || col < 0 || row >= 10 || col >= 10)

CellContent guesses[FIELDSIZE][FIELDSIZE];
CellContent myField[FIELDSIZE][FIELDSIZE];
CellContent opponentField[FIELDSIZE][FIELDSIZE];

void load_field(const char* fileName, CellContent field[FIELDSIZE][FIELDSIZE]);

/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
    for (int i = 0; i < FIELDSIZE; i++)
    {
        for (int j = 0; j < FIELDSIZE; j++)
        {
            guesses[i][j] = Unknown;
        }
    }

    FILE* fdM = fopen("battleship.my", "r");
    FILE* fdO = fopen("battleship.op", "r");

    fread(myField, sizeof(myField), 1, fdM);
    fread(opponentField, sizeof(opponentField), 1, fdO);
    fclose(fdM);
    fclose(fdO);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
    if (invalid(row, col))
        return OutOfRange;
    return myField[row][col];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
    if (invalid(row, col))
        return false;

    for (int yOffset = -1; yOffset < 3; yOffset++)
        for (int xOffset = -1; xOffset < 3; xOffset++)
        {
            if (invalid(row + yOffset, col + xOffset)) continue;                
            guesses[row + yOffset][col + xOffset] = Water;
        }

    guesses[row][col] = opponentField[row][col];
    return true;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
    if (invalid(row, col))
        return OutOfRange;
    return guesses[row][col];
}
