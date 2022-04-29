#pragma once
#include "Scene.h"
#include "Collision.h"
#include <string>
#include "Sophia.h"
#include "Bullet.h"

class BMScene : public CScene {
protected:
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_Map(string line);

	void LoadAssets(LPCWSTR assetFile);

	Sophia* sophia;

	vector<LPGAMEOBJECT> objects;

public:
	BMScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	//void Clear();
	void PurgeDeletedObjects();

	//static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	Sophia* GetSophia() { return sophia; }

	void AddObject(LPGAMEOBJECT object) { 
		objects.push_back(object);
	}
};

