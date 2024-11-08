#include "CSkinMeshObject.h"
#include "Camera\CameraManager\CCameraManager.h"

CSkinMeshObject::CSkinMeshObject()
	: m_pMesh    ( nullptr )
	, m_pBSphere ( nullptr )
	, m_pAnimCtrl( nullptr )
{
	m_pBSphere = new CBoundingSphere();
}

CSkinMeshObject::~CSkinMeshObject()
{
	SAFE_DELETE(m_pBSphere);
	DetachMesh();
}

void CSkinMeshObject::Update()
{
	if (m_pMesh == nullptr) {
		return;
	}
}

void CSkinMeshObject::Draw( LIGHT& Light )
{
	if (m_pMesh == nullptr) {
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	CAMERA camera = CCameraManager::GetInstance().GetCamera();

	//レンダリング.
	m_pMesh->Render(camera.View, camera.Proj, Light, camera.Position, m_pAnimCtrl );
}

//メッシュを接続する
void CSkinMeshObject::AttachMesh(CSkinMesh& pMesh)
{
	m_pMesh = &pMesh;

	//アニメーションコントローラを取得
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimationController();

	//アニメーションコントローラのクローンを作成
	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl)))	//クローン作製先
	{
		_ASSERT_EXPR(false, L"アニメーションコントローラのクローン作製失敗");
	}
}

//メッシュを切り離す
void CSkinMeshObject::DetachMesh()
{
	m_pMesh = nullptr;

	SAFE_RELEASE(m_pAnimCtrl);
}

