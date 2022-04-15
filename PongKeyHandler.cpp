#include "PongKeyHandler.h"
#include "Game.h"
#include "PongScene.h"
#include "Paddle0.h"
#include "Paddle1.h"

void PongKeyHandler::KeyState(BYTE* states) {
	CGame* game = CGame::GetInstance();
	Paddle0* paddle0 = (Paddle0*)((PongScene*)(game->GetCurrentScene()))->GetPaddle0();
	Paddle1* paddle1 = (Paddle1*)((PongScene*)(game->GetCurrentScene()))->GetPaddle1();

	if (game->IsKeyDown(DIK_W)) {
		// move paddle down
		paddle0->SetState(PADDLE_STATE_MOVE_UP);
	}
	else if (game->IsKeyDown(DIK_S)) {
		// move paddle up
		paddle0->SetState(PADDLE_STATE_MOVE_DOWN);
	}

	if (game->IsKeyDown(DIK_DOWN)) {
		// move paddle down
		paddle1->SetState(PADDLE_STATE_MOVE_DOWN);
	}
	else if (game->IsKeyDown(DIK_UP)) {
		// move paddle up
		paddle1->SetState(PADDLE_STATE_MOVE_UP);
	}

}

void PongKeyHandler::OnKeyDown(int KeyCode) {}

void PongKeyHandler::OnKeyUp(int KeyCode) {
	CGame* game = CGame::GetInstance();
	Paddle0* paddle0 = (Paddle0*)((PongScene*)(game->GetCurrentScene()))->GetPaddle0();
	Paddle1* paddle1 = (Paddle1*)((PongScene*)(game->GetCurrentScene()))->GetPaddle1();

	switch (KeyCode) {
		case DIK_W:
			paddle0->SetState(PADDLE_STATE_STAND_STILL);
			break;
		case DIK_S:
			paddle0->SetState(PADDLE_STATE_STAND_STILL);
			break;
		case DIK_UP:
			paddle1->SetState(PADDLE_STATE_STAND_STILL);
			break;
		case DIK_DOWN:
			paddle1->SetState(PADDLE_STATE_STAND_STILL);
			break;
	}



	
}
