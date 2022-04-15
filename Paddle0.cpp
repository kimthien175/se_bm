#include "Paddle0.h"
#include "PongAssetsIDs.h"

void Paddle0::Render() {
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_PADDLE_0)->Draw(x, y);


	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	//DebugOutTitle(L"Cam: %d %d", cx, cy);

}
