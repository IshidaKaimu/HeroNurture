#pragma once
#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "SkinMeshObject/Hero/CHeroBase.h"

/*****************************************
*カイトクラス
**/
class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadData( const json& jsondata ) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	//アニメーション関数
	void Animation() override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//場面切り替え
	bool SceneChange();

	//アニメーション切り替えフラグ立てる
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置

};

