#pragma once
#include "GameObject.h"


#define PADDLE_BBOX_WIDTH	12
#define PADDLE_BBOX_HEIGHT	112

#define PADDLE_SPEED		0.2f

#define PADDLE_STATE_STAND_STILL	0
#define PADDLE_STATE_MOVE_DOWN	1
#define PADDLE_STATE_MOVE_UP			2

class Paddle : public CGameObject{

public:
	Paddle(float x, float y) : CGameObject(x, y) { state = PADDLE_STATE_STAND_STILL; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void SetState(int state);
	bool isTouchedWithScreenEdge();
};


