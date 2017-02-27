#include "XBOXController.h"
struct VertexFormatPos3Tex2
{   // Custom vertex format for position+normal
	float tu , tv ;             ///< texture coordinates	
	float px , py , pz ;        ///< untransformed (world-space) position
};

	class BackgroundManagerC
{
public:
	static BackgroundManagerC	*CreateInstance();
	static BackgroundManagerC	*GetInstance() {return sInstance;};
	~BackgroundManagerC(){};

	void		init(int width, int height);
	void		updateSprites(DWORD milliseconds, bool player1Win);
	void		renderSprites();
	void		drawSprite(GLuint sprite, int startX, int startY, int width, int height);
	void		shutdown();

	int			getWidth() {return mWidth;}
	int			getHeight() {return mHeight;}



private:
	static BackgroundManagerC *sInstance;
	BackgroundManagerC(){};
	int mWidth;
	int mHeight;
	GLuint mSpriteTextureMap;
	GLuint mSpriteTextureMap_StartScreen;
	GLuint mSpriteTextureMap_GameScreen;
	GLuint mSpriteTextureMap_StartButton;
	GLuint mSpriteTextureMap_ExitButton;
	GLuint mSpriteTextureMap_WinPlayer1;
	GLuint mSpriteTextureMap_WinPlayer2;

	int background;
	int menuNumber;

	DWORD mLastUpdateTime;
	DWORD mCurrentTime;
	int player1StartX;
	int player1StartY;
	int player1Width;
	int player1Height;

	int backgroundStartX;
	int backgroundStartY;
	int backgroundWidth;
	int backgroundHeight;
};

#define MOOD_UPDATE_DELTA_TIME 100