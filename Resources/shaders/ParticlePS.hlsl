#include "Particle.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

cbuffer ConstBufferDataMaterial :register(b0)
{
	float4 color;
}

float4 main(GSOutput input) : SV_TARGET
{

	return float4(tex.Sample(smp,input.uv))*color;
//return float4(1, 1, 1, 1);
}