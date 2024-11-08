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

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );

	//�J�������̎擾
	CAMERA camera = CCameraManager::GetInstance().GetCamera();

	//�����_�����O.
	m_pSprite->Render( camera.View, camera.Proj );
}
