#include "Paddle1.h"
#include "PongAssetsIDs.h"

void Paddle1::Render() {
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_PADDLE_1)->Draw(x, y);


	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	//DebugOutTitle(L"Cam: %d %d", cx, cy);
}
