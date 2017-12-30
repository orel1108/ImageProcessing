#pragma once

#include <QImage>
#include <QString>

class ImageIO
  {
  public:
    const QImage& Get() const;

    void Set(const QImage& i_image);

    bool Load(const QString& i_filename);
    
    bool Save(const QString& i_filename) const;

  private:
    QImage m_image;
  };
