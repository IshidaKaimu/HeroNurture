#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"
#include "StaticMeshObject/Character/CCharacter.h"

//=====================================
// 地面クラス
// 制作者:石田櫂夢
//=====================================
class CGround
	: public CStaticMeshObject
{
public:
	CGround();
	virtual ~CGround();

	virtual void LoadData();

	virtual void Update() override;

	virtual void Draw() override;

	//プレイヤーを設定
	void SetPlayer(CCharacter& pPlayer) { m_pPlayer = &pPlayer; }

protected:
	CCharacter* m_pPlayer;

};

