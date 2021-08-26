#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	entity_char = ' ';
}

GameObject::~GameObject()
{
}

Position GameObject::getObjectPosition()
{
	return objectPosition;
}

char GameObject::getEntityChar()
{
	return entity_char;
}

void GameObject::setEntityChar(char c)
{
	entity_char = c;
}
