#include "Element.h"

Element::Element(Vector2f posichion,string name) 
{
	this->texture.loadFromFile("Image/" + name + ".png");
	this->self.setTexture(texture);
	self.setOrigin(self.getLocalBounds().width / 2, self.getLocalBounds().height/2);
	self.setPosition(posichion);
}
