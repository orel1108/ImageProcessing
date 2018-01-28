#pragma once

#include <Common/Matrix.h>

#include <Operations/ImageOperationLinearFilter.h>

#include <cstddef>

/**
 * @class ImageOperationCircularFilter
 * @brief Class implements "Circular filter".
 * @tparam TImage Type of image.
 * @tparam TSize Size of filter matrix.
 */
template<class TImage, std::uint8_t TSize>
class ImageOperationCircularFilter final
  : ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>
  {
  static_assert(TSize % 2 == 1, "Filter size should be odd.");

  using BaseFilter = ImageOperationLinearFilterPixels<TImage, Matrix<TSize, TSize>>;

  public:
    /**
     * @brief Constructor.
     * @param[in,out] Image to be processed.
     */
    ImageOperationCircularFilter(TImage& io_image);

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
ImageOperationCircularFilter<TImage, TSize>::ImageOperationCircularFilter(TImage& io_image)
  : BaseFilter(io_image)
  {}

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
bool ImageOperationCircularFilter<TImage, TSize>::Apply()
  {
  if (!m_image.IsValid())
    return false;
  
  _SetupMatrix();
  return BaseFilter::Apply();
  }

///////////////////////////////////////////////////////////////////////////////

template<class TImage, std::uint8_t TSize>
void ImageOperationCircularFilter<TImage, TSize>::_SetupMatrix()
  {
  const auto hr = static_cast<TIndexType>(TSize) / 2;
  const auto hc = static_cast<TIndexType>(TSize) / 2;
  
  const auto radius = TSize * TSize / 4;

  std::uint16_t counter = 0;
  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
      {
      const auto sqr_dist = (r - hr) * (r - hr) + (c - hc) * (c - hc);
      if (sqr_dist <= radius)
        {
        m_matrix.At(r, c) = 1.0;
        counter++;
        }
      }

  for (TIndexType r = 0; r < static_cast<TIndexType>(TSize); ++r)
    for (TIndexType c = 0; c < static_cast<TIndexType>(TSize); ++c)
        m_matrix.At(r, c) /= counter;
  }
