#include "Bullet.h"
#include "BMScene.h"
#include <math.h>

void Bullet::Render() {
	if (!isDeleted) {
		CSprites::GetInstance()->Get(spriteID)->Draw(x, y);
	}
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;

	//Sophia* sophia = ((BMScene*)CGame::GetInstance()->GetCurrentScene())->GetSophia();

	//float sophiaX, sophiaY;
	//sophia->GetPosition(sophiaX, sophiaY);
	//if (abs(bulletTempX - sophiaX) > 200) {
	//	Delete();
	//}
}

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
