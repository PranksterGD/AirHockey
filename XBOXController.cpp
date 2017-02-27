#include "XBOXController.h"

XBUTTONIDs XButtons;

XBUTTONIDs::XBUTTONIDs()
{
	A = 0;
	B = 1;
	X = 2;
	Y = 3;

	DPad_Up = 4;
	DPad_Down = 5;
	DPad_Left = 6;
	DPad_Right = 7;

	L_Shoulder = 8;
	R_Shoulder = 9;

	L_Thumbstick = 10;
	R_Thumbstick = 11;

	Start = 12;
	Back = 13;
}
XBOXControllerC::XBOXControllerC(int playerNum)
{
	mControllerNum = playerNum;

	for (int i = 0; i < numberOfButtons; i++)
	{
		mPrev_ButtonStates[i] = false;
		mButtonStates[i] = false;
		mController_ButtonsDown[i] = false;
	}
}

XINPUT_STATE XBOXControllerC::GetState()
{
	memset(&mControllerState, 0, sizeof(XINPUT_STATE));
	XInputGetState(mControllerNum, &mControllerState);
	return mControllerState;
}

int XBOXControllerC::GetControllerNum()
{
	return mControllerNum;
}

void XBOXControllerC::Update()
{
	mControllerState = GetState();

	for (int i = 0; i < numberOfButtons; i++)
	{
		mButtonStates[i] =!! (mControllerState.Gamepad.wButtons& XInput_Buttons[i]);
		mController_ButtonsDown[i] = !mPrev_ButtonStates[i] && mButtonStates[i];
	}
}

void XBOXControllerC::RefreshState()
{
	memcpy(mPrev_ButtonStates, mButtonStates,sizeof(mPrev_ButtonStates));
}



bool XBOXControllerC::IsConnected()
{
	//Invoke the memset(); function to zero the XBOX_CONTROLLER_State. 
	memset(&mControllerState, 0, sizeof(XINPUT_STATE));

	//We store the XInputGetState value inside result, note that result is a DWORD which is a typedef unsigned long. 
	DWORD result = XInputGetState(mControllerNum, &mControllerState);

	//Check if the controller is disconnected using the Ternary Operator. 
	return  result == ERROR_DEVICE_NOT_CONNECTED ? false : true;
}

void XBOXControllerC::Vibrate(float left, float right)
{
	XINPUT_VIBRATION vibration;
	memset(&vibration, 0, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = (int)(left*65535.0f);
	vibration.wRightMotorSpeed = (int)(right*65535.0f);
	XInputSetState(mControllerNum, &vibration);
}


float XBOXControllerC::LeftStick_X()
{
	short sX = mControllerState.Gamepad.sThumbLX;
	float sXPercentage = (float)sX / 32768.0f;
	return sXPercentage;
}

float XBOXControllerC::LeftStick_Y()
{
	short sY = mControllerState.Gamepad.sThumbLY;
	float sYPercentage = (float)sY / 32768.0f;
	return sYPercentage;
}

float XBOXControllerC::RightStick_X()
{
	short sX = mControllerState.Gamepad.sThumbLX;
	float sXPercentage = (float)sX / 32768.0f;
	return sXPercentage;
}

float XBOXControllerC::RightStick_Y()
{
	short sY = mControllerState.Gamepad.sThumbLY;
	float sYPercentage = (float)sY / 32768.0f;
	return sYPercentage;
}

float XBOXControllerC::LeftTrigger()
{
	char trigger = mControllerState.Gamepad.bLeftTrigger;
	if (trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return trigger / 255.0f;
	else
		return 0.0f;
}

float XBOXControllerC::RightTrigger()
{
	char trigger = mControllerState.Gamepad.bRightTrigger;
	if (trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return trigger / 255.0f;
	else
		return 0.0f;
}

bool XBOXControllerC::GetButtonPressed(int buttonNumber)
{
	if (mControllerState.Gamepad.wButtons &XInput_Buttons[buttonNumber])
	{
		return true;
	}
	return false;
}
