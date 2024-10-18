#include "CBossEvolution.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CSkinMeshManager.h" 
#include "CEffect.h"
#include "CUIManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"

CBossEvolution::CBossEvolution()
    :m_pBeEvoBoss()
    ,m_pBoss     ()
    ,m_pWhiteFade()
    ,m_pSky      ()
    ,m_CameraPosZ(3.0f)
    ,m_CameraPosY()
    ,m_Alpha     (0.0)
    ,m_EndChange ()
    ,m_CameraChange()
{
    Create();
    LoadData();
}

CBossEvolution::~CBossEvolution()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pWhiteFade);
    SAFE_DELETE(m_pBoss);
    SAFE_DELETE(m_pBeEvoBoss);
}

void CBossEvolution::Create()
{
    m_pBeEvoBoss = new CBeEvoBoss();
    m_pBoss     = new CBoss();
    m_pWhiteFade = new CUIObject();
    m_pSky = new CSky();
}

void CBossEvolution::LoadData()
{
    //�X�L�����b�V���}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CSkinMeshManager* SkMng = CSkinMeshManager::GetInstance();
    //UI�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CUIManager* UiMng = CUIManager::GetInstance();
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();



    //�ϐg�O�{�X�Ƀ��b�V����ݒ�
    m_pBeEvoBoss->AttachMesh(SkMng->GetMesh(CSkinMeshManager::FastBoss));
    
    //�ϐg��{�X
    m_pBoss->AttachMesh(SkMng->GetMesh(CSkinMeshManager::Boss));
    m_pBoss->EvoInit();

    D3DXVECTOR3 BeBPos = m_pBeEvoBoss->GetPosition();

    //���t�F�[�h
    m_pWhiteFade->AttachSprite(UiMng->GetSprite(CUIManager::WhiteFade));
    m_pWhiteFade->SetAlpha(m_Alpha);

    //�X�J�C�{�b�N�X
    m_pSky->AttachMesh(MMng->GetMesh(CMeshManager::Sky));


    CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BeBPos.x, BeBPos.y + 3.0f, BeBPos.z - m_CameraPosZ));
    CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BeBPos.x, BeBPos.y + 3.0f, BeBPos.z));
}

