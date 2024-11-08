#pragma once
#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "SkinMeshObject/Hero/CHero.h"

constexpr float KAITO_SPEED = 0.05f;

/*****************************************
*カイトクラス
**/
class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	virtual void Update() override;
	virtual void Draw( LIGHT& Light ) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//場面切り替え
	bool SceneChange();

	//アニメーション切り替えフラグ立てる
	void AnimChange();

	//オープニングシーンでの初期化
	void OpInit();

	//オープニングシーンでのアニメーション
	void OPAnim();

	//必殺技シーンでの初期化
	void SpInit();
	
	//必殺技シーンでのアニメーション
	void SpAnim();

	//白フェード開始フラグ立てる
	bool WhiteStart();

	//走り出すフラグを立てる
	void Run( bool run);

	//待機モーションへ
	void Wait();

	//アニメーション番号切り替え
	void AnimNoChange(int no);

	//アニメーションが終わったら
	bool EndAnim(int no);

	//構え完了
	bool Setup();

	//魔法陣召喚
	void Magic(bool magic);

	//斬撃モーション再開
	void Slash();

	//軌道エフェクト開始
	void Root();

protected:
	D3DXVECTOR3    m_BonePos;			//カイト:ボーン座標
	bool           m_Run;				//走り出すフラグ
	bool           m_AnimChange;		//アニメーション切り替えフラグ
	float          m_EffPosZ;			//エフェクトのZ軸位置

	//エフェクト関連のカウント
	int            m_EffCnt;			//パワーアップエフェクトのカウント
	int            m_MagicCnt;			//魔法陣エフェクトのカウント
	int            m_SlashCnt;			//斬撃エフェクトのカウント
	int            m_RootCnt;			//軌道エフェクトのカウント

	//フラグ
	bool           m_White;				//白フェード

	//エフェクト関連のフラグ
	bool		   m_Magic;				//風魔法フラグ
	bool           m_Setup;				//構え完了フラグ
	bool		   m_Slash;				//斬撃フラグ
	bool           m_Root;				//軌道フラグ

};

