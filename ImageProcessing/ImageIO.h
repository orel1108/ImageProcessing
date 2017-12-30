#pragma once

#include <QImage>
#include <QString>

/**
 * class ImageIO
 * @brief Class implements image load / save operations.
 */
class ImageIO
  {
  public:
    /**
     * @brief Getter for image.
     * @return Loaded image.
     */
    const QImage& Get() const;

    /**
     * @brief Sets image.
     * @param[in] i_image Image to be set.
     */
    void Set(const QImage& i_image);

    /**
     * @brief Loads image from file.
     * @param[in] i_filename Name of file with image.
     * @return true on operation success and false otherwise.
     */
    bool Load(const QString& i_filename);
    
    /**
     * @brief Saves image to file.
     * @param[in] i_filename Name of file.
     * @return true on operation success and false otherwise.
     */
    bool Save(const QString& i_filename) const;

  private:
    QImage m_image;
  };
