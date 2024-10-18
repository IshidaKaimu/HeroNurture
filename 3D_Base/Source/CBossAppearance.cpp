#include "CBossAppearance.h"
#include "CSceneManager.h"
#include "CSkinMeshManager.h"
#include "CSoundManager.h"
#include "CMeshManager.h"
#include "WriteText.h"


CBossAppearance::CBossAppearance()
    : m_pFastBoss  ()
    , m_CameraPosZ()
    , m_CameraLookY()
{
    Create();
    LoadData();
}

CBossAppearance::~CBossAppearance()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pFastBoss);
}

void CBossAppearance::Create()
{
    m_pFastBoss = new CFastBoss();
    m_pSky = new CSky();
}

void CBossAppearance::LoadData()
{
    //スキンメッシュクラスのインスタンスを変数に代入
    CSkinMeshManager* SkMng = CSkinMeshManager::GetInstance();
    
    //スタティックメッシュクラスのインスタンスを変数に代入
    CMeshManager* SMng = CMeshManager::GetInstance();

    //進化前ボスのメッシュ設定
    m_pFastBoss->AttachMesh(SkMng->GetMesh(CSkinMeshManager::FastBoss));

    //スカイボックス
    m_pSky->AttachMesh(SMng->GetMesh(CMeshManager::Sky));

    Init();

    //ボスの位置を変数に代入
    D3DXVECTOR3 pos = m_pFastBoss->GetPosition();

    //画面切り替わり時違和感がないように
    CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x, 1.0f, pos.z - 30.0f));
    CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y, pos.z));

    m_pFastBoss->ApeAnim();

}

void CBossAppearance::Init()
{
    D3DXVECTOR3 pos = m_pFastBoss->GetPosition();

}

void CBossAppearance::Update()
{
    if (!FadeIn()) { return; }

    CSceneManager* SMng = CSceneManager::GetInstance();

    m_pFastBoss->ApeAnim();

    //BGMの停止、音量
    CSoundManager::PlayLoop(CSoundManager::BGM_BossApe);
    CSoundManager::Volume(CSoundManager::BGM_BossApe, 400);


    D3DXVECTOR3 pos = m_pFastBoss->GetPosition();

    switch (m_Cut)
    {
    case CBossAppearance::Ape:

        m_AnimCnt++;
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x, 1.0f, pos.z - 30.0f));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y, pos.z));
        if (m_AnimCnt >= 300)
        {
            m_AnimCnt = 0;
            m_Cut = Left;
        }
        break;
    case CBossAppearance::Left:

        m_AnimCnt++;
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x + 5.0f, pos.y + 3.0f, pos.z));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y + 3.0f, pos.z));
        if (m_AnimCnt >= 180)
        {
            m_AnimCnt = 0;
            m_Cut = Right;
        }

        break;
    case CBossAppearance::Right:
        m_AnimCnt++;
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x - 5.0f, pos.y + 3.0f, pos.z));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y + 3.0f, pos.z));
        if (m_AnimCnt >= 180)
        {
            m_AnimCnt = 0;
            m_Cut = Center;
        }

        break;
    case CBossAppearance::Center:

        m_AnimCnt++;

        //正面
        if (m_CameraPosZ <= 8.0f)
        {
            m_CameraPosZ += 0.1f;
        }

        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x, 3.0f, pos.z - m_CameraPosZ));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y, pos.z));

        if (m_AnimCnt >= 200)
        {
            m_Cut = Zoom;
            m_AnimCnt = 0;
        }

        break;
    case CBossAppearance::Zoom:

        m_AnimCnt++;

        //正面
        if (m_CameraPosZ >= 6.0f)
        {
            m_CameraPosZ -= 0.08f;
        }

        if (m_CameraLookY <= 3.0f)
        {
            m_CameraLookY += 0.08f;
        }

        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(pos.x, 3.0f, pos.z - m_CameraPosZ));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(pos.x, pos.y + m_CameraLookY, pos.z));

        if (m_AnimCnt >= 120)
        {
            m_AnimCnt = 0;
            m_Cut = SceneChange;
        }

        break;
    case SceneChange:

        m_SceneTransitionFlg = true;    //シーン遷移フラグ有効化

        if (m_SceneTransitionFlg && FadeOut()) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);

            //カメラを合わせる
            CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
            CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

        }

        break;
    default:
        break;
    }
}

void CBossAppearance::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    m_pSky->Draw(View, Proj, Light, Camera);

    m_pFastBoss->Draw(View,Proj,Light,Camera);

    WriteText::GetInstance()->Draw_Text(L"Boss Appearance", WriteText::Select, D3DXVECTOR2(0, 0));

}
