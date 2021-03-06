#pragma once
#include "GameObject.h"

#define BALL_BBOX_WIDTH		24
#define BALL_BBOX_HEIGHT	24

#define BALL_SPEED	0.2f

class Ball:public CGameObject{
public:
	Ball(float x, float y);
	// bounding box ???

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 1; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt);

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	bool isTouchedWithScreenEdge();

	void OnCollisionWithPaddle(LPCOLLISIONEVENT e);
};

