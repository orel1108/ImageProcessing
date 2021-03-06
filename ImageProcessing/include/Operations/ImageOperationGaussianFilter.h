#pragma once

#include <Common/Matrix.h>

#include <Operations/ImageOperationLinearFilter.h>

#include <cstddef>

/**
 * @class ImageOperationGaussianFilter
 * @brief Class implements "Gaussian filter".
 * @tparam TImage Type of image.
 * @tparam TSize Size of filter matrix.
 */
template<class TImage, std::uint8_t TSize>
class ImageOperationGaussianFilter final
  : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>
  {
  static_assert(TSize % 2 == 1, "Filter size should be odd.");

  using BaseFilter = ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>;

  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationGaussianFilter(TImage& io_image);

    /**
     * @brief Filters pixels in image.
     * @return true on operation success and false otherwise.
     */
    bool Apply() override;

  private:
    void _SetupMatrix();
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
ImageOperationGaussianFilter<TImage, TSize>::ImageOperationGaussianFilter(TImage& io_image)
  : BaseFilter(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
bool ImageOperationGaussianFilter<TImage, TSize>::Apply()
  {
  if (!m_image.IsValid())
    return false;
  
  _SetupMatrix();
  return BaseFilter::Apply();
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
void ImageOperationGaussianFilter<TImage, TSize>::_SetupMatrix()
  {
  const double sigma  = 1.0;
  const double denum = 2 * sigma * sigma;
  const double coeff = denum * M_PI;

  const auto hr = static_cast<TIndexType>(TSize) / 2;
  const auto hc = static_cast<TIndexType>(TSize) / 2;
  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    {
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
      {
      const auto numer = (r - hr) * (r - hr) + (c - hc) * (c - hc);
      const auto expon = std::exp(-numer / denum);
      const auto value = expon / coeff;
      m_matrix.At(r, c) = value;
      }
    }
  }
