class CGame
{
public:
	const char8_t *GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	void SetGameMode(bool value);
	void SetMenuMode(bool value);
	void SetEndMode(bool value);
	bool GetGameMode();
	bool GetMenuMode();
	bool GetEndMode();
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;
private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	bool mGameMode;
	bool mMenuMode;
	bool mEndMode;
	CGame(){};
};