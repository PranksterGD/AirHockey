#pragma once
#include"XBOXController.h"
#include <Box2D/Box2D.h>
class PlayerC
{
public:
	PlayerC(int controllerNumber,int startPosX, int startPosY, b2World* world, float width, float hight);
	XBOXControllerC* getController();
	void Update(b2World* world);
	void render();
	void resetPosition();


private:
	XBOXControllerC * playerController;
	int playerSprite;
	float posX;
	float posY;
	float initialPosX;
	float initialPosY;
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;
	static const int worldToScreen = 1;
	static const float bodyToImage;
	float bodyHalfWidth;
	float bodyHalfHeight;
	float spriteWidth;
	float spriteHeight;


};