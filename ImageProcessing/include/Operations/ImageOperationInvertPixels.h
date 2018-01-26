#pragma once

#include <Operations/IImageOperationBase.h>

/**
 * @class ImageOperationInvertPixels
 * @brief Class implement image pixels invertion.
 * @tparam Type of image to be processed.
 */
template<class TImage>
class ImageOperationInvertPixels final : public IImageOperationBase<TImage>
  {
  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationInvertPixels(TImage& io_image);

    /**
     * @brief Inverts all pixels in image.
     * @return true on operation success and false otherwise.
     */
    bool Apply() override;
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage>
ImageOperationInvertPixels<TImage>::ImageOperationInvertPixels(TImage& io_image)
  : IImageOperationBase<TImage>(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage>
bool ImageOperationInvertPixels<TImage>::Apply()
  {
  if (!m_image.IsValid())
    return false;

  const auto sx = static_cast<TIndexType>(m_image.GetSizeX());
  const auto sy = static_cast<TIndexType>(m_image.GetSizeY());
  for (TIndexType x = 0; x < sx; ++x)
    for (TIndexType y = 0; y < sy; ++y)
      {
      const auto rgb = static_cast<TPixelType>(m_image.GetPixel(x, y));
      m_image.SetPixel(x, y, ~rgb);
      }

  return true;
  }

///////////////////////////////////////////////////////////////////////////////
