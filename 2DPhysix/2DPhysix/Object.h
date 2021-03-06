#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>

#define RADTODEG 57.295779513082320876f

class Object
{
public:
	Object(const float X, const float Y, const float positionX, const float positionY, const float mass, bool mov, bool rot, const float gravity);

	sf::RectangleShape& getShape()
	{
		return shape;
	}

	void setHorizontalVelocity(float vel)
	{
		vx = vel; // *forceMultiplier;
	}

	void setVerticalVelocity(float vel)
	{
		vy = vel; // *forceMultiplier;
	}

	void setAngle(float ang)
	{
		angle = ang;
	}

	void setAngularVelocity(float vel)
	{
		angVel = vel; // *forceMultiplier;
	}

	void setForceMultiplier(float value)
	{
		//forceMultiplier = value;
	}

	void normalize(sf::Vector2f& vec)
	{
		float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);

		// Can't divide by zero.
		if (magnitude > 0)
		{
			vec = sf::Vector2f(vec.x / magnitude, vec.y / magnitude);
		}
	}
	
	void setPosition(const sf::Vector2f& pos)
	{
		posX = pos.x;
		posY = pos.y;
	}

	void setDebugMode(bool yn, sf::Window* win)
	{
		debugMode = yn;
		window = win;
	}

	bool ownsPoint(const sf::Vector2f& point)
	{
		for (size_t i = 0; i < points.size(); i++)
		{
			if (points[i] == point)
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2f& getOriginOffset()
	{
		return originOffset;
	}

	std::vector<sf::Vector2f>& getPoints()
	{
		return points;
	}

	sf::Vector2f getVelocity()
	{
		sf::Vector2f vel = { vx, vy };
		return vel;
	}
	
	void setNewVelocity(const float& velX, const float& velY, const float& angularVel)
	{
		vx = velX;
		vy = velY;
		angVel = angularVel;
	}

	float& getAngularVelocity()
	{
		return angVel;
	}

	float& getAngle()
	{
		return angle;
	}

	float& getMass()
	{
		return mass;
	}

	sf::Vector2f& getSize()
	{
		return size;
	}

	float posX; // Horizontal location.
	float posY; // Vertical location.
	
	void updateAxes();

	void update(float deltaTime);
	void render(sf::RenderWindow& win);
	

	std::vector<sf::Vector2f> points; // Contains shape points in order
	std::vector<sf::Vector2f> axes; // Contains edge normals for this object.

private:
	sf::RectangleShape shape; // Shape of the object
	sf::Vector2f originOffset;
	sf::Vector2f size;
	bool movable; // Can the object be moved by anything.
	bool rotatable; // Can the object spin.
	float g; // Gravity.
	float vx; // Horizontal speed.
	float vy; // Vertical speed.
	
	float angle; // Rotation of the object in degrees.
	float angVel; // Angular velocity, how fast the object spins.
	float mass; // Mass of the object. Only used in collision handling.
	// float forceMultiplier; // Multiplies velocities etc.
	bool debugMode;
	sf::Window* window;

};

