#include "OBJ.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float3 lightPos = float3(1, 1, 1);
	float4 lightColor = float4(1, 1, 1, 1);
	float4 texcolor = tex.Sample(smp, input.uv);

	//float light_diffuse = saturate(dot(-light, input.normal));
	//float3 shade_color;
	//shade_color = m_ambient;
	//shade_color += m_diffuse * light_diffuse;
	//return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);

	//ambient
	float4 ambient = texcolor * 0.3 * lightColor;

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

}