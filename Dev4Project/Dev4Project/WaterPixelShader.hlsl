Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
};

struct Lights
{
    float4 position, lightDirection;
    float4 ambient, diffuse, specular, lightColor;
    float _constant, _linear, _exponent;
    unsigned int lightType;
    float cosineInnerCone, cosineOuterCone;
    float lightRadius;
    int lightOn;
};

cbuffer SHADER_VAR : register(b0)
{
    float4x4 worldMatrix;
    float4x4 viewMatrix;
    float4x4 projMatrix;
    Lights light[3];
};


float4 main(PS_INPUT inputPixel) : SV_TARGET
{
    float4 finalColor = 0;
    
    float2 tex = inputPixel.Tex;
    
    tex.x += saturate(sin(light[0]._constant * tex) * 0.25f);
    
    finalColor = txDiffuse.Sample(samLinear, tex);
    
    if (finalColor.a < 0.2)
        discard;
    
    return finalColor;
}