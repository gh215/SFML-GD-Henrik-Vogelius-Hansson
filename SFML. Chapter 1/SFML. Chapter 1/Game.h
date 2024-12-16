#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const float PlayerSpeed = 1.f;

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(Keyboard::Key, bool isPressed);
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
private:
	RenderWindow mWindow;
	CircleShape mPlayer;
};

Game::Game() : mWindow(VideoMode(680, 480), "SFML APP"), mPlayer()
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(Color::Cyan);
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	while (mWindow.isOpen())
	{
		Time deltaTime = clock.restart();
		processEvents();
		update();
		render();
	}
}

void Game::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
	if (key == Keyboard::W) mIsMovingUp = isPressed;
	if (key == Keyboard::S) mIsMovingDown = isPressed;
	if (key == Keyboard::A) mIsMovingLeft = isPressed;
	if (key == Keyboard::D) mIsMovingRight = isPressed;
}

void Game::processEvents()
{
	Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update()
{
	Vector2f movement(0.f, 0.f);
	if (mIsMovingUp) movement.y -= PlayerSpeed;
	if (mIsMovingDown) movement.y += PlayerSpeed;
	if (mIsMovingLeft) movement.x -= PlayerSpeed;
	if (mIsMovingRight) movement.x += PlayerSpeed;

	mPlayer.move(movement);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

