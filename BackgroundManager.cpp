#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "BackgroundManager.h"
#include <Box2D/Box2D.h>
#include "game.h"
#include "PlayerManager.h"
#include "soil.h"

BackgroundManagerC* BackgroundManagerC::sInstance = NULL;


BackgroundManagerC *BackgroundManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else
		sInstance = new BackgroundManagerC();
	return sInstance;
}
void BackgroundManagerC::init(int height, int width)
{

	/* load an image file directly as a new OpenGL texture */

	mSpriteTextureMap_StartScreen = SOIL_load_OGL_texture("Textures/StartScreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	mSpriteTextureMap_StartButton = SOIL_load_OGL_texture("Textures/Menu_Start.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);


	mSpriteTextureMap_ExitButton = SOIL_load_OGL_texture("Textures/Menu_Exit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	mSpriteTextureMap_GameScreen = SOIL_load_OGL_texture("Textures/AirhockeyBackground.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	mSpriteTextureMap_WinPlayer1 = SOIL_load_OGL_texture("Textures/player1winscreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	mSpriteTextureMap_WinPlayer2 = SOIL_load_OGL_texture("Textures/player2winscreen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	menuNumber = mSpriteTextureMap_StartButton;

	backgroundStartX = -23;
	backgroundStartY = -40;
	backgroundWidth = 45;
	backgroundHeight = 80;

}
void BackgroundManagerC::shutdown()
{

}
void BackgroundManagerC::renderSprites()
{

	drawSprite(background, backgroundStartX, backgroundStartY, backgroundWidth, backgroundHeight);
	if (CGame::GetInstance()->GetMenuMode())
	{
		drawSprite(menuNumber, backgroundStartX, backgroundStartY, backgroundWidth, backgroundHeight);
	}
}

void BackgroundManagerC::drawSprite(GLuint sprite, int startX, int startY, int width, int height)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sprite);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(0, 0);
	glVertex3f(startX, startY, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(startX + width, startY, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(startX + width, startY + height, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(startX, startY + height, 0.0);
	glEnd();
}

void BackgroundManagerC::updateSprites(DWORD milliseconds, bool player1Win)
{
	XBOXControllerC* player1 = PlayerManagerC::GetInstance()->getPlayer1()->getController();
	mCurrentTime += milliseconds;


	if (player1->IsConnected())
	{
		//Switching between the two states of the menu (start and exit) based on user pressing up or down
		if (CGame::GetInstance()->GetMenuMode())
		{
			background = mSpriteTextureMap_StartScreen;
			if (player1->GetButtonPressed(XButtons.DPad_Down))
			{
				player1->Vibrate(0.25f, 0.25f);
				if (menuNumber == mSpriteTextureMap_StartButton)
				{
					menuNumber = mSpriteTextureMap_ExitButton;
				}
			}

			if (player1->GetButtonPressed(XButtons.DPad_Up))
			{
				player1->Vibrate(0.25f, 0.25f);
				if (menuNumber == mSpriteTextureMap_ExitButton)
				{
					menuNumber = mSpriteTextureMap_StartButton;
				}
			}
			//If user hits start, set game mode active
			if (player1->GetButtonPressed(XButtons.Start) || (player1->GetButtonPressed(XButtons.A) && menuNumber == mSpriteTextureMap_StartButton))
			{
				CGame::GetInstance()->SetMenuMode(false);
				CGame::GetInstance()->SetGameMode(true);
			}
			//If user hits exit, exit out of the program
			if (player1->GetButtonPressed(XButtons.A) && menuNumber == mSpriteTextureMap_ExitButton)
			{
				exit(0);
			}
		}
		//If game mode active, set the background to be the board
		else if (CGame::GetInstance()->GetGameMode())
		{
			background = mSpriteTextureMap_GameScreen;
		}
		//If end mode active, set the background to be the board
		else if (CGame::GetInstance()->GetEndMode())
		{
			if (player1->GetButtonPressed(XButtons.B))
			{
				CGame::GetInstance()->SetEndMode(false);
				CGame::GetInstance()->SetMenuMode(true);
			}
			if (player1Win)
			{
				background = mSpriteTextureMap_WinPlayer1;;
			}
			else
			{
				background = mSpriteTextureMap_WinPlayer2;
			}
		}
		player1->RefreshState();
		player1->Vibrate(0, 0);
	}
}
