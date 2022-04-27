#pragma once
#include "Textures.h"
class BMMap {
	LPTEXTURE tex;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	BMMap(int tex_id);
	void Draw();

	~BMMap();
};

