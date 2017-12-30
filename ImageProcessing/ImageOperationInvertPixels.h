#pragma once

template<class TImage>
class ImageOperationInvertPixels
  {
  public:
    using TIndexType = int;
    using TPixelType = unsigned int;

    ImageOperationInvertPixels(TImage& io_image)
      : m_image(io_image)
      {}

    bool Apply()
      {
      const auto width  = static_cast<TIndexType>(m_image.width());
      const auto height = static_cast<TIndexType>(m_image.height());
      for (TIndexType w = 0; w < width; ++w)
        for (TIndexType h = 0; h < height; ++h)
          {
          const auto rgb = static_cast<TPixelType>(m_image.pixel(w, h));
          m_image.setPixel(w, h, ~rgb);
          }

      return true;
      }

    template<class TRegion>
    bool Apply(const TRegion& i_region)
      {
      return true;
      }

  private:
    TImage& m_image;
  };