void CBossEvolution::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();


    D3DXVECTOR3 BeBPos = m_pBeEvoBoss->GetPosition();
    D3DXVECTOR3 BPos   = m_pBoss->GetPosition();
    
    //�T�E���h�}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CSoundManager* SMng = CSoundManager::GetInstance();

    //�i���O�{�X�̃A�j���[�V����
    m_pBeEvoBoss->EvoAnim();

    //�i����{�X�̃A�j���[�V����
    m_pBoss->EvoAnim();

    //���t�F�[�h�̃��l�ݒ�
    m_pWhiteFade->SetAlpha(m_Alpha);

    //�{�X�i��
    CSoundManager::PlayLoop(CSoundManager::BGM_BossEvo);
    CSoundManager::Volume(CSoundManager::BGM_BossEvo, 300);


    switch (m_Cut)
    {
    case CBossEvolution::ZoomOut:

        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BeBPos.x, BeBPos.y + 3.0f, BeBPos.z - m_CameraPosZ));

        //�{�X���痣���
        if (m_CameraPosZ <= 8.0)
        {
            m_CameraPosZ += 0.1;
            SMng->PlaySE(CSoundManager::SE_EvoNow);
            SMng->Volume(CSoundManager::SE_EvoNow, 300);
            m_pBeEvoBoss->EffStart();
        }
        else
        {

            for (int i = 0; i < 240; i++)
            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BeBPos.x , BeBPos.y + 3.0f, BeBPos.z - m_CameraPosZ));
            m_AnimCnt++;


        }

        //�G�t�F�N�g���n�܂��Đ��b��Ɏ��̏�ʂ�
        if (m_AnimCnt >= 240)
        {
            m_Cut = Change;
            m_AnimCnt = 0.0f;
            m_CameraPosZ = 0.0f;

        }
        break;
    case CBossEvolution::Change:
        PlayWhiteFade();

        break;
    case CBossEvolution::Evolution:
        PlayWhiteFade();
        switch (m_CameraWork)
        {
        case CBossEvolution::Fast:


            if (m_EndChange = true)
            {
                if (m_CameraPosY <= 5.0f)
                {
                    m_CameraPosY += 0.08;
                }

                CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BPos.x + 3.0, BPos.y + m_CameraPosY, BPos.z - 4.0));
                CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BPos.x, BPos.y + m_CameraPosY, BPos.z));

                if (m_CameraPosY >= 5.0f)
                {
                    m_AnimCnt++;
                    if (m_AnimCnt >= 60)
                    {
                        m_CameraWork = Second;
                        m_AnimCnt = 0.0;
                        m_CameraPosY = 0.0f;
                    }
                }
            }
            break;
        case CBossEvolution::Second:

            if (m_CameraPosY <= 5.0f)
            {
                m_CameraPosY += 0.08;
            }

            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BPos.x - 3.0, BPos.y + m_CameraPosY, BPos.z - 4.0));
            CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BPos.x, BPos.y + m_CameraPosY, BPos.z));

            if (m_CameraPosY >= 5.0f)
            {
                m_AnimCnt++;

                if (m_AnimCnt >= 60)
                {
                    m_CameraWork = Third;
                    m_AnimCnt = 0.0;
                    m_CameraPosY = 0.0f;

                }
            }

            break;
        case CBossEvolution::Third:

            if (m_CameraPosY <= 6.0f)
            {
                m_CameraPosY += 0.08;
            }

            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BPos.x, BPos.y + m_CameraPosY, BPos.z - 4.0));
            CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BPos.x, BPos.y + m_CameraPosY, BPos.z));

            if (m_CameraPosY >= 6.0f)
            {
                m_AnimCnt = 0.0;
                m_CameraWork = Force;
            }
            break;
        case CBossEvolution::Force:
            if (m_CameraPosZ <= 5.0f)
            {
                m_CameraPosZ += 0.08;
            }

            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BPos.x, BPos.y + 6.0f, (BPos.z-4.0) - m_CameraPosZ));
            CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BPos.x, BPos.y + 6.0f, BPos.z));

            if (m_CameraPosZ >= 5.0f)
            {
                m_AnimCnt++;
                m_CameraWork = Fifth;

            }

            break;
        case CBossEvolution::Fifth:
            m_pBoss->AnimChange();
            break;
        default:
            break;
        }
    }
    if (m_pBoss->SceneChange())
    {
        m_SceneTransitionFlg = true;    //�V�[���J�ڃt���O�L����
    }

    if (m_SceneTransitionFlg && FadeOut()) 
    {
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
        //�J���������킹��
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    }

}

void CBossEvolution::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_EndChange == false) {
        m_pBeEvoBoss->Draw(View, Proj, Light, Camera);
    }
   if(m_EndChange == true)
   {
       m_pBoss->Draw(View, Proj, Light, Camera);
   }

   m_pSky->Draw(View, Proj, Light, Camera);

   if (m_Cut == Change || m_Cut == Evolution && m_CameraWork != Fifth)
   {
       m_pWhiteFade->Draw();
   }

   WriteText::GetInstance()->Draw_Text(L"Boss Evolution", WriteText::Select, D3DXVECTOR2(0,0));

}

void CBossEvolution::PlayWhiteFade()
{
    if(m_AlphaChange == false)
    {
        m_Alpha += 0.01f;

        if (m_Alpha >= 1.0f)
        {
            m_EndChange = true;
            m_AlphaChange = true;
            m_Cut = Evolution;
        }
    }
    else
    {
        m_Alpha -= 0.01f;

        if (m_Alpha <= 0.0f)
        {
            m_Alpha = 0.0f;
        }
    }
    
}

