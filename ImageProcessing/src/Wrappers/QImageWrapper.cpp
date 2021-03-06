#include <Wrappers/QImageWrapper.h>

///////////////////////////////////////////////////////////////////////////////

QImageWrapper::QImageWrapper(QImage& io_image)
  : m_image(io_image)
  {
  }

///////////////////////////////////////////////////////////////////////////////

bool QImageWrapper::IsValid() const noexcept
  {
  return !m_image.isNull();
  }

///////////////////////////////////////////////////////////////////////////////

auto QImageWrapper::GetPixel(TIndexType i_x, TIndexType i_y) const -> TPixelType
  {
  return m_image.pixel(i_x, i_y);
  }

///////////////////////////////////////////////////////////////////////////////

void QImageWrapper::SetPixel(TIndexType i_x, TIndexType i_y, TPixelType i_pixel)
  {
  m_image.setPixel(i_x, i_y, i_pixel);
  }

///////////////////////////////////////////////////////////////////////////////

auto QImageWrapper::GetSizeX() const -> TSizeType
  {
  return m_image.width();
  }

///////////////////////////////////////////////////////////////////////////////

auto QImageWrapper::GetSizeY() const -> TSizeType
  {
  return m_image.height();
  }
