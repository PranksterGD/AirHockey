#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "openGLStuff.h"
#include "game.h"
#include "BackgroundManager.h"
#include "XBOXController.h"
#include "PlayerManager.h"
#include <Box2D/Box2D.h>
#include "PhysicsManager.h"
#include "ScoreManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";
CGame* CGame::sInstance=NULL;
BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	//Start the game with menu mode
	SetGameMode(false);
	SetEndMode(false);
	SetMenuMode(true);
	//creating singletons
	BackgroundManagerC::CreateInstance();
	PlayerManagerC::CreateInstance();
	PhysicsManagerC::CreateInstance();
	ScoreManagerC::CreateInstance();

	//Initalizing the singletons
	PhysicsManagerC::GetInstance()->init();
	PlayerManagerC::GetInstance()->init(PhysicsManagerC::GetInstance()->getWorld());
	BackgroundManagerC::GetInstance()->init(28,26);
	ScoreManagerC::GetInstance()->init();
}
void CGame::UpdateFrame(DWORD milliseconds)			
{
	//Check if user hits Escape to exit out of the game
	keyProcess();
	//Check if a player has won, and if so, switch to the end mode
	if (ScoreManagerC::GetInstance()->getPlayer1Win() || ScoreManagerC::GetInstance()->getPlayer2Win())
	{
		mGameMode = false;
		mEndMode = true;
	}
	BackgroundManagerC::GetInstance()->updateSprites(milliseconds, ScoreManagerC::GetInstance()->getPlayer1Win());

	//If in game mode, call updates to the physics player and score manager
	if (GetGameMode())
	{
		PhysicsManagerC::GetInstance()->update(ScoreManagerC::GetInstance());
		PlayerManagerC::GetInstance()->update(PhysicsManagerC::GetInstance()->getWorld(), PhysicsManagerC::GetInstance()->needToResetPlayerPositions);
		ScoreManagerC::GetInstance()->update();
	}
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();
	//draw the background
	BackgroundManagerC::GetInstance()->renderSprites();
	//if in game mode, draw the players, the score and the puck
	if (GetGameMode())
	{
		PlayerManagerC::GetInstance()->renderPlayers();
		PhysicsManagerC::GetInstance()->render();
		ScoreManagerC::GetInstance()->renderScores();
	}
}

void CGame::SetGameMode(bool value)
{
	mGameMode = value;
}

void CGame::SetMenuMode(bool value)
{
	mMenuMode = value;
}

void CGame::SetEndMode(bool value)
{
	mEndMode = value;
}

bool CGame::GetGameMode()
{
	return mGameMode;
}

bool CGame::GetMenuMode()
{
	return mMenuMode;
}

bool CGame::GetEndMode()
{
	return mEndMode;
}

CGame *CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	ScoreManagerC::GetInstance()->shutdown();
	BackgroundManagerC::GetInstance()->shutdown();
	PlayerManagerC::GetInstance()->shutdown();
	PhysicsManagerC::GetInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete ScoreManagerC::GetInstance();
	delete BackgroundManagerC::GetInstance();
	delete PlayerManagerC::GetInstance();
	delete PhysicsManagerC::GetInstance();
}