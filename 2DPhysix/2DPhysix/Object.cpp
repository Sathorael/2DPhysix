#include "Object.h"
#include <iostream>

Object::Object(const float X, const float Y, const float positionX, const float positionY, const float mass, bool mov, bool rot, const float gravity) :
	g(gravity),
	movable(mov),
	rotatable(rot),
	vx(0.0f),
	vy(0.0f),
	posX(positionX),
	posY(positionY),
	mass(mass),
	angle(0.0f),
	angVel(0.0f),
	forceMultiplier(100.0f)
{
	shape.setSize(sf::Vector2f(X, Y));
	shape.setOrigin(X / 2, Y / 2); // Origin also acts as center of mass. getOrigin() for access.
	shape.setPosition(posX, posY);

	for (size_t i = 0; i < 4; i++) // Push our points into a vector
	{
		points.push_back(shape.getTransform().transformPoint(shape.getPoint(i))); // World coordinates
	}

	// Hard coded, might change later, might not.
	// edge normals need to normalized ( length == 1 ) before they are added

	sf::Vector2f edge = points[0] - points[1];
	sf::Vector2f normal(edge.x, -edge.y);
	normalize(normal);
	axes.push_back(normal);

	edge = points[1] - points[2];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes.push_back(normal);

	edge = points[2] - points[3];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes.push_back(normal);

	edge = points[3] - points[0];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes.push_back(normal);

}


void Object::render(sf::RenderWindow& win)
{
	win.draw(shape);
}

void Object::updateAxes()
{
	// Hard code is best code

	for (size_t i = 0; i < 4; i++) // Push our points into a vector
	{
		points[i] = shape.getTransform().transformPoint(shape.getPoint(i));
	}

	sf::Vector2f edge = points[0] - points[1];
	sf::Vector2f normal(edge.x, -edge.y);
	normalize(normal);
	axes[0] = normal;

	edge = points[1] - points[2];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes[1] = normal;

	edge = points[2] - points[3];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes[2] = normal;

	edge = points[3] - points[0];
	normal = sf::Vector2f(edge.x, -edge.y);
	normalize(normal);
	axes[3] = normal;
}

void Object::update(float deltaTime)
{
	
	// All constant physics stuff in here, transforms for the shape etc. 
	// Collisions likely handled elsewhere (or not :O), data then moved here for processing.
	// No friction, horizontal acceleration is ignored for now.
	// Rotation ignores slowing elements.

	if (movable) // X and Y positions change.
	{
		// Standard falling motion with x-directional velocity.
		// We don't care how the object gained its velocity so mass isn't taken into account. Maybe in the future.
		posY = posY + vy * deltaTime;
		vy = vy - g * deltaTime;
		posX = posX + vx * deltaTime;
	}

	if (rotatable) // Object can rotate.
	{
		angle = angle + angVel * deltaTime;
	}

	/*for (size_t i = 0; i < 4; i++)
	{
		std::cout << "Point " << i << "\nx: " << shape.getPoint(i).x
			<< "\ny: " << shape.getPoint(i).y << "\n";
	}*/

	shape.setRotation(angle);
	shape.setPosition(posX, posY);

	updateAxes(); // Get all axes for this object for SAT.

	// Might get huge
}

