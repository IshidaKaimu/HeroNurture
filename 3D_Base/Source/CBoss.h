#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float BOSS_SPEED = 0.05f;

/*****************************************
* ボスクラス
**/
class CBoss
	:public CSkinMeshObject
{
public:
	CBoss();
	virtual ~CBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	//アニメーション速度の設定
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void AnimChange();		   //アニメーション切り替えフラグ　※進化シーンで使う
							   
	void EvoAnim();			   //進化シーンでのアニメーション
							   
	void SpAnim();			   //必殺技シーンでのアニメーション
							   
	void DeathAnim();		   //死亡シーンでのアニメーション
							   
	bool SceneChange();		   //シーンをシーンセレクトに戻す条件
							   
	void EvoInit();			   //進化シーンでの初期化
							   
	void SpInit();			   //必殺技シーンでの初期化
							   
	void DeathInit();		   //死亡シーンでの初期化
							   
	void Death();			   //爆発エフェクト再生開始
							   
	bool AfterDeath();		   //死亡後

	void AnimNoChange(int no); //アニメーション番号切り替え

	bool BossFell();		   //ボスが倒れ切っているかの判断


protected:
	D3DXVECTOR3    m_BonePos;			//ボス:ボーン座標
	
	bool           m_AnimChange;		//アニメーション切り替えフラグ

	float          m_EffPosZ;			//エフェクトのZ軸位置
	int            m_EffCnt;			//エフェクトの時間
	bool           m_EffStart;			//エフェクトスタートフラグ

	int            m_DeathCnt;			//死亡時間
	bool           m_Death;				//爆発エフェクト再生フラグ

	int            m_BossRadianX;        //ボスのX軸回転変動用
	int            m_RotateCnt;			 //徐々に倒していくためのカウント	

	bool           m_Fell;				 //ボスが倒れ切ったフラグ
	int            m_FellCnt;			 //倒れ切った後からのカウント
};

