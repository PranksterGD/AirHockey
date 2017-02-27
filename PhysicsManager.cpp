#include "Player.h"
#include <stdio.h>
#include "soil.h"
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <cmath>
#include "PhysicsManager.h"

PhysicsManagerC* PhysicsManagerC::sInstance = NULL;
const float PhysicsManagerC::puckDensity = 0.5f;
const float PhysicsManagerC::puckFriction = 1.0f;
const float PhysicsManagerC::puckRestitution = 0.8f;
PhysicsManagerC *PhysicsManagerC::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new PhysicsManagerC();
	return sInstance;
}

void PhysicsManagerC::init()
{
	createWorld();
	createPuck();
	puckSprite = SOIL_load_OGL_texture("Textures/AirhockeyPuck.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
	needToResetPlayerPositions = false;
}

b2World* PhysicsManagerC::getWorld()
{
	return world;
}

void PhysicsManagerC::createPuck()
{
	puckBodyDef.position.Set(0.0f, 0.0f);  //Puck starts off at the center of the screen
	puckBodyDef.type = b2_dynamicBody;	  //The puck is a dynamic body
	puckBody = world->CreateBody(&puckBodyDef);
	puckBox.SetAsBox(0.5f, 0.5f);		//Creating the shape of the puck

	//Setting the fixture for the puck, and group index so it can pass through the middle of the board
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &puckBox;
	fixtureDef.density = puckDensity;
	fixtureDef.friction = puckFriction;
	fixtureDef.restitution = puckRestitution;
	fixtureDef.filter.groupIndex = -1;
	puckBody->CreateFixture(&fixtureDef);
	puckHalfWidth = 1.2;
	puckHalfHeight = 1.2;
}

void PhysicsManagerC::update(ScoreManagerC* scoreManagerInstance)
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 10;
	int32 positionIterations = 10;	
	world->Step(timeStep, velocityIterations, positionIterations);
	puckPosX = puckBody->GetPosition().x;
	puckPosY = puckBody->GetPosition().y;

	//Testing if player 2 scores
	if (puckPosX >= -7.0f &&puckPosX<=7.0f && puckPosY<=-38.0f)
	{
		puckBody->SetTransform(b2Vec2(0.0f, 0.0f), puckBody->GetAngle());
		puckBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		scoreManagerInstance->updatePlayer2Score();
		needToResetPlayerPositions = true;
	}

	//Testing if player 1 scores
	else	if (puckPosX >= -7.0f &&puckPosX <= 7.0f && puckPosY >= 38.0f)
	{
		puckBody->SetTransform(b2Vec2(0.0f, 0.0f), puckBody->GetAngle());
		puckBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		scoreManagerInstance->updatePlayer1Score();
		needToResetPlayerPositions = true;
	}
	else
	{
		needToResetPlayerPositions = false;
	}

}

//Creating the edges around the board so that game objects do not fly of out the screen.
void PhysicsManagerC::createWorld()
{
	gravity.Set(0.0f, 0.0f);
	world = new b2World(gravity);
	groundBodyDef.position.Set(0.0f, 0.0f);
	groundBodyDef.type = b2_staticBody;
	groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape edge;
	//bottom edge
	edge.Set(b2Vec2(-23.0f, -40.0f), b2Vec2(22.0f, -40.0f));
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.0f;
	fixtureDef.shape = &edge;
	//left edge
	groundBody->CreateFixture(&fixtureDef);
	edge.Set(b2Vec2(-23.0f, -40.0f), b2Vec2(-23.0f, 40.0f));
	fixtureDef.shape = &edge;
	//top edge
	groundBody->CreateFixture(&fixtureDef);
	edge.Set(b2Vec2(-23.0f, 40.0f), b2Vec2(22.0f, 40.0f));
	fixtureDef.shape = &edge;
	//right edge
	groundBody->CreateFixture(&fixtureDef);
	edge.Set(b2Vec2(22.0f, -40.0f), b2Vec2(22.0f, 40.0f));
	fixtureDef.shape = &edge;
	//bot goal left edge
	groundBody->CreateFixture(&fixtureDef);
	edge.Set(b2Vec2(-7.0f, -40.0f), b2Vec2(-7.0f, -38.0f));
	fixtureDef.shape = &edge;
	groundBody->CreateFixture(&fixtureDef);
	//bot goal right edge
	edge.Set(b2Vec2(7.0f, -40.0f), b2Vec2(7.0f, -38.0f));
	fixtureDef.shape = &edge;
	groundBody->CreateFixture(&fixtureDef);
	//top goal left edge
	groundBody->CreateFixture(&fixtureDef);
	edge.Set(b2Vec2(-7.0f, 40.0f), b2Vec2(-7.0f, 38.0f));
	fixtureDef.shape = &edge;
	groundBody->CreateFixture(&fixtureDef);
	//top goal right edge
	edge.Set(b2Vec2(7.0f, 40.0f), b2Vec2(7.0f, 38.0f));
	fixtureDef.shape = &edge;
	groundBody->CreateFixture(&fixtureDef);

	//mid edge
	edge.Set(b2Vec2(-23.0f, 0.0f), b2Vec2(22.0f, 0.0f));
	fixtureDef.shape = &edge;
	fixtureDef.filter.groupIndex = -1;
	groundBody->CreateFixture(&fixtureDef);

}

void PhysicsManagerC::render()
{

	renderPuck();
}

void PhysicsManagerC::shutdown()
{
	delete(world);
}

//Drawing the puck
void PhysicsManagerC::renderPuck()
{
	puckPosX = puckBody->GetPosition().x;
	puckPosY = puckBody->GetPosition().y;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, puckSprite);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(0, 0);
	glVertex3f(puckPosX - puckHalfWidth, puckPosY - puckHalfHeight, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(puckPosX + puckHalfWidth, puckPosY - puckHalfHeight, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(puckPosX + puckHalfWidth, puckPosY + puckHalfHeight, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(puckPosX - puckHalfWidth, puckPosY + puckHalfHeight, 0.0);
	glEnd();
}