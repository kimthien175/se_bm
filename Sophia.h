#pragma once
#include "GameObject.h"
#include "BMAssetsIDs.h"

#define SOPHIA_HIT_TIME	500
#define SOPHIA_WHEELS_FRAMETIME 80

#define SOPHIA_POINTING_UP_FRAMETIME 20

// stand for pi/6
#define SOPHIA_ROT_FRAMETIME 30
//#define SOPHIA_OSCILLATION_PHASE 0.011

#define SOPHIA_HORIZONTAL_SPEED 0.08f

#define SOPHIA_STATE_IDLE 0

//MONO
#define SOPHIA_STATE_MOVE_LEFT 1
#define SOPHIA_STATE_MOVE_RIGHT 2
#define SOPHIA_STATE_LOOK_UP
#define SOPHIA_STATE_STOP_ACCELERATING 4

//DOUBLE
#define SOPHIA_STATE_MOVE_LEFT_LOOK_UP
#define SOPHIA_STATE_MOVE_RIGHT_LOOK_UP

class Sophia : public CGameObject {
	bool isOnPlatform = true;
	int platformHeight = 96;
	float halfHeight;
	//bool isLanding = false;
	//bool isJumping = false;


	// gun state
	// jump state
	// run state

	bool _isPointingUp = false;
	int pointingStep = 0;
	DWORD elapsedPointingTime = 0;
	bool  _isAcceleratingPointingUp = false;

	bool isOscillationHeightLow = false;

	bool _isRotating = false;
	DWORD elapsedRotTime = 0;
	bool isFrameRot = false;
	int rotArea = 0;

	int spriteRowSetID = ID_SPRITE_SOPHIA_HIGH;

	int wheelIndex = 0;
	bool _isLookingLeft = false;

	// wheel index update
	int spWheelCurrentFrame = -1;
	int spWheelLastFrameTime = -1;
	ULONGLONG spNow = 0;

	void UpdateSpriteFrame(DWORD dt);

	void UpdateOscillationHeight(DWORD dt);
	void UpdateRotation(DWORD dt);
	void UpdateWheelIndex();
	void UpdatePointingUp(DWORD dt);

	int SwitchPointingUpFrame();
	void FixStandingOnPlatform();
public:
	Sophia(float x, float y) : CGameObject(x, y) {
		
		FixStandingOnPlatform();
	}

	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	bool isMovingLeft() { return vx<0; }
	bool isMovingRight() { return vx > 0; }
	bool isLookingLeft() { return _isLookingLeft; }
	//bool isPointingUp() { return _isPointingUp; }
	bool isRotating() { return _isRotating; }
	//bool isAcceleratingPoitingUp() { return  _isAcceleratingPointingUp; }

	void SetRotation();
	void AcceleratePointingUp() { _isAcceleratingPointingUp = true; }
	void RelasePointingUp() {  _isAcceleratingPointingUp = false; }
};

