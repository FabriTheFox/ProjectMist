#include "MistEngine_PCH.h"

#include "Texture.h"
#include <wincodec.h>

std::vector<uint8_t> ME::Texture::LoadBGRAImage(const wchar_t* filename, uint32_t& width, uint32_t& height)
{
    IWICImagingFactory* wicFactory;
    CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

    IWICBitmapDecoder* decoder;
    wicFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

    IWICBitmapFrameDecode* frame;
    decoder->GetFrame(0, &frame);

    frame->GetSize(&width, &height);

    WICPixelFormatGUID pixelFormat;
    frame->GetPixelFormat(&pixelFormat);

    uint32_t rowPitch = width * sizeof(uint32_t);
    uint32_t imageSize = rowPitch * height;

    std::vector<uint8_t> image;
    image.resize(size_t(imageSize));

    if (memcmp(&pixelFormat, &GUID_WICPixelFormat32bppBGRA, sizeof(GUID)) == 0)
    {
        frame->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data()));
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

        formatConverter->CopyPixels(nullptr, rowPitch, imageSize, reinterpret_cast<BYTE*>(image.data()));
    }

    return image;
}
