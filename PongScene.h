#pragma once
#include "Scene.h"
#include "Collision.h"
#include <string>

class PongScene : public CScene {
protected:
	LPGAMEOBJECT ball;

	LPGAMEOBJECT paddle0;
	LPGAMEOBJECT paddle1;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	PongScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetBall() { return ball; }
	LPGAMEOBJECT GetPaddle0() { return paddle0; }
	LPGAMEOBJECT GetPaddle1() { return paddle1; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

