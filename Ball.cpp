#include "Ball.h"
#include "PongAssetsIDs.h"

void Ball::GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

void Ball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}

void Ball::Render() {
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_BALL)->Draw(x, y);
}
