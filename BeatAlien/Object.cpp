/*
*	オブジェクトの設定
*
*	2015/05/05		Y.Ozawa
*/

#include "include.h"

#define VERTEX3_FVF (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)


//Direct3Dデバイス
extern LPDIRECT3DDEVICE9 d3dDevice;

//デフォルトコンストラクタ
Object::Object()
{
	// ポイントスプライトのバッファの初期化
	if (FAILED(d3dDevice->CreateVertexBuffer(10000 * sizeof(Vertex3), D3DUSAGE_WRITEONLY, VERTEX3_FVF, D3DPOOL_MANAGED, &pointBuffer, nullptr)))
		DebugAlert("頂点バッファが\n作成できませんでした。");

	// フォントの初期化
	D3DXCreateFont(d3dDevice,
		32,							// 文字の高さ
		16,							// フォントの文字の幅
		FW_NORMAL,					// フォントのウェイト
		0,							// 要求されるミップレベルの数
		false,						// 斜体フォントの場合はtrue
		0,							// 文字セット
		0,							//出力精度
		DEFAULT_QUALITY,			//出力品質
		DEFAULT_PITCH || FF_DONTCARE,	//フォントのピッチとファミリ
		"",							//フォントの書体
		&font);


	DebugLog("オブジェクトを生成しました\n");

	Initialize();
}

//デストラクタ
Object::~Object()
{
	DebugLog("オブジェクトを解放しました\n");

	Release();
}

//オブジェクトの初期化
void Object::Initialize()
{
	Object::position = D3DXVECTOR3(0, 0, 0);
	Object::rotation = D3DXVECTOR3(0, 0, 0);
	Object::scale = D3DXVECTOR3(1, 1, 1);

	D3DXMatrixIdentity(&m_world);

	DebugLog("オブジェクトを初期化しました\n");
}

//オブジェクトの解放
void Object::Release()
{

}

//オブジェクトを描画する
void Object::Draw(Model* model, Texture* texture)
{
	//ワールド行列の設定
	TransForm();
	d3dDevice->SetTransform(D3DTS_WORLD, &m_world);

	//モデルの描画
	D3DXMATERIAL *materials = (D3DXMATERIAL *)model->buffer->GetBufferPointer();
	for (DWORD i = 0; i < model->numMaterial; i++)
	{
		//マテリアルの設定
		d3dDevice->SetMaterial(&materials[i].MatD3D);

		d3dDevice->SetTexture(0, texture->texture);

		//分割されたメッシュの描画
		model->mesh->DrawSubset(i);
	}
}

// ポイントスプライトを描画する
void Object::DrawPointSprite(Vertex3 point[], int numPoint, Texture &texture)
{
	Vertex3 *vertex;

	pointBuffer->Lock(0, 0, (LPVOID*)&vertex, 0);
	for (int i = 0; i < numPoint; i++)
	{
		// ポイントスプライトの位置の計算
		vertex[i].pos = point[i].pos;

		// ポイントスプライトのサイズを設定
		vertex[i].size = point[i].size;

		// ポイントスプライトの色を設定
		vertex[i].color = point[i].color;
	}
	pointBuffer->Unlock();

	// テクスチャをパイプラインにセット
	d3dDevice->SetTexture(0, texture.texture);

	// ワールド変換マトリックスをパイプラインにセット
	D3DXMATRIX m_world;
	D3DXMatrixIdentity(&m_world);
	d3dDevice->SetTransform(D3DTS_WORLD, &m_world);

	
	//アルファブレンディングを行う
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ポイントスプライトの描画
	d3dDevice->SetRenderState(D3DRS_ZENABLE, true);	// Z比較を行わない
	d3dDevice->SetStreamSource(0, pointBuffer, 0, sizeof(Vertex3));
	d3dDevice->SetFVF(VERTEX3_FVF);
	d3dDevice->DrawPrimitive(D3DPT_POINTLIST, 0, numPoint);
	d3dDevice->SetRenderState(D3DRS_ZENABLE, true);		// Z比較を行う

	//アルファブレンドを終わらせる
	d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

// 文字列の描画
void Object::DrawString(RECT rect, const TCHAR *str)
{
	font->DrawText(nullptr,
		str,
		-1,
		&rect,
		DT_CENTER | DT_VCENTER | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 255));
}


//座標変換
void Object::TransForm()
{
	D3DXMATRIX m_temp;
	D3DXMatrixIdentity(&m_world);
	D3DXMatrixIdentity(&m_temp);

	//行列を拡大縮小
	D3DXMatrixScaling(&m_temp, scale.x, scale.y, scale.z);
	m_world *= m_temp;

	//行列を拡大縮小する
	D3DXMatrixRotationYawPitchRoll(&m_temp, rotation.y, rotation.x, rotation.z);
	m_world *= m_temp;

	//行列を平行移動する
	D3DXMatrixTranslation(&m_temp, position.x, position.y, position.z);
	m_world *= m_temp;
}


