#pragma once

#include <Common/Matrix.h>
#include <Operations/ImageOperationLinearFilter.h>

#include <cmath>
#include <cstddef>

template<class TImage, std::size_t TSize>
class ImageOperationGaussianFilter final : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>
  {
  static_assert(TSize % 2 == 1, "Filter size should be odd.");

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
    Matrix<TSize, TSize> _CalculateMatrix() const;
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::size_t TSize>
ImageOperationGaussianFilter<TImage, TSize>::ImageOperationGaussianFilter(TImage& io_image)
  : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::size_t TSize>
bool ImageOperationGaussianFilter<TImage, TSize>::Apply()
  {
  if (!m_image.IsValid())
    return false;
  
  const auto matrix = _CalculateMatrix();
  ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>::SetMatrix(matrix);

  return ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>::Apply();
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::size_t TSize>
Matrix<TSize, TSize> ImageOperationGaussianFilter<TImage, TSize>::_CalculateMatrix() const
  {
  const double sigma  = 1.0;
  const double denum = 2 * sigma * sigma;
  const double coeff = denum * M_PI;

  Matrix<TSize, TSize> matrix;

  const auto hr = static_cast<TIndexType>(TSize) / 2;
  const auto hc = static_cast<TIndexType>(TSize) / 2;
  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    {
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
      {
      const auto numer = (r - hr) * (r - hr) + (c - hc) * (c - hc);
      const auto expon = std::exp(-numer / denum);
      const auto value = expon / coeff;
      matrix.At(r, c) = value;
      }
    }

  return matrix;
  }

///////////////////////////////////////////////////////////////////////////////
