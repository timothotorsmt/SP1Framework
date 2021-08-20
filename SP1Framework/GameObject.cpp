#include "GameObject.h"
#include <iostream>

//done by dennis wong
GameObject::GameObject()
{
	entity_char = ' ';
}

GameObject::~GameObject()
{
}

//done by timothy
//edited by jeremy
Position GameObject::getObjectPosition()
{
	return objectPosition;
}

//done by dennis wong
char GameObject::getEntityChar()
{
	return entity_char;
}

//done by dennis wong
void GameObject::setEntityChar(char c)
{
	entity_char = c;
}
