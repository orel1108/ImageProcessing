#pragma once

#include "QRectWrapper.h"

#include <QImage>

#include <cstdint>

/**
 * @class QImageWrapper
 * @brief Class implements QImage wrapper.
 */
class QImageWrapper
  {
  public:
    /// Type of image index.
    using TIndexType = std::int32_t;
    /// Type of pixel value.
    using TPixelType = std::uint32_t;
    /// Type of image size.
    using TSizeType  = std::uint64_t;
    /// Type of rectangle.
    using TRectType  = QRectWrapper;

    /**
     * @brief Constructor.
     * @param[in,out] io_image Image to be wrapped.
     */
    explicit QImageWrapper(QImage& io_image);

    /**
     * @brief Checks if image is valid.
     * @return true if image is valid and false otherwise.
     */
    bool IsValid() const noexcept;

    /**
     * @brief Gets pixel at given position.
     * @param[in] i_x X position.
     * @param[in] i_y Y position.
     * @return Pixel at position.
     */
    TPixelType GetPixel(TIndexType i_x, TIndexType i_y) const;

    /**
     * @brief Sets pixel at given position.
     * @param[in] i_x X position.
     * @param[in] i_y Y position.
     * @param[in] Pixel to be set.
     */
    void SetPixel(TIndexType i_x, TIndexType i_y, TPixelType i_pixel);

    /**
     * @brief Get size of image in X direction.
     * @return X-size of image.
     */
    TSizeType GetSizeX() const;

    /**
     * @brief Get size of image in Y direction.
     * @return Y-size of image.
     */
    TSizeType GetSizeY() const;

  private:
    QImage& m_image;
  };
