#pragma once
#include <Box2D/Box2D.h>
#include "ScoreManager.h"
class PhysicsManagerC
{
public:
	static PhysicsManagerC	*CreateInstance();
	static PhysicsManagerC	*GetInstance() { return sInstance; };
	~PhysicsManagerC() {};
	bool needToResetPlayerPositions;

	void	init();
	void	shutdown();
	void	update(ScoreManagerC* scoreManagerInstance);
	void	createWorld();
	void    createPuck();
	void	renderPuck();
	void    render();
	b2World* getWorld();
private:
	b2Vec2 gravity;
	b2World* world;

	b2BodyDef groundBodyDef;
	b2Body *groundBody;
	b2PolygonShape groundBox;

	b2BodyDef puckBodyDef;
	b2Body* puckBody;
	b2PolygonShape puckBox;
	int puckSprite;
	float puckHalfWidth;
	float puckHalfHeight;
	float puckPosX;
	float puckPosY;

	static const float puckDensity;
	static const float puckFriction;
	static const float puckRestitution;

	static PhysicsManagerC *sInstance;
	PhysicsManagerC() {};
};
