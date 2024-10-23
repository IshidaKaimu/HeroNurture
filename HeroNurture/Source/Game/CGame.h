#pragma once
#include "CDirectX9.h"
#include "CDirectX11.h"
#include "DebugText/CDebugText.h"
#include "Sprite3D/CSprite3D.h"
#include "Sprite2D/CSprite2D.h"
#include "SpriteObject/CSpriteObject.h"
#include "StaticMeshObject/Character/CCharacter.h"
#include "SkinMeshObject/Player/CPlayer.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "StaticMeshObject/Shot/CShot.h"
#include "UIObject/CUIObject.h"
#include "StaticMesh/CStaticMesh.h"
#include "StaticMeshObject/CStaticMeshObject.h"
#include "SkinMesh/CSkinMesh.h"
#include "SkinMeshObject/Zako/CZako.h"
#include "Ray/CRay.h"
#include "Camera/CCamera.h"
#include "Scene/Title/CSceneSelect.h"

#include <vector> //�ϒ��z��


/********************************************************************************
*	�Q�[���N���X.
**/
class CGame
{
public:
	static constexpr int ENEMY_MAX = 3;	//�G�l�~�[�̍ő吔.

	CGame( CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd );
	~CGame();

	void Create();
	HRESULT LoadData();
	void Release();

	void Update();
	void Draw();


private:
	CDirectX9*		m_pDx9;
	CDirectX11*		m_pDx11;

	CDebugText*		m_pDbgText;	//�f�o�b�O�e�L�X�g.

	//���C�\���N���X
	CRay*			m_pRayY;	//Y����(����)

	//�E�B���h�E�n���h��.
	HWND			m_hWnd;

	//�J�������.
	CCamera*		m_pCamera;
	//���C�g���.
	LIGHT			m_Light;

	//�s��.
	D3DXMATRIX		m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX		m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.

	//�Q�[���ň����X�v���C�g�f�[�^(�g���܂킷����).
	CSprite3D*		m_pSpriteGround;
	CSprite3D*		m_pSpritePlayer;
	CSprite3D*		m_pSpriteExplosion;

	//�X�v���C�g2D�f�[�^(�g���܂킷����).
	CSprite2D*		m_pSprite2DPmon;

	//�X�L�����b�V��(�g���܂킷����)
	int            m_ZakoAnimNo;			//�U�R:�A�j���[�V�����ԍ�
	double         m_ZakoAnimTime;			//�U�R:�A�j���[�V�����o�ߎ���
	D3DXVECTOR3    m_ZakoBonePos;			//�U�R:�{�[�����W

	//�X�^�e�B�b�N���b�V��(�g���܂킷����).
	CStaticMesh*	m_pStaticMeshFighter;	//���@.
	CStaticMesh*	m_pStaticMeshGround;	//�n��.
	CStaticMesh*	m_pStaticMeshBSphere;	//�o�E���f�B���O�X�t�B�A(�����蔻��p).

	//�X�v���C�g�I�u�W�F�N�g�N���X.
	CSpriteObject*		m_pExplosion;
	

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	CStaticMeshObject*	m_pStcMeshObj;

	//�L�����N�^�[�N���X.
	CCharacter*			m_pPlayer;
	CCharacter*			m_pEnemy;
	CCharacter*			m_pEnemies[ENEMY_MAX];
	CCharacter**		m_ppEnemies;
	int					m_EnemyMax;

	//�n�ʃN���X.
	CGround*			m_pGround;

	//�e�N���X.
	CShot*				m_pShot;

	//std::vector<�錾�������^��> �ϐ���
	std::vector<CZako*> m_Zako;

private:
	//=delete�u�폜��`�v�ƌĂ΂��@�\.
	//�w�肳�ꂽ�ꍇ�A���̊֐��͌Ăяo���Ȃ��Ȃ�.
	CGame() = delete;	//�f�t�H���g�R���X�g���N�^�֎~.
	CGame( const CGame& ) = delete;
	CGame& operator = (const CGame& rhs ) = delete;
};