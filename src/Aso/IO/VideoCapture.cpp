/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/IO/VideoCapture.hpp>
#include <Aso/OpenCV2.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso
{

/**
 *
 */
VideoCapture::VideoCapture()
    : VideoCapture(0)
{}

/**
 *
 */
VideoCapture::VideoCapture(int captureId)
    : _ocvVideoCapture(captureId)
{}

/**
 *
 */
bool VideoCapture::isOpen() const
{
    return _ocvVideoCapture.isOpened();
}

/**
 *
 */
int VideoCapture::width() const
{
    return (int) _ocvVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
}

/**
 *
 */
int VideoCapture::height() const
{
    return (int) _ocvVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
}

/**
 *
 */
Rect VideoCapture::dimensions() const
{
    return Rect(width(), height());
}

/**
 *
 */
void VideoCapture::refresh()
{
    _ocvVideoCapture.read(_frame);
}

/**
 *
 */
const cv::Mat& VideoCapture::frame() const
{
    return _frame;
}

}
