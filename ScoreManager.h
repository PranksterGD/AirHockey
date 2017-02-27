#pragma once
#include "Player.h"
#include <Box2D/Box2D.h>
class ScoreManagerC
{
public:
	static ScoreManagerC	*CreateInstance();
	static ScoreManagerC	*GetInstance() { return sInstance; };
	~ScoreManagerC() {};

	void	init();
	void	shutdown();
	void	update();

	void updatePlayer1Score();
	void updatePlayer2Score();
	void renderScores();

	bool getPlayer1Win();
	bool getPlayer2Win();

private:
	int player1Score;
	int player2Score;

	int scoreSprites[5];

	int player1ScoreStartX;
	int player1ScoreEndX;
	int player1ScoreStartY;
	int player1ScoreEndY;


	int player2ScoreStartX;
	int player2ScoreEndX;
	int player2ScoreStartY;
	int player2ScoreEndY;

	bool player1Win;
	bool player2Win;

	void render(int score, int startX, int endX, int startY, int endY);
	static const int maxScore = 5;
	static ScoreManagerC *sInstance;
	ScoreManagerC() {};
};