#include "OBJ.hlsli"

VSOutput main(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.svpos = mul(mat, pos);
	output.normal = normal;
	output.worldPosition = mul(world,output.svpos);
	output.uv = uv;
	return output;
}