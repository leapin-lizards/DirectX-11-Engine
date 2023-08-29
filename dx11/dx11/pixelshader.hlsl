cbuffer alphaBuffer : register(b0)
{
    float alpha;
}
struct PS_INPUT
{
    float4 inPos : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
};
Texture2D objTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input):SV_Target
{
    float3 pixelCoord = objTexture.Sample(samplerState,input.inTexCoord);
    
    return float4(pixelCoord, alpha);

}