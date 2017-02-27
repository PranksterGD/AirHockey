#include "ScoreManager.h"
#include <stdio.h>
#include "soil.h"
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <cmath>

ScoreManagerC* ScoreManagerC::sInstance = NULL;

ScoreManagerC *ScoreManagerC::CreateInstance()
{
	assert(sInstance == NULL);
	sInstance = new ScoreManagerC();
	return sInstance;
}

void ScoreManagerC::init()
{

	player1Score = 0;
	player2Score = 0;
	player1Win = false;
	player2Win = false;
	int i = 0;
	scoreSprites[i++] = SOIL_load_OGL_texture("Textures/Score0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	scoreSprites[i++] = SOIL_load_OGL_texture("Textures/Score1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	scoreSprites[i++] = SOIL_load_OGL_texture("Textures/Score2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	scoreSprites[i++] = SOIL_load_OGL_texture("Textures/Score3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	scoreSprites[i++] = SOIL_load_OGL_texture("Textures/Score4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);

	player1ScoreStartX = -27;
	player1ScoreEndX = -24;
	player1ScoreStartY = -39;
	player1ScoreEndY = -36;

	player2ScoreStartX = 24;
	player2ScoreEndX = 27;
	player2ScoreStartY = 36;
	player2ScoreEndY = 39;
}

void ScoreManagerC::shutdown()
{

}

void ScoreManagerC::update()
{
	if (player1Score >= maxScore)
	{
		player1Score = 0;
		player2Score = 0;
		player1Win = true;
	
	}
	else
		if (player2Score >= maxScore)
		{
			player1Score = 0;
			player2Score = 0;
			player2Win = true;
		}
		else
		{
			player2Win = false;
			player1Win = false;
		}
}

void ScoreManagerC::updatePlayer1Score()
{
	player1Score++;
}

void ScoreManagerC::updatePlayer2Score()
{
	player2Score++;
}

bool ScoreManagerC::getPlayer1Win()
{
	return player1Win;
}

bool ScoreManagerC::getPlayer2Win()
{
	return player2Win;
}


void ScoreManagerC::renderScores()
{
	render(player1Score, player1ScoreStartX, player1ScoreEndX, player1ScoreStartY, player1ScoreEndY);
	render(player2Score, player2ScoreStartX, player2ScoreEndX, player2ScoreStartY, player2ScoreEndY);

}

void ScoreManagerC::render(int score,int startX, int endX, int startY, int endY)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, scoreSprites[score]);
	glBegin(GL_QUADS);
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(0, 0);
	glVertex3f(startX,startY, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(endX, startY, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(endX , endY, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(startX, endY, 0.0);
	glEnd();
}