#pragma once

#include <QRect>

/**
 * @class QRectWrapper
 * @brief Class implements QRect wrapper.
 */
class QRectWrapper
  {
  public:
    /// Type of image index.
    using TIndexType = std::int32_t;
    /// Type of image size.
    using TSizeType  = std::uint64_t;

    /**
     * @brief Constructor.
     * @param[in] i_rect Rectangle to be wrapped.
     */
    QRectWrapper(const QRect& i_rect);

    /**
     * @brief Gets X position.
     */
    TIndexType GetPositionX() const;
    
    /**
     * @brief Gets Y position.
     */
    TIndexType GetPositionY() const;

    /**
     * @brief Gets X size.
     */
    TSizeType GetSizeX() const;

    /**
     * @brief Gets Y size.
     */
    TSizeType GetSizeY() const;

  private:
    QRect m_rect;
  };
