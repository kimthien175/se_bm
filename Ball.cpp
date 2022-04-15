#include "Ball.h"
#include "PongAssetsIDs.h"
#include "math.h"
#include <stdlib.h>   
#include <time.h>  
using namespace std;

Ball::Ball(float x, float y): CGameObject(x,y) {
	srand(time(NULL));
	int randDegreeAngle = rand() % 360;
	float randAngle = randDegreeAngle*1.0 / 360 * 2 * 3.14;
	vx = cos(randAngle) * BALL_SPEED;
	vy = sin(randAngle) * BALL_SPEED;
}

void Ball::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BALL_BBOX_WIDTH / 2;
	top = y - BALL_BBOX_HEIGHT / 2;
	right = left + BALL_BBOX_WIDTH;
	bottom = top + BALL_BBOX_HEIGHT;
}

void Ball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;
	isTouchedWithScreenEdge();
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Ball::Render() {
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_BALL)->Draw(x, y);
}

bool Ball::isTouchedWithScreenEdge() {
	int screenHeight = CGame::GetInstance()->GetBackBufferHeight();

	if (y - BALL_BBOX_HEIGHT / 2 <= 0) {
		y = BALL_BBOX_HEIGHT / 2;
		vy = vy * (-1);
		return true;
	}

	if (y + BALL_BBOX_HEIGHT / 2 >= screenHeight) {
		y = screenHeight - BALL_BBOX_HEIGHT / 2;
		vy = vy * (-1);
		return true;
	}

	int screenWidth = CGame::GetInstance()->GetBackBufferWidth();

	if (x - BALL_BBOX_WIDTH / 2 <= 0) {
		x = BALL_BBOX_WIDTH / 2;
		vx = vx * (-1);
		return true;
	}

	if (x + BALL_BBOX_HEIGHT / 2 >= screenWidth) {
		x = screenWidth - BALL_BBOX_HEIGHT / 2;
		vx = vx * (-1);
		return true;
	}

	return false;
}
