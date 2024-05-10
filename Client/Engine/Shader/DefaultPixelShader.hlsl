cbuffer constant : register(b0)
{
	float r;
	float g;
	float b;
	float a;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

Texture2D texture_ : register(t0);
SamplerState sampler_ : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 color = input.color;
	if (input.texcoord.x >= 0 && input.texcoord.y >= 0)
    {
        color = texture_.Sample(sampler_, input.texcoord);
    }
	
	color.r *= r;
	color.g *= g;
	color.b *= b;
	color.a *= a;
	
	return color;
}