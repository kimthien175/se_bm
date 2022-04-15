#pragma once
#include "Scene.h"

class PongKeyHandler : public CSceneKeyHandler {
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PongKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};