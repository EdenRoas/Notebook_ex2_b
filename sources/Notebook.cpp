/**
*AUTHOR: Eden Roas
*/
#include "Notebook.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace ariel;
const int row_limit = 99;
const int minChar = 32;//asci
const int maxChar = 125;
void Notebook::write(int page, int row, int col, Direction way,const string &s_write )
{
    this->last_line_in_use[page] = row;
    if (page < 0 || row < 0 || col < 0 || col > row_limit)
    {
        throw runtime_error("Negtive Arguments & Out Of Bounds ");
    }
    int len_write = s_write.size();
    if (way == Direction::Horizontal)
    {
        if (len_write + col > row_limit)
        {
            throw runtime_error("Out Of Bounds for this string");
        }
    }
    int tempRow = row;
    int tempColumn = col;
    for (char check : s_write) //check if we can write this string here
    {
        if (check == '\n' || check == '~' || check < minChar || check > maxChar)
        {
            throw runtime_error("Invalid Input");
        }
        if (this->my_notebook[page][tempRow][tempColumn].blank != '_')
        {
            throw runtime_error("Invalid action - alredy write or erase in here");
        }
        if (way == Direction::Horizontal)
        {
            tempColumn++;
        }
        else
        {
            tempRow++;
        }
    }

    for (char write_ : s_write) // if we passed the check above,now we can write
    {
        this->my_notebook[page][row][col].blank = write_;
        if (way == Direction::Horizontal)
        {
            col++;
        }
        else
        {
            row++;
        }
    }
}
string Notebook::read(int page, int row, int col, Direction way, int lentgh) 
{
        if (page < 0 || row < 0 || col < 0 || lentgh < 0 || col > row_limit)
        {
            throw runtime_error("Negtive Arguments & Out Of Bounds ");
        }
        if (col + lentgh > row_limit + 1 && way == Direction::Horizontal)
        {
            throw runtime_error("ERROR:only 100 charactes in row");
        }
        
        string sol;
        if (way == Direction::Vertical)
        {   for (int i = 0; i < lentgh; i++)
            {
                if (minChar <= my_notebook[page][row + i][col].blank && my_notebook[page][row + i][col].blank <= maxChar + 1 )
                {
                    sol += my_notebook[page][row + i][col].blank;
                }
                else
                {
                    sol += '_';
                }
            }
            
        }
        else
        {
            for (int i = 0; i < lentgh; i++)
            {
                if (minChar <= my_notebook[page][row][col + i].blank && my_notebook[page][row][col + i].blank <= maxChar + 1)
                {
                    sol += my_notebook[page][row][col + i].blank;
                }
                else
                {
                    sol += '_';
                }
            }
            
        }
        return sol;
}
        
   
void Notebook::erase(int page, int row, int col, Direction way, int lentgh)
{
    if (page < 0 || row < 0 || col < 0 || lentgh < 0 || col > row_limit)
    {
        throw runtime_error("Negetive Arguments & Out of bounds for line");
    }
    if (way == Direction::Horizontal)
    {
        if (lentgh + col > row_limit)
        {
            throw runtime_error("Out Of Bounds for row");
        }
    }
    this->last_line_in_use[page] = row;
    for (int i = 0; i < lentgh; i++)
    {
        this->my_notebook[page][row][col].blank = '~';
        if (way == Direction::Vertical)
        {
            row++;
        }
        else
        {
            col++;
        }
    }
}

void Notebook::show(int page)
{
    if (page < 0)
    {
        throw runtime_error("Negetive Argument for page");
    }

    int row = this->last_line_in_use[page];
    Direction way = Direction::Horizontal;
    int tempRow = row;
    if (row > 0)
    {
        for (int i = tempRow - 1; i <= row + 1; i++)
        {
            this->read(page, i, 0, way, row_limit);
        }
    }
    else
    {
        for (int i = 0; i <= 1; i++)
        {
            for (int j = 0; j < row; j++)
            {
                cout << this->my_notebook[page][j][i].blank;
            }
            cout << endl;
        }
    }
}