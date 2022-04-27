#pragma once
#include "Scene.h"

class BMKeyHandler : public CSceneKeyHandler {
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	BMKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};

