#include"FBX.hlsli"
//0番スロットに設定されたテクスチャ
Texture2D<float4> tex	:register(t0);
//0番スロットに設定されたサンプラー
SamplerState smp	:register(s0);

//エントリーポイント
float4 main(VSOutput input) : SV_TARGET
{
	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp,input.uv);
	
	float3 lightPos = float3(1, 1, 1);
	float4 lightColor = float4(1, 1, 1, 1);

	//ambient
	float4 ambient = texcolor * 0.3 * lightColor;
	ambient.w = 1;

	//diffuse
	float intensity = saturate(dot(normalize(input.normal), lightPos));
	float4 color = texcolor;
	float4 diffuse = color * intensity * lightColor;

	//specular
	float3 eyeDir = normalize(cameraPos - input.worldPosition);
	float3 lightDir = normalize(lightPos);
	input.normal = normalize(input.normal);
	float3 reflectDir = -lightDir + 2 * input.normal * dot(input.normal, lightDir);
	float4 specular = pow(saturate(dot(reflectDir, eyeDir)), 20) * lightColor;
	//合成
	float4 ads = ambient + diffuse + specular;
	return ads;

	////Lambert反射
	//float3 light = normalize(float3(1, -1, 1));//右下奧向きのライト
	//float diffuse = saturate(dot(-light, input.normal));
	//float brightness = diffuse + 0.3f;
	//float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
	////陰影とテクスチャの色を合成
	//return shadecolor * texcolor;
}