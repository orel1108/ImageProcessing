#include "ImageIO.h"

#include <QImageReader>
#include <QImageWriter>

///////////////////////////////////////////////////////////////////////////////

const QImage& ImageIO::Get() const
  {
  return m_image;
  }

///////////////////////////////////////////////////////////////////////////////

void ImageIO::Set(const QImage& i_image)
  {
  m_image = i_image;
  }

///////////////////////////////////////////////////////////////////////////////

bool ImageIO::Load(const QString& i_filename)
  {
  QImageReader reader(i_filename);
  reader.setAutoTransform(true);
  m_image = reader.read();
  return !m_image.isNull();
  }

///////////////////////////////////////////////////////////////////////////////

bool ImageIO::Save(const QString& i_filename) const
  {
  if (m_image.isNull())
    return false;

  QImageWriter writer(i_filename);
  return writer.write(m_image);
  }
