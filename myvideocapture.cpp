#include "myvideocapture.h"
#include <QDebug>
#include "serialterminal.h"

MyVideoCapture::MyVideoCapture(int id_camara, QObject *parent)
    : QThread { parent }
{
    Id_Camara = id_camara;
    mVideoCap = new cv::VideoCapture(id_camara);
    stateAlarma = false;
    alarmaActive = false;
    if (!mVideoCap->isOpened())
    {
        mVideoCap = nullptr;
    }
}

MyVideoCapture::~MyVideoCapture()
{
    this->terminate();
    delete terminal;
}

void MyVideoCapture::run()
{
    if (mVideoCap->isOpened())
    {
        cv::Mat _kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size2i(3, 3), cv::Point2i(1, 1));
        while (true)
        {
            *mVideoCap >> mFrame;
            if (!mFrame.empty())
            {
                if(!antFrame.empty())
                {
                    cv::Mat difFrame;
                    subtract(mFrame, antFrame, difFrame);
                    threshold(difFrame, difFrame, 15, 255, cv::THRESH_BINARY);
                    morphologyEx(difFrame, difFrame, 0 /*CV_MOP_OPEN*/, _kernel, cv::Point2i(-1, -1), 1);
                    cvtColor(difFrame, difFrame, cv::COLOR_BGR2GRAY);

                    //cv::imshow("Movimientos " + std::to_string(Id_Camara), difFrame);

                    std::vector<std::vector<cv::Point>> contours;
                    std::vector<cv::Vec4i> hierarchy;

                    int largest_area = 0;
                    int largest_contour_index = 0;
                    cv::Rect bounding_rect;

                    findContours(difFrame, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

                    if(alarmaActive)
                    {
                        if(contours.size() > 0 && stateAlarma == false)
                        {
                            stateAlarma = true;
                            emit SendOnAlarma(1);
                            emit ActiveSequence();
                        }
                        for (size_t i = 0; i < contours.size(); i++)
                        {
                            double a = contourArea(contours[i], false);

                            if (a > largest_area)
                            {
                                largest_area = a;
                                largest_contour_index = i;
                                bounding_rect = boundingRect(contours[i]);
                            }
                        }
                    }

                    cv::Mat dst = mFrame.clone();
                    cv::Scalar color(255, 255, 255);
                    drawContours(dst, contours, largest_contour_index, color, cv::FILLED, 8, hierarchy);
                    rectangle(dst, bounding_rect, cv::Scalar(0, 255, 0), 1, 8, 0);

                    //cv::imshow("Rectangulo Movimientos " + std::to_string(Id_Camara), dst);

                    mFrame = dst.clone();
                }
                antFrame = mFrame.clone();
                mPixmap = cvMatToQPixmap(mFrame);
                emit newPixmapCaptured();
            }
            //cv::imshow("Deteccion de Movimientos " + std::to_string(Id_Camara), mFrame);
            //if (cv::waitKey(30) == 27) break;
        }
    }
}

QImage MyVideoCapture::cvMatToQImage(const cv::Mat &inMat)
{
    switch (inMat.type())
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);
            return image;
        }
        // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888);
            return image.rgbSwapped();
        }
        // 8-bit, 1 channel
        case CV_8UC1:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Grayscale8);
            return image;
        }
        default:
        {
            qWarning()<< "ASM::cvMatToQImage()- cv::Mat image type not handled in switch:" << inMat.type();
            break;
        }
    }
    return QImage();
}

QPixmap MyVideoCapture::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(cvMatToQImage(inMat));
}

