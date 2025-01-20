#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// �O���錾
//=====================================
//�q�[���[�}�l�[�W���[
class CHeroManager;
//�G�̃q�[���[�}�l�[�W���[
class CEnemyHeroManager;
//�J�����}�l�[�W���[
class CCameraManager;

//=====================================
// �萔�錾(_U = �ŗL�U���V�[���ŗp���邱�Ƃ�����)
//=====================================
//----�J�������----
//���C�̌ŗL�U���V�[��
const D3DXVECTOR3 YUI_CAMPOS  = { -1.0f,2.0f,-7.0f }; //�������W
const D3DXVECTOR3 YUI_CAMLOOK = { -1.0f,2.0f,0.0f };  //���������_
//�J�C�g�̌ŗL�U���V�[��
const D3DXVECTOR3 KAITO_CAMPOS  = { -1.0f,2.0f,-7.0f }; //�������W
const D3DXVECTOR3 KAITO_CAMLOOK = { -1.0f,2.0f,0.0f };  //���������_


class CUniqueAttack
	: public CSceneBase
{
public:
	CUniqueAttack();
	~CUniqueAttack();

	//�\�z�֐�
	void Create()	  override;
	//�j���֐�
	void Releace()	  override;
	//�f�[�^�ݒ�֐�
	void LoadData()	  override;
	//�������֐�
	void Initialize() override;
	//�X�V�֐�
	void Update()     override;
	//�`��֐�
	void Draw()		  override;
	//�f�o�b�O�p�֐�
	void Debug();

private:
	//���ꂼ��̃q�[���[�̌ŗL�U���A�j���[�V�����ɗp����J�������[�N
	void YuiCameraWork();  //���C
	void KaitoCameraWork();//�J�C�g


private:
	//�q�[���[�}�l�[�W���[
	CHeroManager* m_pHero;
	//�G�̃q�[���[�}�l�[�W���[
	CEnemyHeroManager* m_pEnemyHero;
	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;
};
