#pragma once

#include <Common/Matrix.h>
#include <Operations/ImageOperationLinearFilter.h>

#include <cstddef>

template<class TImage, std::size_t TSize>
class ImageOperationBoxFilter final : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>
  {
  static_assert(TSize % 2 == 1, "Filter size should be odd.");

  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationBoxFilter(TImage& io_image);

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
ImageOperationBoxFilter<TImage, TSize>::ImageOperationBoxFilter(TImage& io_image)
  : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::size_t TSize>
bool ImageOperationBoxFilter<TImage, TSize>::Apply()
  {
  if (!m_image.IsValid())
    return false;
  
  const auto matrix = _CalculateMatrix();
  ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>::SetMatrix(matrix);

  return ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>::Apply();
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::size_t TSize>
Matrix<TSize, TSize> ImageOperationBoxFilter<TImage, TSize>::_CalculateMatrix() const
  {
  const double matrix_size = TSize * TSize;
  Matrix<TSize, TSize> matrix;
  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
      matrix.At(r, c) = 1.0 / matrix_size;

  return matrix;
  }

///////////////////////////////////////////////////////////////////////////////
