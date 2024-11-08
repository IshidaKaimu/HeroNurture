#include "CSpriteObject.h"
#include "Camera\CameraManager\CCameraManager.h"

CSpriteObject::CSpriteObject()
	: m_pSprite		( nullptr )
{
}

CSpriteObject::~CSpriteObject()
{
	DetachSprite();
}

void CSpriteObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

void CSpriteObject::Draw()
{
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );

	//カメラ情報の取得
	CAMERA camera = CCameraManager::GetInstance().GetCamera();

	//レンダリング.
	m_pSprite->Render( camera.View, camera.Proj );
}
