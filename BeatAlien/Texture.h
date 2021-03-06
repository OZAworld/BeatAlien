/*
*	テクスチャ
*
*	2015/05/05		Y.Ozawa
*/

#pragma once

//テクスチャ
class Texture
{
public:

	LPDIRECT3DTEXTURE9 texture;

public:

	//デフォルトコンストラクタ
	Texture();

	//コンストラクタ
	Texture(const TCHAR *textureFileName);

	//デストラクタ
	~Texture();

	//メッシュをロードする
	bool LoadTexture(const TCHAR *textureFileName);

};
