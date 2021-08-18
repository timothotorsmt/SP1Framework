#include "GameObject.h"
#include <iostream>

GameObject::~GameObject()
{
	std::cout << "GameObject have been removed!" << std::endl;
}