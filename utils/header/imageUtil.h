#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H
#include <QImage>
class ImageUtil
{
public:
    static int getPixelNum(const QImage &image)
    {
        return image.width() * image.height();
    }
};

#endif // IMAGEUTIL_H