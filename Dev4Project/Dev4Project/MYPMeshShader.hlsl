Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct OutputVert
{
    float4 pos : SV_POSITION;
    float3 uvw : OTEXCOORD;
    float3 nrm : ONORMAL;
    
};

float4 main(OutputVert inputPixel) : SV_TARGET
{
    float4 finalColor = {1,1,0,1};
    finalColor = txDiffuse.Sample(samLinear,inputPixel.uvw.xy);
	return finalColor;
}