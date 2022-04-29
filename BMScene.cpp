#include "BMScene.h"
#include "Sprites.h"
#include "Textures.h"
#include "Debug.h"
#include "Utils.h"
#include "Animations.h"
#include <fstream>
#include "BMKeyHandler.h"
#include "BMAssetsIDs.h"

void BMScene::_ParseSection_SPRITES(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL) {
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void BMScene::_ParseSection_ANIMATIONS(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void BMScene::_ParseSection_ASSETS(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void BMScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	switch (object_type) {
		case OBJECT_TYPE_JASON: sophia = new Sophia(x, y);
		default:
			DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
			return;
	}


}

void BMScene::_ParseSection_Map(string line) {
	int map_tex_id = atoi(line.c_str());
	map = new BMMap(map_tex_id);
}

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_MAP					0
#define SCENE_SECTION_ASSETS			1
#define SCENE_SECTION_OBJECTS			2
#define SCENE_SECTION_ANIMATIONS	3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void BMScene::LoadAssets(LPCWSTR assetFile) {
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { 
			section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section) {
			case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

BMScene::BMScene(int id, LPCWSTR filePath):CScene(id, filePath) {
	key_handler = new BMKeyHandler(this);
	sophia = NULL;
}

void BMScene::Load() {
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section) {
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_Map(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void BMScene::Update(DWORD dt) {
	//paddle0->Update(dt);
	//paddle1->Update(dt);

	//vector<LPGAMEOBJECT> coObjects;
	//coObjects.push_back(paddle0);
	//coObjects.push_back(paddle1);

	sophia->Update(dt);

	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->IsDeleted())
			objects[i]->Update(dt);
	}

	CGame::GetInstance()->SetCamPos(0, 0);

	PurgeDeletedObjects();
}

void BMScene::Render() {
	// render map
	map->Draw();

	// render game obj
	sophia->Render();

	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->IsDeleted())
			objects[i]->Render();
	}

	//float x, y;
	//sophia->GetPosition(x, y);
	//Bullet* bullet = new Bullet(x, y, 1, 0);
	//


	//CGame* g = CGame::GetInstance();
	//float cx, cy;
	//g->GetCamPos(cx, cy);

	//cx = (FLOAT)floor(cx);
	//cy = (FLOAT)floor(cy);

	//D3DXMATRIX matTranslation;

	//D3DXMatrixTranslation(&matTranslation, 0 - cx, g->GetBackBufferHeight() - 0 + cy, 0.1f);

	//this->sprite.matWorld = (this->matScaling * matTranslation);

	//g->GetSpriteHandler()->DrawSpritesImmediate(sprite->, 1, 0, 0);

	// render objects
}

void BMScene::Unload() {
	if (map) delete map;
	if (sophia) delete sophia;

	PurgeDeletedObjects();
}

//void BMScene::Clear() {}

void BMScene::PurgeDeletedObjects() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->IsDeleted()) {
			delete objects[i];
			objects[i] = NULL;
		}
	}
}

//bool BMScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) {
//	return o->IsDeleted();
//}