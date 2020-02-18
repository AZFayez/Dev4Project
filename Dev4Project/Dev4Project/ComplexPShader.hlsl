Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : ONORMAL;
    float2 Tex : OTEXCOORD1;
    float3 Tex3D : OTEXCOORD2;
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
    finalColor = txDiffuse.Sample(samLinear, inputPixel.Tex);
    float4 Dirlight = saturate(dot(-normalize(light[0].lightDirection.xyz), normalize(inputPixel.Norm))) * light[0].lightColor;
    float4 Pointlight = saturate(dot(normalize(light[1].position.xyz - inputPixel.Tex3D).xyz, normalize(inputPixel.Norm))) * light[1].lightColor;
    float pointAttinuation = 1 - saturate(length(light[1].position.xyz - inputPixel.Tex3D) / light[1].lightRadius);
    Pointlight *= pointAttinuation;
    
    float3 SpotlightDir = normalize(light[2].position.xyz - inputPixel.Tex3D);
    float SurfaceRatio = saturate(dot(-SpotlightDir, light[2].lightDirection.xyz));
    float spotfactor = (SurfaceRatio > light[2].cosineOuterCone) ? 1 : 0;
    float spotLightRatio = saturate(dot(SpotlightDir.xyz, normalize(inputPixel.Norm)));
    float4 SpotColor = spotfactor * spotLightRatio * light[2].lightColor;
    
    float SpotAtten = 1 - saturate((light[2].cosineInnerCone - SurfaceRatio) / (light[2].cosineInnerCone - light[2].cosineOuterCone));
    SpotColor *= SpotAtten;
    
    return finalColor * saturate(Pointlight + Dirlight + SpotColor);
}