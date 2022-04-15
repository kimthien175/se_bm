#include "Paddle.h"
#include "Collision.h"
#include "PongAssetsIDs.h"

void Paddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;
	isTouchedWithScreenEdge();
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Paddle::SetState(int state) {
	switch (state) {
		case PADDLE_STATE_STAND_STILL:
			vx = 0;
			vy = 0;
			break;
		case PADDLE_STATE_MOVE_DOWN:
			vx = 0;
			vy = PADDLE_SPEED;
			break;
		case PADDLE_STATE_MOVE_UP:
			vx = 0;
			vy = -PADDLE_SPEED;
			break;
	}
	CGameObject::SetState(state);
}

bool Paddle::isTouchedWithScreenEdge() {
	int screenHeight = CGame::GetInstance()->GetBackBufferHeight();

	if (y - PADDLE_BBOX_HEIGHT/2 <= 0) {
		y = PADDLE_BBOX_HEIGHT / 2;
		return true;
	} 

	if (y + PADDLE_BBOX_HEIGHT/2 >= screenHeight ) {
		y = screenHeight - PADDLE_BBOX_HEIGHT/2;
		return true;
	}

	return false;
}

void Paddle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - PADDLE_BBOX_WIDTH / 2;
	top = y - PADDLE_BBOX_HEIGHT / 2;
	right = left + PADDLE_BBOX_WIDTH;
	bottom = top + PADDLE_BBOX_HEIGHT;
}
