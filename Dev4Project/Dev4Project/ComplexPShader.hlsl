Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
};

float4 main(PS_INPUT inputPixel) : SV_TARGET
{
    float4 finalColor = { 1, 1, 0, 1 };
    finalColor = txDiffuse.Sample(samLinear, inputPixel.Tex);
    return finalColor;
}