#include "Paddle.h"

void Paddle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PADDLE_BBOX_WIDTH / 2;
	top = y - PADDLE_BBOX_HEIGHT / 2;
	right = left + PADDLE_BBOX_WIDTH;
	bottom = top + PADDLE_BBOX_HEIGHT;
}

void Paddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}

void Paddle::Render() {}
