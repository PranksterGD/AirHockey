#include "PlayerManager.h"
#include <assert.h>
#include "soil.h"
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <cmath>
PlayerManagerC* PlayerManagerC::sInstance = NULL;

PlayerManagerC *PlayerManagerC::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new PlayerManagerC();
	return sInstance;
}

//Creates the two players
void PlayerManagerC::init(b2World* world)
{
	float playerWidth = 1.5f;
	float playerHeight= 1.5f;
	player1 = new PlayerC(0, player1StartPosX, player1StartPosY, world, playerWidth, playerHeight);
	player2 = new PlayerC(1, player2StartPosX, player2StartPosY,world, playerWidth, playerHeight);
}

//Updates both the players
void PlayerManagerC::update(b2World* world, bool needToResetPlayerPositions)
{
	player1->Update( world);
	player2->Update(world);	
	if (needToResetPlayerPositions)
	{
		resetPlayerPositions();
	}
}

PlayerC* PlayerManagerC::getPlayer1()
{
	return player1;
}

PlayerC* PlayerManagerC::getPlayer2()
{
	return player2;
}

void PlayerManagerC::renderPlayers()
{
	player1->render();
	player2->render();
}

void PlayerManagerC::resetPlayerPositions()
{
	player1->resetPosition();
	player2->resetPosition();
}

void PlayerManagerC::shutdown()
{
	delete(player1->getController());
	delete(player1);
	delete(player2->getController());
	delete(player2);
}