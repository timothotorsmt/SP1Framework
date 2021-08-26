#include "minigame1.h"

minigame1::minigame1()
{
    randInt1 = generateRandomNum(0);
    randInt2 = generateRandomNum(1);
    randInt3 = generateRandomNum(2);
}

minigame1::~minigame1()
{
}

int minigame1::generateRandomNum(int n)
{
    int returnNum = 0;
    while (returnNum == 0 || !isinteger((float)returnNum)) {
        int nums[3] = { 0, 0, 0 };
        char ops[2] = { '+', '+' };
        int randNum = std::rand() % 9 + 1;
        nums[1] = randNum;
        for (int i = 0; i < 2; i++) {
            int randOperator = std::rand() % 4;
            int randNum = std::rand() % 9 + 1;
            switch (randOperator) {
            case 0:
                ops[i] = '+';
                operators[(2 * n) + i] = '+';
                nums[i + 1] = randNum;
                break;
            case 1:
                ops[i] = '-';
                operators[(2 * n) + i] = '-';
                nums[i + 1] = randNum;
                break;
            case 2:
                ops[i] = 'x';
                operators[2 * n + i] = 'x';
                nums[i + 1] = randNum;
                break;
            case 3:
                ops[i] = '/';
                operators[2 * n + i] = '/';
                nums[i + 1] = randNum;
                break;
            }
        }
        if ((ops[1] == 'x' || ops[1] == '/') && (ops[0] == '+' || ops[0] == '-')) {
            returnNum = calculate((float)nums[0], calculate((float)nums[1], (float)nums[2], ops[1]), ops[0]);
        }
        else {
            returnNum = calculate(calculate((float)nums[0], (float)nums[1], ops[0]), (float)nums[2], ops[1]);
        }
    }
    return returnNum;
}

bool minigame1::checkResult(int result, int i)
{
    switch (i)
    {
    case 1:
        return (result == randInt1);
        break;
    case 2:
        return (result == randInt2);
        break;
    case 3:
        return (result == randInt3);
        break;
    }
    return false;
}

bool minigame1::isinteger(float k)
{
    return std::floor(k) == k;
}

int minigame1::getRandInt(int i)
{
    switch (i)
    {
    case 1:
        return randInt1;
    case 2:
        return randInt2;
    case 3:
        return randInt3;
    }
    return 0;
}

void minigame1::addNumber(int i)
{
    int n = numbers[i];
    n += 1;
    if (n == 10)
        n = 1;
    numbers[i] = n;
}

void minigame1::addOperator(int i)
{
    switch (operators[i]) {
    case '+':
        operators[i] = '-';
        break;
    case '-':
        operators[i] = 'x';
        break;
    case 'x':
        operators[i] = '/';
        break;
    case '/':
        operators[i] = '+';
        break;
    }
}

int minigame1::getNumber(int i)
{
    return numbers[i];
}

char minigame1::get_operator(int i)
{
    return operators[i];
}

float minigame1::getResult(int i)
{
    switch (i) {
    case 1:
        if ((operators[1] == 'x' || operators[1] == '/') && (operators[0] == '+' || operators[0] == '-')) {
            return calculate((float)numbers[0], calculate((float)numbers[1], (float)numbers[2], operators[1]), operators[0]);
        }
        else {
            return calculate(calculate((float)numbers[0], (float)numbers[1], operators[0]), (float)numbers[2], operators[1]);
        }
    case 2:
        if ((operators[3] == 'x' || operators[3] == '/') && (operators[2] == '+' || operators[2] == '-')) {
            return calculate((float)numbers[3], calculate((float)numbers[4], (float)numbers[5], operators[3]), operators[2]);
        }
        else {
            return calculate(calculate((float)numbers[3], (float)numbers[4], operators[2]), (float)numbers[5], operators[3]);
        }
    case 3:
        if ((operators[5] == 'x' || operators[5] == '/') && (operators[4] == '+' || operators[4] == '-')) {
            return calculate((float)numbers[6], calculate((float)numbers[7], (float)numbers[8], operators[5]), operators[4]);
        }
        else {
            return calculate(calculate((float)numbers[6], (float)numbers[7], operators[4]), (float)numbers[8], operators[5]);
        }
    } 
    return 0;
}

void minigame1::generatenewnums()
{
    randInt1 = generateRandomNum(0);
    randInt2 = generateRandomNum(1);
    randInt3 = generateRandomNum(2);
}

float minigame1::calculate(float a, float b, char operators)
{
    switch (operators) {
    case '+':
        return (float)(a + b);
    case '-':
        return (float)(a - b);
    case 'x':
        return (float)(a * b);
    case '/':
        if (b != 0)
            return (float)(a / b);
    }
    return 0;
}
