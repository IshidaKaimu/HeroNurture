#include "CHeroManager.h"

CHeroManager::CHeroManager()
    :m_Hero ()
{
    m_Hero = std::make_unique<CHeroBase>();
}

CHeroManager::~CHeroManager()
{
}

//�������֐�
void CHeroManager::Initialize()
{
    //�e�q�[���[�N���X�̏�����
    m_Hero->Initialize();
}

//�f�[�^�ǂݍ��݊֐�
void CHeroManager::LoadData()
{
    //�e�q�[���[�N���X�̃f�[�^�ǂݍ���
    m_Hero->LoadData();
}

//�X�V�֐�
void CHeroManager::Update()
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Update();
}

//�`��֐�
void CHeroManager::Draw( LIGHT& light )
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Draw( light );
}

//�A�j���[�V�����֐�
void CHeroManager::Animation()
{
    m_Hero->Animation();
}
