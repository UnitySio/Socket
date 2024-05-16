#pragma pack_matrix(row_major)

cbuffer constant : register(b0)
{
	float4x4 mat;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = mul(float4(input.position, 1.f), mat);
	output.color = input.color;
	return output;
}