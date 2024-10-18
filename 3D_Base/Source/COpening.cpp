#include "COpening.h"
#include "CSceneManager.h"
#include "CSkinMeshManager.h"
#include "CSoundManager.h"
#include "CMeshManager.h"
#include "WriteText.h"

COpening::COpening()
    : m_pKaito()
    , m_LookPointY( 1.0f )
    , m_CameraPosZ(4.0f)
    , m_pSky()
{
    Create();
    LoadData();
}

COpening::~COpening()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pKaito);
}

void COpening::Create()
{
    //�U�R�N���X
    m_pKaito = new CKaito();
    //�J�����N���X
    m_pCamera = new CCamera();
    //�X�J�C�{�b�N�X
    m_pSky = new CSky();
}

void COpening::LoadData()
{
    //�X�L�����b�V���}�l�[�W���N���X�̃C���X�^���X��ϐ��ɑ��
    CSkinMeshManager* SkMng = CSkinMeshManager::GetInstance();

    //�X�^�e�B�b�N���b�V���}�l�[�W���[�N���X�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* SMng = CMeshManager::GetInstance();
   
    //�J�C�g�Ƀ��b�V����ݒ�
    m_pKaito->AttachMesh(SkMng->GetMesh(CSkinMeshManager::Player));

    //�J�C�g�̏�����
    m_pKaito->OpInit();

    //�X�J�C�{�b�N�X�Ƀ��b�V����ݒ�
    m_pSky->AttachMesh(SMng->GetMesh(CMeshManager::Sky));

    //�J�������J�C�g�ɍ��킹��    
    Init();
}

void COpening::Init()
{
    CSceneManager* SMng = CSceneManager::GetInstance();
    D3DXVECTOR3 Kpos = m_pKaito->GetPosition();

    //���
    SMng->SetCameraPos(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0f, Kpos.z + 5.0f));
    SMng->SetCameraLook(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0, Kpos.z));
}

void COpening::Update()
{
    //BGM
    CSoundManager::PlayLoop(CSoundManager::BGM_Opening);
    CSoundManager::Volume(CSoundManager::BGM_Opening, 400);


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CSceneManager* SMng = CSceneManager::GetInstance();

    m_AnimCnt++;

    //�J�C�g�̃I�[�v�j���O�̃A�j���[�V����
    m_pKaito->OPAnim();

    D3DXVECTOR3 Kpos = m_pKaito->GetPosition();

    SMng->SetCameraLook(D3DXVECTOR3(Kpos));

    
    if (FadeIn()) {

        switch (m_Cut)
        {
        case COpening::Back:

            m_AnimCnt++;

            //���
            SMng->SetCameraPos(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0f, Kpos.z + 5.0f));
            SMng->SetCameraLook(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0, Kpos.z));

            if(m_AnimCnt >= 300)
            {
                m_AnimCnt = 0;
                m_Cut = Left;
            }

            break;
        case COpening::Left:

            m_AnimCnt++;

            //�����_
            SMng->SetCameraPos(D3DXVECTOR3(Kpos.x + 3.0, Kpos.y + 3.0f, Kpos.z));
            SMng->SetCameraLook(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0, Kpos.z));
            if (m_AnimCnt >= 300)
            {
                m_AnimCnt = 0;
                m_Cut = Right;
            }

            break;
        case COpening::Right:

            m_AnimCnt++;

            //�E���_
            SMng->SetCameraPos(D3DXVECTOR3(Kpos.x - 3.0f, Kpos.y + 3.0f, Kpos.z));
            SMng->SetCameraLook(D3DXVECTOR3(Kpos.x, Kpos.y + 3.0, Kpos.z));

            if (m_AnimCnt >= 300)
            {
                m_AnimCnt = 0;
                m_Cut = Center;
            }

            break;
        case COpening::Center:

            m_AnimCnt++;

            //����
            if (m_LookPointY < 3.0f)
            {
                m_LookPointY += 0.08f;
            }

            SMng->SetCameraPos(D3DXVECTOR3(m_pKaito->GetPosition().x, m_pKaito->GetPosition().y + 3.0f, m_pKaito->GetPosition().z - 4.0f));
            SMng->SetCameraLook(D3DXVECTOR3(m_pKaito->GetPosition().x, m_LookPointY, m_pKaito->GetPosition().z));

            if (m_AnimCnt >= 300)
            {
                m_AnimCnt = 0;
                m_Cut = CenterBack;
            }

            break;
        case COpening::CenterBack:

            m_AnimCnt++;

            //����
            if (m_CameraPosZ <= 10.0f)
            {
                m_CameraPosZ += 0.1f;
            }

            SMng->SetCameraPos(D3DXVECTOR3(m_pKaito->GetPosition().x, m_pKaito->GetPosition().y + 3.0f, m_pKaito->GetPosition().z - m_CameraPosZ));
            SMng->SetCameraLook(D3DXVECTOR3(m_pKaito->GetPosition().x, m_LookPointY, m_pKaito->GetPosition().z));

            if (m_CameraPosZ >= 10.0f)
            {
                m_AnimCnt = 0;
                m_Cut = Slash;
            }

            break;
        case COpening::Slash:

            m_pKaito->AnimChange();
            SMng->SetCameraPos(D3DXVECTOR3(m_pKaito->GetPosition().x, m_pKaito->GetPosition().y + 3.0f, m_pKaito->GetPosition().z - m_CameraPosZ));
            SMng->SetCameraLook(D3DXVECTOR3(m_pKaito->GetPosition().x, m_LookPointY, m_pKaito->GetPosition().z));

            break;
        default:
            break;
        }

        //�V�[���J��(��)
        if (m_pKaito->SceneChange() == true)
        {
            m_SceneTransitionFlg = true;    //�V�[���J�ڃt���O�L����
        }

        //�Z���N�g�V�[���ɖ߂�
        if (m_SceneTransitionFlg && FadeOut()) 
        {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
            //�J���������킹��
            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
            CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

        }
    }
}

void COpening::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{


    m_pSky->Draw(View, Proj, Light, Camera);

    m_pKaito->Draw(View, Proj, Light, Camera);

    //���ږ��̕\��
    WriteText::GetInstance()->Draw_Text(L"Opening", WriteText::Select, D3DXVECTOR2(0, 0));


}
