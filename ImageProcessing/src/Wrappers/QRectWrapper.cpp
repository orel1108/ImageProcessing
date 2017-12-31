#include <Wrappers/QRectWrapper.h>

///////////////////////////////////////////////////////////////////////////////

QRectWrapper::QRectWrapper(const QRect& i_rect)
  : m_rect(i_rect)
  {
  }

auto QRectWrapper::GetPositionX() const -> TIndexType
  {
  return m_rect.bottom();
  }

auto QRectWrapper::GetPositionY() const -> TIndexType
  {
  return m_rect.left();
  }

auto QRectWrapper::GetSizeX() const -> TSizeType
  {
  return m_rect.width();
  }

auto QRectWrapper::GetSizeY() const -> TSizeType
  {
  return m_rect.height();
  }
