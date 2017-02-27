#pragma once
//
// Constants for gamepad buttons
//

#include <windows.h>
#include <Xinput.h>
static const WORD XInput_Buttons[] =
{
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

struct XBUTTONIDs
{
	XBUTTONIDs();

	int A, B, X, Y;

	int DPad_Up, DPad_Down, DPad_Left, DPad_Right;

	int L_Shoulder, R_Shoulder;

	int L_Thumbstick, R_Thumbstick;

	int Start;
	
	int Back;
};

#pragma comment(lib,"XINPUT.lib")
class XBOXControllerC
{

public:
	XBOXControllerC(int playerNum);

	XINPUT_STATE GetState();
	int GetControllerNum();

	void Update();

	float LeftStick_X();
	float RightStick_X();
	float LeftStick_Y();
	float RightStick_Y();

	float LeftTrigger();
	float RightTrigger();

	bool GetButtonPressed(int buttonNumber);
	void RefreshState();
	bool IsConnected();
	void Vibrate(float left = 0, float right = 0);

private:
	static const int numberOfButtons = 14;
	bool mPrev_ButtonStates[numberOfButtons];
	bool mButtonStates[numberOfButtons];
	bool mController_ButtonsDown[numberOfButtons];
	XINPUT_STATE mControllerState;
	int mControllerNum;
};

extern XBUTTONIDs XButtons;