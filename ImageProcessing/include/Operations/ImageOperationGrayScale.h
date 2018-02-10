#pragma once

#include <Operations/IImageOperationBase.h>

/**
 * @class ImageOperationGrayScale
 * @brief Converts RGB image into gray scale.
 * @tparam Type of image to be processed.
 */
template<class TImage>
class ImageOperationGrayScale final : IImageOperationBase<TImage>
  {
  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationGrayScale(TImage& io_image);

    /**
     * @brief Converts RGB image into gray scale image.
     * @return true on operation success and false otherwise.
     */
    bool Apply() override;
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage>
ImageOperationGrayScale<TImage>::ImageOperationGrayScale(TImage& io_image)
  : IImageOperationBase<TImage>(io_image)
  {
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage>
bool ImageOperationGrayScale<TImage>::Apply()
  {
  if (!m_image.IsValid())
    return false;

  const auto sx = static_cast<TIndexType>(m_image.GetSizeX());
  const auto sy = static_cast<TIndexType>(m_image.GetSizeY());

  for (TIndexType x = 0; x < sx; ++x)
    for (TIndexType y = 0; y < sy; ++y)
      {
      const auto p = m_image.GetPixel(x, y);
      const auto r = (p >> 0)  & 0xFF;
      const auto g = (p >> 8)  & 0xFF;
      const auto b = (p >> 16) & 0xFF;
      const auto v = static_cast<TPixelType>(0.3 * r + 0.59 * g + 0.11 * b);
      m_image.SetPixel(x, y, v + (v << 8) + (v << 16));
      }

  return true;
  }
