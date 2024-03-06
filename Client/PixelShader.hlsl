struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

Texture2D texture_ : register(t0);
SamplerState sampler_ : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 color = texture_.Sample(sampler_, input.texcoord);
    return float4(color, 1.f);
}