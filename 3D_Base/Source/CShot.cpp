#include "CShot.h"

CShot::CShot()
	: m_Display		 ( false )
	, m_MoveDirection()
	, m_MoveSpeed    ()
	, m_DisplayTime  ()
{
}

CShot::~CShot()
{
}

void CShot::Update()
{

	if( m_Display == true ){
		m_vPosition += m_MoveDirection * m_MoveSpeed  ;

		m_DisplayTime--;
		if( m_DisplayTime < 0 ){
			//見えない所に置いておく.
			m_vPosition = D3DXVECTOR3( 0.0f, -10.0f, 0.0f );
			m_Display = false;
		}
	}
}

void CShot::Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera )
{
	if( m_Display == true ){
		CStaticMeshObject::Draw( View, Proj, Light, Camera );
	}
}

void CShot::Reload( const D3DXVECTOR3& Pos, float RotY )
{
	//弾が飛んでいたら終了
	if (m_Display == true) return;

	m_vRotation.y = RotY;//弾の向き(見た目)も変える
	m_vPosition = Pos;
	m_Display = true;
	m_MoveDirection.y = RotY;
	m_MoveSpeed = 0.2f;
	m_DisplayTime = FPS * 3;	//約3秒くらい表示する

	//Z軸ベクトル(z+方向への単位ベクトル)
    //※長さ( 大きさ )が１のベクトルを単位ベクトルという
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);

	//Y方向の回転行列
	D3DXMATRIX mRotationY;
	//Y軸回転行列を作成
	D3DXMatrixRotationY(
		&mRotationY,	//(out行列)
		m_MoveDirection.y); //プレイヤーのY方向の回転値

	//Y軸回転行列を使ってZ軸ベクトルを座標変換している
	D3DXVec3TransformCoord(
		&m_MoveDirection,//(out)移動方向ベクトル
		&vecAxisZ,		//(in)Z軸ベクトル
		&mRotationY);	//Y軸回転行列

}
