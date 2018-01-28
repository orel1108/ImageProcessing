#pragma once

#include <Operations/IImageOperationBase.h>

#include <vector>

/**
 * @class ImageOperationLinearFilterPixels
 * @brief Class implement image pixels linear filtering.
 * @tparam TImage Type of image to be processed.
 * @tparam TMatrix Type of kernel matrix.
 */
template<class TImage, class TMatrix>
class ImageOperationLinearFilterPixels : public IImageOperationBase<TImage>
  {
  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationLinearFilterPixels(TImage& io_image);

    /**
     * @brief Filters pixels in image.
     * @return true on operation success and false otherwise.
     */
    bool Apply() override;

  protected:
    TMatrix m_matrix;
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage, class TMatrix>
ImageOperationLinearFilterPixels<TImage, TMatrix>::ImageOperationLinearFilterPixels(TImage& io_image)
  : IImageOperationBase<TImage>(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, class TMatrix>
bool ImageOperationLinearFilterPixels<TImage, TMatrix>::Apply()
  {
  if (!m_image.IsValid())
    return false;

  const auto sx = static_cast<TIndexType>(m_image.GetSizeX());
  const auto sy = static_cast<TIndexType>(m_image.GetSizeY());

  const auto hr = static_cast<TIndexType>(m_matrix.NumbefOfRows()) / 2;
  const auto hc = static_cast<TIndexType>(m_matrix.NumbefOfCols()) / 2;

  std::vector<std::vector<TPixelType>> copy_pixels(sx, std::vector<TPixelType>(sy, 0));

  for (TIndexType x = 0; x < sx; ++x)
    for (TIndexType y = 0; y < sy; ++y)
      for (TIndexType r = -hr; r < hr + 1; ++r)
        for (TIndexType c = -hc; c < hc + 1; ++c)
          {
          const auto m = (x + r + sx) % sx;
          const auto n = (y + c + sy) % sy;
          copy_pixels[m][n] += static_cast<TPixelType>(m_image.GetPixel(x, y) * m_matrix.At(r + hr, c + hc));
          }

  for (TIndexType x = 0; x < sx; ++x)
    for (TIndexType y = 0; y < sy; ++y)
      m_image.SetPixel(x, y, copy_pixels[x][y]);

  return true;
  }
