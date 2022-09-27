#ifndef IMAGETOWEB_H
#define IMAGETOWEB_H

#include <QtWidgets/QMainWindow>
#include "websocketserver.h"
#include "opencv2/opencv.hpp"


namespace Ui
{
    class ImageToWebClass;
}

class ImageToWeb : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageToWeb(QWidget *parent = nullptr);
    ~ImageToWeb();

private slots:
    void on_pushButton_clicked();

private:
    void cvMatToJPG(const cv::Mat& input, std::vector<uchar>& buf);

    Ui::ImageToWebClass *ui;


    WebSocketServer* m_websocketServer;
};

#endif //IMAGETOWEB_H
