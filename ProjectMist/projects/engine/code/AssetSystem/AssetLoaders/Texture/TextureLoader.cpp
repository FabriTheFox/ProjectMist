#include "MistEngine_PCH.h"

#include <AssetSystem/AssetLoaders/AssetLoaderDefs.h>
#include <wincodec.h>
#include <Utilities/StringUtils.h>

namespace ME { namespace AssetLoaders
{
	void LoadBGRAImage(Texture& tex, const String& path)
    {
        std::wstring wpath;
        StringToWide(path, wpath);

        IWICImagingFactory* wicFactory;
        CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

        IWICBitmapDecoder* decoder;
        wicFactory->CreateDecoderFromFilename(wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

        IWICBitmapFrameDecode* frame;
        decoder->GetFrame(0, &frame);

        frame->GetSize(&tex.mWidth, &tex.mHeight);

        WICPixelFormatGUID pixelFormat;
        frame->GetPixelFormat(&pixelFormat);

        uint32_t rowPitch = tex.mWidth * sizeof(uint32_t);
        uint32_t imageSize = rowPitch * tex.mHeight;

		tex.mTextureData.resize(size_t(imageSize));

        if (memcmp(&pixelFormat, &GUID_WICPixelFormat32bppBGRA, sizeof(GUID)) == 0)
        {
            frame->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(tex.mTextureData.data()));
        }
        else
        {
            IWICFormatConverter* formatConverter;
            wicFactory->CreateFormatConverter(&formatConverter);

            BOOL canConvert = FALSE;
            formatConverter->CanConvert(pixelFormat, GUID_WICPixelFormat32bppBGRA, &canConvert);
            if (!canConvert)
            {
                throw std::exception("CanConvert");
            }

            formatConverter->Initialize(frame, GUID_WICPixelFormat32bppBGRA,
                WICBitmapDitherTypeErrorDiffusion, nullptr, 0, WICBitmapPaletteTypeMedianCut);

            formatConverter->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(tex.mTextureData.data()));
        }
    }

	void LoadFromFile(Texture& tex, const String& filepath)
	{
		LoadBGRAImage(tex, filepath);
	}
}}

