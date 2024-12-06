#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"
#include "StaticMeshObject/Character/CCharacter.h"

/**************************************************
*	地面クラス.
**/
class CSky
	: public CStaticMeshObject
{
public:
	CSky();
	virtual ~CSky();

	//メッシュデータ設定
	void LoadData();
	//更新関数
	virtual void Update() override;
	//描画関数
	virtual void Draw() override;

protected:
};

