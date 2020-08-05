#pragma once

class Config {
public:
	int windowWidth = 500;
	int windowHeight = 500;
	int windowPositionX = 200;
	int windowPositionY = 100;

	bool animated = false;
	float xrotation = 0.0f;
	float yrotation = 0.0f;

	float scale = 1.0f;
	float xmovement = 0.0f;
	float ymovement = 0.0f;
	float zmovement = 0.0f;
};
