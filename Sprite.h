#pragma once

#include "Texture.h"
#include "Game.h"

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;

	int spriteHeight;
	int spriteWidth;
public:

	CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex);

	void Draw(float x, float y);

	int getHeight() { return spriteHeight; }
	void getSize(int& height, int& width) { height = spriteHeight; width = spriteWidth; }
};

typedef CSprite* LPSPRITE;