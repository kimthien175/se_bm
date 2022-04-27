#include "BMMap.h"
#include "BMAssetsIDs.h"
#include "Game.h"

BMMap::BMMap(int tex_id) {
	tex = CTextures::GetInstance()->Get(tex_id);

	float texWidth = (float)tex->getWidth();
	float texHeight = (float)tex->getHeight();

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = 0;
	sprite.TexCoord.y = 0;

	int spriteWidth = tex->getWidth();
	int spriteHeight = tex->getHeight();

	sprite.TexSize.x = 1;
	sprite.TexSize.y = 1;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0);
}

void BMMap::Draw() {
	CGame* g = CGame::GetInstance();
	float cx, cy;
	g->GetCamPos(cx, cy);

	D3DXMATRIX matTranslation;

	D3DXMatrixTranslation(&matTranslation, ((FLOAT)(tex->getWidth())) / 2.0 -cx, ((FLOAT)(tex->getHeight()))  / 2.0 -cy, 0.1);

	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

BMMap::~BMMap() {
	if (tex) delete tex;
}
