// Lab 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFPhysics.h>

using namespace sf;
using namespace std;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");

	World world(Vector2f(0, 1));
	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	
	// Create the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Create the left wall.
	PhysicsRectangle left_wall;
	left_wall.setSize(Vector2f(20, 600));
	left_wall.setCenter(Vector2f(10, 300));
	left_wall.setStatic(true);
	world.AddPhysicsBody(left_wall);

	// Create a right wall.
	PhysicsRectangle right_wall;
	right_wall.setSize(Vector2f(20, 600));
	right_wall.setCenter(Vector2f(790, 300));
	right_wall.setStatic(true);
	world.AddPhysicsBody(right_wall);

	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(200, 20));
	obstacle.setCenter(Vector2f(400, 400));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	int bangCount(0);
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		if (bangCount >= 2) {
			exit(0);
		}

		bangCount++;

		
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		
		window.draw(floor);
		window.draw(left_wall);
		window.draw(right_wall);
		window.draw(ceiling);
		window.draw(obstacle);
		window.draw(ball);

		window.display();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
