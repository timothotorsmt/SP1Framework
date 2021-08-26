#pragma once
#include <cmath>
#include <iostream>
#include <random>

class minigame1
{
	unsigned int randInt1;
	unsigned int randInt2;
	unsigned int randInt3;
	int numbers[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char operators[6] = { '+', '+', '+', '+', '+', '+' };

public:

	minigame1();
	~minigame1();

	int generateRandomNum(int n);
	bool checkResult(int result, int i);
	bool isinteger(float k);
	int getRandInt(int i);
	void addNumber(int i);
	float calculate(float a, float b, char operators);
	void addOperator(int i);
	int getNumber(int i);
	char get_operator(int i);
	float getResult(int i);
	void generatenewnums();
};

