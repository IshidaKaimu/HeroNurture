/*********************************************************************
*	スタティックメッシュクラス用シェーダファイル.
**/
//グローバル変数.
//テクスチャは レジスタ t(n).
Texture2D		g_Texture	: register( t0 );
//サンプラは レジスタ s(n).
SamplerState	g_SamLinear	: register( s0 );

//コンスタントバッファ.
//メッシュ単位.
cbuffer per_mesh	: register( b0 )
{
	matrix	g_mW;			//ワールド行列.
	matrix	g_mWVP;			//ワールド,ビュー,プロジェクションの合成行列.
};
//マテリアル単位.
cbuffer per_material: register( b1 )
{
	float4	g_Diffuse;		//ディフューズ色(拡散反射色).
	float4	g_Ambient;		//アンビエント色(環境色).
	float4	g_Specular;		//スペキュラ色(鏡面反射色).
};
//フレーム単位.
cbuffer per_frame	: register( b2 )
{
	float4	g_CameraPos;	//カメラ位置(視点位置).
	float4	g_vLightDir;	//ライトの方向ベクトル.
};

//頂点シェーダの出力パラメータ.
struct VS_OUTPUT
{
	float4	Pos			: SV_Position;
	float3	Normal		: TEXCOORD0;
	float2	UV			: TEXCOORD1;
	float3	Light		: TEXCOORD2;
	float3	EyeVector	: TEXCOORD3;
	float4	PosWorld	: TEXCOORD4;
	float4	Color		: COLOR;
};

//-------------------------------------------------
//	頂点(バーテックス)シェーダ.
//-------------------------------------------------
VS_OUTPUT VS_Main(
	float4 Pos	: POSITION,
	float4 Norm	: NORMAL,
	float2 UV	: TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//プロジェクション変換(ワールド,ビュー,プロジェクション).
	output.Pos = mul( Pos, g_mWVP );

	//法線をモデルの姿勢に合わせる.
	// (モデルが回転すれば法線も回転させる必要があるため).
	output.Normal = mul( Norm, (float3x3)g_mW );
	output.Normal = normalize( output.Normal );

	//ライト方向:
	// ディレクショナルライトは、どこでも同じ方向.位置は無関係.
	output.Light = normalize( g_vLightDir );

	output.PosWorld = mul( Pos, g_mW );

	//視線ベクトル:
	// ワールド空間上での頂点から頂点へ向かうベクトル.
	output.EyeVector = normalize( g_CameraPos - output.PosWorld );

	//テクスチャ座標.
	output.UV = UV;

	return output;
}

//-------------------------------------------------
//	ピクセルシェーダ.
//-------------------------------------------------
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	//テクスチャカラー.
	float4 texColor = g_Texture.Sample( g_SamLinear, input.UV );

	return texColor;
}

