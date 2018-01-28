#pragma once

#include <Common/Matrix.h>

#include <Operations/ImageOperationLinearFilter.h>

#include <cstddef>

/**
 * @class ImageOperationBoxFilter
 * @brief Class implements "Box filter".
 * @tparam TImage Type of image.
 * @tparam TSize Size of filter matrix.
 */
template<class TImage, std::uint8_t TSize>
class ImageOperationBoxFilter final
  : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>
  {
  static_assert(TSize % 2 == 1, "Filter size should be odd.");

  using BaseFilter = ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>;

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
    void _SetupMatrix();
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
ImageOperationBoxFilter<TImage, TSize>::ImageOperationBoxFilter(TImage& io_image)
  : BaseFilter(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
bool ImageOperationBoxFilter<TImage, TSize>::Apply()
  {
  if (!m_image.IsValid())
    return false;
  
  _SetupMatrix();
  return BaseFilter::Apply();
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
void ImageOperationBoxFilter<TImage, TSize>::_SetupMatrix()
  {
  const double matrix_size = TSize * TSize;
  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
      m_matrix.At(r, c) = 1.0 / matrix_size;
  }
