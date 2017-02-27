#include "Player.h"
#include <stdio.h>
#include "soil.h"
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <cmath>

const float PlayerC::bodyToImage = 1.5f;
PlayerC::PlayerC(int controllerNum, int startPosX, int startPosY, b2World* world, float width, float height)
{
	playerController = new XBOXControllerC(controllerNum);
	if (playerController->GetControllerNum() == 0)
	{
		playerSprite = SOIL_load_OGL_texture("Textures/AirhockeyPlayer1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
	}
	else
	{
		playerSprite = SOIL_load_OGL_texture("Textures/AirhockeyPlayer2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
	}
	bodyHalfHeight = height*worldToScreen*bodyToImage;
	bodyHalfWidth = width*worldToScreen*bodyToImage;

	//The players are dynamic bodies
	bodyDef.type = b2_dynamicBody;

	//Creating the body, shape and fixture for the players
	bodyDef.position.Set(startPosX, startPosY);
	body = world->CreateBody(&bodyDef);
	dynamicBox.SetAsBox(bodyHalfWidth, bodyHalfHeight);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	body->CreateFixture(&fixtureDef);
	b2Vec2 position = body->GetPosition();
	posX = position.x * worldToScreen;
	posY = position.y * worldToScreen;
	spriteWidth = width;
	spriteHeight = height;

	initialPosX = startPosX;
	initialPosY = startPosY;
}

XBOXControllerC* PlayerC::getController()
{
	return playerController;
}

void PlayerC::Update(b2World* world)
{
	float x = 0;
	float y = 0;
	b2Vec2 position = body->GetPosition();

	playerController->Update();

	x = playerController->LeftStick_X();
	y = playerController->LeftStick_Y();

	if (abs(x) > 0.2f || abs(y) > 0.2f)
	{
		body->ApplyLinearImpulse(b2Vec2(100 * x, 100 * y), body->GetWorldCenter(), true);
	}
	else
	{
		body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}

	posX = position.x*worldToScreen;
	posY = position.y*worldToScreen;

	playerController->RefreshState();
}

//After a goal is scored, reset player positions
void PlayerC::resetPosition()
{
	body->SetTransform(b2Vec2(initialPosX, initialPosY), body->GetAngle());
}

//Draw the player
void PlayerC::render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playerSprite);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(0, 0);
	glVertex3f(posX - spriteWidth, posY - spriteHeight, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(posX + spriteWidth, posY - spriteHeight, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(posX + spriteWidth, posY + spriteHeight, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(posX - spriteWidth, posY + spriteHeight, 0.0);
	glEnd();
}