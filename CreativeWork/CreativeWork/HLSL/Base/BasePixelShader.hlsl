#include "BaseHeader.hlsli"

float4 main(VS_OUT In) : SV_TARGET
{
    float4 Out;
    Out = g_abstractLight.GetColor(In);
    
    return Out;
}