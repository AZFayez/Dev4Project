Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct OutputVert
{
    float4 pos : SV_POSITION;
    float3 uvw : OTEXCOORD;
    float3 nrm : ONORMAL;
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
    finalColor *= saturate(dot(-normalize(light[0].lightDirection.xyz), inputPixel.nrm)) * light[0].lightColor;
	return finalColor;
}