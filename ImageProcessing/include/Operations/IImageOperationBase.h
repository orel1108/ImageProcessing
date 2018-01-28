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
