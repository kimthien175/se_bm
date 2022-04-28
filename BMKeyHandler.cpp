#include "BMKeyHandler.h"
#include "Game.h"
#include "BMScene.h"

void BMKeyHandler::KeyState(BYTE* states) {
	CGame* game = CGame::GetInstance();
	Sophia* sophia = ((BMScene*)game->GetCurrentScene())->GetSophia();

	if (game->IsKeyDown(DIK_RIGHT)) {
		sophia->SetState(SOPHIA_STATE_ACCELERATE_RIGHT);

		if (sophia->isLookingLeft() && !sophia->isRotating()) sophia->SetRotation();
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		sophia->SetState(SOPHIA_STATE_ACCELERATE_LEFT);

		if (!sophia->isLookingLeft() && !sophia->isRotating()) sophia->SetRotation();
	}

	if (game->IsKeyDown(DIK_UP)) {
		sophia->AcceleratePointingUp();
	}

	if (game->IsKeyDown(DIK_SPACE)) {
		if (!sophia->isJumping()) 
			sophia->SetJump();
	}
}

void BMKeyHandler::OnKeyDown(int KeyCode) {}

void BMKeyHandler::OnKeyUp(int KeyCode) {
	CGame* game = CGame::GetInstance();
	Sophia* sophia = ((BMScene*)game->GetCurrentScene())->GetSophia();

	switch (KeyCode) {
		case DIK_RIGHT:
			if (sophia->isMovingRight()) sophia->SetState(SOPHIA_STATE_STOP_ACCELERATING);
			break;
		case DIK_LEFT:
			if (sophia->isMovingLeft()) sophia->SetState(SOPHIA_STATE_STOP_ACCELERATING);
			break;
		case DIK_UP:
			sophia->RelasePointingUp();
			break;
	}
}
