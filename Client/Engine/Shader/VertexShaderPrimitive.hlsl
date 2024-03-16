#pragma pack_matrix(row_major)

cbuffer constant : register(b0)
{
	float4x4 mat;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.pos = mul(float4(input.pos, 1.f), mat);
	output.color = input.color;
	return output;
}