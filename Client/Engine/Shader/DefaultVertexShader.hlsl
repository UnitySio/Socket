#pragma pack_matrix(row_major)

cbuffer constant : register(b0)
{
	float4x4 mat;
	float2 uv_offset;
	float2 uv_scale;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
	float4 color : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = mul(float4(input.position, 1.f), mat);
	output.texcoord = (input.texcoord + uv_offset) * uv_scale;
	output.color = input.color;
	return output;
}