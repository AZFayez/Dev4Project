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
    
    if (finalColor.a < 0.2)
        discard;
    
    float4 Dirlight = saturate(dot(-normalize(light[0].lightDirection.xyz), normalize(inputPixel.nrm))) * light[0].lightColor;
    float4 Pointlight = saturate(dot(normalize(light[1].position - inputPixel.posW).xyz, normalize(inputPixel.nrm))) * light[1].lightColor;
    float pointAttinuation = 1 - saturate(length(light[1].position - inputPixel.posW) / light[1].lightRadius);
    Pointlight *= pointAttinuation;
    
    float4 SpotlightDir = normalize(light[2].position - inputPixel.posW);
    float SurfaceRatio = saturate(dot(-SpotlightDir, light[2].lightDirection));
    float spotfactor = (SurfaceRatio > light[2].cosineOuterCone) ? 1 : 0;
    float spotLightRatio = saturate(dot(SpotlightDir, normalize(inputPixel.nrm)));
    float4 SpotColor = spotfactor * spotLightRatio * light[2].lightColor;
    
    float SpotAtten = 1 - saturate((light[2].cosineInnerCone- SurfaceRatio) / (light[2].cosineInnerCone - light[2].cosineOuterCone));
    SpotColor *= SpotAtten;
    
    return finalColor * saturate( Pointlight + Dirlight + SpotColor);
}