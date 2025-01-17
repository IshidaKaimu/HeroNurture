#pragma once
#include "Singleton\CSingleton.h"
#include "Camera\CCamera.h"
#include <memory>

//=====================================
// �J�����}�l�[�W���[�N���X
//=====================================

class CCameraManager
	: public CCamera
	, public CSingleton<CCameraManager>
{
public:
	//�t�����h�錾
	friend class CSingleton<CCameraManager>;

public:

	~CCameraManager();

	//�J�����̍X�V
	void CameraUpdate();

	//�J�������̎擾
	CAMERA GetCamera() { return GetInstance().m_pCamera.get()->GetCamera(); }

	// =======================
	// �Q�b�^�[�E�Z�b�^�[�֐�
	// =======================
	//���W
	D3DXVECTOR3 GetPos() { return m_pCamera->GetPos(); }
	void SetPos( D3DXVECTOR3 pos ) { m_pCamera->SetPos(pos); }
	void SetPos( float x, float y, float z ) { m_pCamera->SetPos(x,y,z); }
	void SetPosX( float x ) { m_pCamera->SetPosX(x); }
	void SetPosY( float y ) { m_pCamera->SetPosY(y); }
	void SetPosZ( float z ) { m_pCamera->SetPosZ(z); }
	//�����_
	D3DXVECTOR3 GetLook() { return m_pCamera->GetLook(); }
	void SetLook(D3DXVECTOR3 look) { m_pCamera->SetLook(look); }
	void SetLook(float x, float y, float z) { m_pCamera->SetLook (x, y, z); }
	void SetLookX(float x) { m_pCamera->SetLookX(x); }
	void SetLookY(float y) { m_pCamera->SetLookY(y); }
	void SetLookZ(float z) { m_pCamera->SetLookZ(z); }

private:
	//�A�N�Z�X����邱�Ƃ��Ȃ��悤��private
	CCameraManager();

private:
	//�J�����N���X
	std::unique_ptr<CCamera> m_pCamera;

};
