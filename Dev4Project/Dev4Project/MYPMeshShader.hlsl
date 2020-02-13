Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct OutputVert
{
    float4 pos : SV_POSITION;
    float3 uvw : OTEXCOORD;
    float3 nrm : ONORMAL;
    float4 posW : WPOSITION;
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


float4 main(OutputVert inputPixel) : SV_TARGET
{
    float4 finalColor = 0;
    finalColor = txDiffuse.Sample(samLinear,inputPixel.uvw.xy);
    float4 Dirlight = saturate(dot(-normalize(light[0].lightDirection.xyz), normalize(inputPixel.nrm))) * light[0].lightColor;
    float4 Pointlight = saturate(dot(normalize(light[1].position - inputPixel.posW).xyz, normalize(inputPixel.nrm))) * light[1].lightColor;
    float pointAttinuation = 1 - saturate(length(light[1].position - inputPixel.posW) / light[1].lightRadius);
    Pointlight *= pointAttinuation;
    return finalColor * saturate( Pointlight + Dirlight);
}