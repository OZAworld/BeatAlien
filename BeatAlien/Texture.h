/*
*	�e�N�X�`��
*
*	2015/05/05		Y.Ozawa
*/

#pragma once

//�e�N�X�`��
class Texture
{
public:

	LPDIRECT3DTEXTURE9 texture;

public:

	//�f�t�H���g�R���X�g���N�^
	Texture();

	//�R���X�g���N�^
	Texture(const TCHAR *textureFileName);

	//�f�X�g���N�^
	~Texture();

	//���b�V�������[�h����
	bool LoadTexture(const TCHAR *textureFileName);

};