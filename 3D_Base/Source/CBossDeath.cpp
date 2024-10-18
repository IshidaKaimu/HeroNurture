#include "CBossDeath.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CSkinMeshManager.h" 
#include "CEffect.h"
#include "CUIManager.h"
#include "CMeshManager.h"
#include "CSoundManager.h"

CBossDeath::CBossDeath()
    : m_pBoss()
    , m_pWhiteFade()
    , m_pSky()
    , m_CameraPosZ(10)
    , m_CameraPosY()
    , m_CameraPosX()
    , m_Alpha(0.0)
    , m_EndChange()
    , m_CameraChange()
{
    Create();
    LoadData();
}

CBossDeath::~CBossDeath()
{
    SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pWhiteFade);
    SAFE_DELETE(m_pBoss);
}

void CBossDeath::Create()
{
    m_pBoss = new CBoss();
    m_pWhiteFade = new CUIObject();
    m_pSky = new CSky();
    m_pCamera = new CCamera();
}

void CBossDeath::LoadData()
{
    //スキンメッシュマネージャのインスタンスを変数に代入
    CSkinMeshManager* SkMng = CSkinMeshManager::GetInstance();
    //UIマネージャのインスタンスを変数に代入
    CUIManager* UiMng = CUIManager::GetInstance();
    //メッシュマネージャーのインスタンスを変数に代入
    CMeshManager* MMng = CMeshManager::GetInstance();

    //変身後ボス
    m_pBoss->AttachMesh(SkMng->GetMesh(CSkinMeshManager::Boss));
    m_pBoss->DeathInit();

    //白フェード
    m_pWhiteFade->AttachSprite(UiMng->GetSprite(CUIManager::WhiteFade));
    m_pWhiteFade->SetAlpha(m_Alpha);

    //スカイボックス
    m_pSky->AttachMesh(MMng->GetMesh(CMeshManager::Sky));

    //ボスのポジション取得関数を変数に代入
    D3DXVECTOR3 BPos = m_pBoss->GetPosition();

    //ボス撃破シーンの初期カメラ位置
    CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(BPos.x, BPos.y + 5.0f, BPos.z - m_CameraPosZ));
    //ボス撃破シーンの初期注視点
    CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(BPos.x, BPos.y + 5.0f, BPos.z));
}

void CBossDeath::Update()
{
    //フェードイン処理
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

    D3DXVECTOR3 BPos = m_pBoss->GetPosition();

    m_pBoss->DeathAnim();

    m_pWhiteFade->SetAlpha(m_Alpha);

    m_pCamera->Update();

    //サウンドマネージャーのインスタンスを変数に代入
    CSoundManager* SMng = CSoundManager::GetInstance();

    //BGM
    SMng->PlayLoop(CSoundManager::BGM_BossDeath);
    //音量
    SMng->Volume(CSoundManager::BGM_BossDeath, 400);

    //カメラの位置
    D3DXVECTOR3  newCameraPos = D3DXVECTOR3(
        BPos.x + m_CameraPosX,
        (BPos.y + 5.0f) + m_CameraPosY,
        BPos.z - m_CameraPosZ);

    switch (m_Cut)
    {
    case CBossDeath::KnockBack:

        //白フェード
        PlayWhiteFade(0, 0.05, 0.6);

        m_AnimCnt++;
        if (m_AnimCnt >= 120)
        {
            m_Cut = ZoomUp;
            m_AnimCnt = 0;
            m_FlashCnt = 0;
        }
        
        break;
    case CBossDeath::ZoomUp:
    
        //白フェード
        PlayWhiteFade(0, 0.1, 0.8);

        //近づく
        if (m_CameraPosX <= 4.0f)
        {
            m_CameraPosX += 0.3f;
        }

        if (m_CameraPosY <= 3.0f)
        {
            m_CameraPosY += 0.4f;
        }

        if (m_CameraPosZ >= 6.0f)
        {
            m_CameraPosZ -= 0.2f;
        }


        if (m_CameraPosZ <= 7.0f)
        {
            m_AnimCnt++;
            if (m_AnimCnt > 60) 
            {
                m_Cut = FallingDown;
                m_AnimCnt = 0;
                m_FlashCnt = 0;
            }
        }
        break;
    case CBossDeath::FallingDown:

        //白フェード
        PlayWhiteFade(3, 0.03, 0.8);

        //だんだん下げていく
        if (m_CameraPosX >= 0.0f)
        {
            m_CameraPosX -= 0.04f;
        }

        if (m_CameraPosY >= -3.0f)
        {
            m_CameraPosY -= 0.03f;
        }

        if (m_CameraPosZ <= 10.0f)
        {
            m_CameraPosZ += 0.03f;
        }

        if (m_pBoss->BossFell())
        {
            m_AnimCnt++;
            if (m_AnimCnt >= 60)
            {
                m_Cut = Falled;
            }
        }
        break;
    case  CBossDeath::Falled:

        m_pCamera->StartShake(0.1f, 10.0, 1.0f, CSceneManager::GetCameraPos());

        m_pCamera->Update();

        //後ろに下がる
        if (m_CameraPosY >= -3.0f)
        {
            m_CameraPosY -= 0.03f;
        }

        if (m_CameraPosZ <= 20.0f)
        {
            m_CameraPosZ += 0.4f;
        }

        if (m_CameraPosY > 10.0f) {
            m_CameraPosY = 10.0f; // 最大Y座標を設定
        }

        break;
    default:
        break;
    }

    CSceneManager::GetInstance()->SetCameraPos(newCameraPos);

    //カメラの移動とボスの消滅が終わり次第シーン遷移
    if (m_CameraPosZ >= 20.0f )
    {

        m_AnimCnt++;
        if (m_AnimCnt >= 120) 
        {
            m_SceneTransitionFlg = true;    //シーン遷移フラグ有効化
        }
    }

    if (m_SceneTransitionFlg && FadeOut())
    {
        CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);

        //カメラを合わせる
        CSceneManager::GetInstance()->SetCameraPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
        CSceneManager::GetInstance()->SetCameraLook(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

    }

}

void CBossDeath::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    if (m_Cut != Falled) 
    {
        m_pBoss->Draw(View, Proj, Light, Camera);
    }

    m_pSky->Draw(View, Proj, Light, Camera);

    if (m_Cut != Falled) {
        m_pWhiteFade->Draw();
    }

    WriteText::GetInstance()->Draw_Text(L"Boss Destroy", WriteText::Select, D3DXVECTOR2(0, 0));

}

//白フェード再生
void CBossDeath::PlayWhiteFade(int max, float speed, float alpha)
{

    //サウンドマネージャーのインスタンスを変数に代入
    CSoundManager* SMng = CSoundManager::GetInstance();

    if (m_AlphaChange == false)
    {
        m_Alpha += speed;

        if (m_Alpha >= alpha)
        {
            m_AlphaChange = true;
            m_FlashCnt++;
            SMng->PlaySE(CSoundManager::SE_DeathNow);
            SMng->Volume(CSoundManager::SE_DeathNow,300);

        }
    }
    else
    {
        m_Alpha -= speed;

        if (m_Alpha <= 0.0f)
        {
            m_Alpha = 0.0f;
            if (m_FlashCnt <= max)
            {
                m_AlphaChange = false;
            }
        }
    }

}

