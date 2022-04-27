#pragma once
#include "Scene.h"
#include "Collision.h"
#include <string>
#include "Sophia.h"

class BMScene : public CScene {
protected:
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_Map(string line);

	void LoadAssets(LPCWSTR assetFile);

	Sophia* sophia;

public:
	BMScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	//LPGAMEOBJECT GetBall() { return ball; }
	//LPGAMEOBJECT GetPaddle0() { return paddle0; }
	//LPGAMEOBJECT GetPaddle1() { return paddle1; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	Sophia* GetSophia() { return sophia; }
};

