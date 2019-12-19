#pragma once

#include <Engine/MistEngineDefs.h>
#include <Libraries/Containers.h>

struct ID3D11Device;
struct ID3D11Buffer;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

namespace ME
{
    class IVertexLayout;   
    class DeviceResources;
    class RendererComp;

    class VertexShader;
    class PixelShader;

    class MISTENGINE_DLL ShaderProgram
    {
    public:
        virtual void CreateConstantBuffers(ID3D11Device* dev) = 0;
        virtual void Draw(DeviceResources* dev, RendererComp* comp) = 0;

        void SetVertexShader(VertexShader* vs) { mVertexShader = vs; }
        void SetPixelShader(PixelShader* ps) { mPixelShader = ps; }

    protected:
        ME::Vector<ID3D11Buffer*> mConstantBuffers;
        ID3D11Buffer* m_pConstantBuffer = nullptr;

        VertexShader* mVertexShader = nullptr;
        PixelShader* mPixelShader = nullptr;
    };

    class MISTENGINE_DLL VertexShader
    {
    public:
        void Create(ID3D11Device* dev, const ME::String& file, const IVertexLayout* verlay);

        ID3D11VertexShader* GetVertexShader() const { return m_pVertexShader; }
        ID3D11InputLayout* GetInputLayout() const { return m_pInputLayout; }
        ID3D11InputLayout* GetInputLayoutExtended() const { return m_pInputLayoutExtended; }

    private:
        ID3D11VertexShader* m_pVertexShader = nullptr;
        ID3D11InputLayout* m_pInputLayout = nullptr;
        ID3D11InputLayout* m_pInputLayoutExtended = nullptr;
    };

    class MISTENGINE_DLL PixelShader
    {
    public:
        void Create(ID3D11Device* dev, const ME::String& file);

        ID3D11PixelShader* GetPixelShader() const { return m_pPixelShader; }

    private:
        ID3D11PixelShader* m_pPixelShader = nullptr;
    };
}

