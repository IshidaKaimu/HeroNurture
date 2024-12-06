#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"

//----前方宣言----
class CSceneManager;

//=====================================
//ユイクラス
//制作者：石田櫂夢
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
	virtual ~CYui()	override;

	//初期化関数
	void Initialize() override;

	//データ読み込み関数
	void LoadMeshData() override;

	//パラメータ情報読み込み
    void LoadParamData(const json& jsondata) override;

	//更新関数
	void Update() override;

	//描画関数
	void Draw() override;

	// =======================
	// 各シーンごとのアニメーション
	// =======================
	//ヒーロー選択シーン 
	void SelectAnimation() override;
	// 育成シーン		
	void NatureAnimation(int no) override;

private:
	//アニメーションスピードの設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//アニメーション切り替えフラグ立てる
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置

};

