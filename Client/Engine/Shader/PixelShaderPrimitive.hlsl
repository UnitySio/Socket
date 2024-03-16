cbuffer constant : register(b0)
{
	float r;
	float g;
	float b;
	float alpha;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 color = input.color;
	color.r *= r;
	color.g *= g;
	color.b *= b;
	color.a *= alpha;
	
	return color;
}