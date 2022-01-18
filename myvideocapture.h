/**
 * @file myvideocaptura.h
 * @version 1.0
 * @date 10/09/2021
 */

#ifndef MYVIDEOCAPTURE_H
#define MYVIDEOCAPTURE_H

#include <QPixmap>
#include <QImage>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QCheckBox>
#include "serialterminal.h"

#define ID_CAMERA 1

class MyVideoCapture : public QThread
{
    Q_OBJECT
    public:
        MyVideoCapture(int id_camara = 1, QObject *parent = nullptr);
        ~MyVideoCapture();

        QPixmap pixmap() const
        {
            return mPixmap;
        }
        bool alarmaActive;
        bool stateAlarma;

    signals:
        void newPixmapCaptured(); // imagen nueva ha sido capturada
        void SendOnAlarma(int state);
        void ActiveSequence();
    protected:
        void run() override;
    private:
        cv::VideoCapture *mVideoCap; // capturador de video
        QPixmap mPixmap; // imagen de Qt
        cv::Mat mFrame; // imagen de OpenCV
        cv::Mat antFrame;
        int Id_Camara;
        SerialTerminal* terminal;

        QImage cvMatToQImage(const cv::Mat &inMat);
        QPixmap cvMatToQPixmap(const cv::Mat &inMat);
};

#endif // MYVIDEOCAPTURE_H
