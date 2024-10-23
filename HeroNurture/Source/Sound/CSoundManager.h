#pragma once
#include "CSound.h"		//�T�E���h�N���X.

/**************************************************
*	�T�E���h�}�l�[�W���[�N���X.
*	Manager(�}�l�[�W���[)�F�Ǘ���.
*		Singleton(�V���O���g���F�f�U�C���p�^�[���̂P��)�ō쐬.
**/
class CSoundManager
{
public:
	//�T�E���h���X�g�񋓌^.
	enum enList
	{
		BGM_Opening,	//�I�[�v�j���O�V�[��.
		BGM_BossApe,	//�{�X�o��V�[��.
		BGM_BossEvo,	//�{�X�i���V�[��.
		BGM_Special,	//�K�E�Z�V�[��.
		BGM_BossDeath,	//�{�X���j�V�[��.
		
		SE_Slash,		//�a��.
		SE_Root,	    //�K�E�̋O��.
		SE_Sp,			//�K�E������
		SE_Charge,	    //�K�E������
		SE_EvoNow,		//�{�X�ϐg��
		SE_EvoAf,		//�ϐg��J�����̓���
		SE_BossVo,		//�{�X�̐�
		SE_BossDeath,	//�{�X���S
		SE_DeathNow,	//���S���t�F�[�h
		SE_BossLoss,	//�{�X����
		SE_BeforeDeath,	//�{�X�����O
		
		

		//������������u�����v�ɒǉ����Ă�������.
		max,		//�ő吔.
	};

public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static CSoundManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CSoundManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}


	~CSoundManager();

	//�T�E���h�f�[�^�Ǎ��֐�.
	bool Load( HWND hWnd );
	//�T�E���h�f�[�^����֐�.
	void Release();

	//SE���Đ�����.
	static void PlaySE( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlaySE();
	}
	//���[�v�Đ�����.
	static void PlayLoop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();
	}
	//��~����.
	static void Stop( enList list ) {
		CSoundManager::GetInstance()->m_pSound[list]->Stop();
	}

	//���ʂ̑���
	static void Volume(enList list,int volume) {
		CSoundManager::GetInstance()->m_pSound[list]->SetVolume(volume);
	}


private://�O������A�N�Z�X�s�\.
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CSoundManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CSoundManager( const CSoundManager& rhs ) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CSoundManager& operator = ( const CSoundManager& rhs ) = delete;

private:
	CSound*		m_pSound[enList::max];
};