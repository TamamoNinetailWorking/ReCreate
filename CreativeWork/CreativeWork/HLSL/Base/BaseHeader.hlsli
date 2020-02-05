
struct VS_IN
{
    float3 pos : POSITIONT;
    float3 normal : NORMAL;
    float2 texel : TEXCOORD;
};

struct VS_OUT
{
    float4 sv_pos : SV_Position;
    float3 normal : NORMAL;
    float2 texel : TEXCOORD0;
    float3 pos : TEXCOORD1;
};

interface iBaseLight
{
    float4 GetColor(VS_OUT In);
};

iBaseLight g_abstractLight;

Texture2D g_DecalMap : register(t0);
Texture2D g_TexMap01 : register(t1);

SamplerState g_Sampler : register(s0);

float GetDiffuseColor(float3 lightdir, float3 normal)
{
    float Out;
    
    Out = dot(lightdir, normal);
    Out = Out * 0.5f + 0.5f;
    Out *= Out;
    
    return Out;
}

float GetSpecularColor(float3 lightdir, float3 normal,float3 lookat)
{
    float Out = 0;
    
    float3 color = normalize(lightdir + lookat);
    
    Out = pow(max(0.0f, dot(normal, color)), 50.0f);
    
    return Out;
}

float3 GetMaterialColor(float2 texel)
{
    float3 Out;
    Out = g_DecalMap.Sample(g_Sampler, texel).rgb;
    
    return Out;
}

class cHalfLambert : iBaseLight
{
    float4 g_vecLight;
    
    float4 GetColor(VS_OUT In)
    {
        float4 Out;
        
        float3 lightdir = normalize(-g_vecLight.xyz);
        float3 normal = normalize(In.normal);
        
        float diffuse = GetDiffuseColor(lightdir, normal);
        
        Out = float4(GetMaterialColor(In.texel) * diffuse, 1);
        
        return Out;
    }
};

class cPhongShading : iBaseLight
{
    float4 g_vecLight;
    float4 g_EyePos;
    
    float4 GetColor(VS_OUT In)
    {
        float4 Out;
        
        float3 lightdir = normalize(-g_vecLight.xyz);
        float3 normal = normalize(In.normal);
        
        float diffuse = GetDiffuseColor(lightdir, normal);
        float3 lookat = normalize(g_EyePos.xyz - In.pos);
        float specular = GetSpecularColor(lightdir, normal, lookat);
        
        Out = float4(GetMaterialColor(In.texel) * diffuse + diffuse * specular, 1);
        
        return Out;
    }
    
};

class cCelShading : iBaseLight
{
    float4 g_vecLight;
    
    float4 GetColor(VS_OUT In)
    {
        float4 Out;
        
        float3 lightdir = normalize(-g_vecLight.xyz);
        float3 normal = normalize(In.normal);
        
        float diffuse = GetDiffuseColor(lightdir, normal);
        float celcolor = g_TexMap01.Sample(g_Sampler, diffuse).r;
        
        Out = float4(GetMaterialColor(In.texel) * celcolor, 1);
        
        return Out;
    }
};

cbuffer cbBuffer0 : register(b0)
{
    cHalfLambert g_HalfLambert;
    cPhongShading g_PhonShading;
    cCelShading g_CelShading;
};