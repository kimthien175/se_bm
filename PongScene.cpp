#include "PongScene.h"
#include "PongKeyHandler.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"
#include "PongAssetsIDs.h"
#include "Paddle0.h"
#include "Paddle1.h"
#include "Ball.h"
#include <fstream>

void PongScene::_ParseSection_SPRITES(string line) {
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

void PongScene::_ParseSection_ANIMATIONS(string line) {
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

void PongScene::_ParseSection_ASSETS(string line) {
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void PongScene::_ParseSection_OBJECTS(string line) {
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	switch (object_type) {
		case OBJECT_TYPE_PADDLE_0:		paddle0 = new Paddle0(x, y); break;
		case OBJECT_TYPE_PADDLE_1: 	paddle1 = new Paddle1(x, y); break;
		case OBJECT_TYPE_BALL:				ball = new Ball(x, y); break;
		default:
			DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
			return;
	}
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void PongScene::LoadAssets(LPCWSTR assetFile) {
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE)) {
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
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

PongScene::PongScene(int id, LPCWSTR filePath) :CScene(id, filePath) {
	ball = NULL;
	paddle0 = NULL;
	paddle1 = NULL;
	key_handler = new PongKeyHandler(this);
}

void PongScene::Load() {
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
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section) {
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void PongScene::Update(DWORD dt) {
	paddle0->Update(dt);
	paddle1->Update(dt);

	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(paddle0);
	coObjects.push_back(paddle1);

	ball->Update(dt, &coObjects);

	CGame::GetInstance()->SetCamPos(0,0);

	PurgeDeletedObjects();
}

void PongScene::Render() {
	// Render background



	paddle0->Render();
	paddle1->Render();
	ball->Render();
}

void PongScene::Unload() {
	// use when ?
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void PongScene::Clear() {
	delete paddle0;
	delete paddle1;
	delete ball;
	paddle0 = NULL;
	paddle1 = NULL;
	ball = NULL;
}

void PongScene::PurgeDeletedObjects() {
	if (paddle0->IsDeleted()) {
		delete paddle0;
		paddle0 = NULL;
	}

	if (paddle1->IsDeleted()) {
		delete paddle1;
		paddle1 = NULL;
	}

	if (ball->IsDeleted()) {
		delete ball;
		ball = NULL;
	}

}

bool PongScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) {
	return o == NULL;
}
