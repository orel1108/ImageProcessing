#pragma once

/**
 * @class IImageOperationBase
 * @brief Interface for operations on images.
 * @tparam Type of image to be processed.
 */
template<class TImage>
class IImageOperationBase
  {
  public:
    /// Type of image index.
    using TIndexType = typename TImage::TIndexType;
    /// Type of pixel value.
    using TPixelType = typename TImage::TPixelType;
    /// Type of image size.
    using TSizeType  = typename TImage::TSizeType;
    /// Type of rectangle.
    using TRectType  = typename TImage::TRectType;

    /**
     * @brief Constructor.
     * @param[in,out] io_image Image to be processed.
     */
    explicit IImageOperationBase(TImage& io_image) noexcept;

    /**
     * @brief Pure virtual function, applies operation on image.
     * @return true on operation success and false otherwise.
     */
    virtual bool Apply() = 0;

    /**
     * @brief Pure virtual function, applies operation on image in region.
     * @param[in] i_region Image region to be processed.
     * @return true on operation success and false otherwise.
     */
    virtual bool Apply(const TRectType& i_region) = 0;

  protected:
    TImage& m_image;
  };

///////////////////////////////////////////////////////////////////////////////
//// IMPL
///////////////////////////////////////////////////////////////////////////////

template<class TImage>
IImageOperationBase<TImage>::IImageOperationBase(TImage& io_image) noexcept
  : m_image(io_image)
  {
  }

///////////////////////////////////////////////////////////////////////////////
