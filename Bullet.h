#pragma once
#include "GameObject.h"
#include "BMAssetsIDs.h"

#define BULLET_SPEED_X 0.25f
#define BULLET_SPEED_Y 0.25f

class Bullet : public CGameObject {
	int spriteID;
public:
	Bullet(float x, float y, float dx, float dy) : CGameObject(x, y) {
		SetSpeed(BULLET_SPEED_X*dx, BULLET_SPEED_Y * dy);

		if (dx > 0) spriteID = ID_SPRITE_BULLET_RIGHT;
		else if (dx < 0) spriteID = ID_SPRITE_BULLET_LEFT;
		else if (dy > 0) spriteID = ID_SPRITE_BULLET_UP;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

