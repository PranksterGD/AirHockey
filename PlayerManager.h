#include "Player.h"
#include <Box2D/Box2D.h>
class PlayerManagerC
{
public:
	static PlayerManagerC	*CreateInstance();
	static PlayerManagerC	*GetInstance() { return sInstance; };
	~PlayerManagerC() {};

	void	init(b2World* world);
	void	shutdown();
	void	update(b2World* world, bool needToResetPlayerPositions);

	PlayerC* getPlayer1();
	PlayerC* getPlayer2();
	void	renderPlayers();
	void	resetPlayerPositions();

private:
	PlayerC* player1;
	PlayerC* player2;

	static const int player1StartPosX = 0;
	static const int player1StartPosY = -25;
	static const int player2StartPosX = 0;
	static const int player2StartPosY = 25;
	
	
	static PlayerManagerC *sInstance;
	PlayerManagerC() {};
};