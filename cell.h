#pragma once

#include <vector>

class Cell
{
public:
    int number;
    std::vector<int> possibleNumbers;
    bool isLoaded;
    bool isValid;

public:
    Cell(int number = 0)
    {
        this->number = number;
        possibleNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        this->isLoaded = false;
        this->isValid = true;
    }

    bool has_value()
    {
        if (this->number != 0)
            return true;
        return false;
    }

    void deleteConstraintNumber(int number)
    {
        bool modified = false;
        auto it = find(possibleNumbers.begin(), possibleNumbers.end(), number);
        if (it != possibleNumbers.end())
        {
            possibleNumbers.erase(it);
        }
    }
};
