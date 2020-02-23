Texture2D txDiffuse : register(t0);
Texture2D tx2 : register(t1);
Texture2D tx3 : register(t2);
Texture2D tx4 : register(t3);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
    float3 Tex3D : OTEXCOORD2;
    uint InstanceNo : IDNo;
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
    if (inputPixel.InstanceNo == 3)
        finalColor = txDiffuse.Sample(samLinear, inputPixel.Tex);
    else if (inputPixel.InstanceNo == 1)
        finalColor = tx2.Sample(samLinear, inputPixel.Tex);
    else if (inputPixel.InstanceNo == 2)
        finalColor = tx3.Sample(samLinear, inputPixel.Tex);
    else
        finalColor = tx4.Sample(samLinear, inputPixel.Tex);
    
    if (finalColor.a == 0)
        discard;
    
    return finalColor;
}