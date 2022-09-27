#include "ImageToWeb.h"
#include "ui_ImageToWeb.h"



using namespace cv;

ImageToWeb::ImageToWeb(QWidget *parent) : 
    QMainWindow(parent), 
    ui(new Ui::ImageToWebClass)
{
    ui->setupUi(this);

    m_websocketServer = new WebSocketServer();
}

ImageToWeb::~ImageToWeb()
{
    delete ui;
}

void ImageToWeb::on_pushButton_clicked()
{
    VideoCapture cap;
    cap.open(0, CAP_DSHOW);

    Mat frame;

    while (cv::waitKey(1))
    {
        if (!cap.read(frame))
        {
            qDebug() << "No frames grabbed!\n";
            break;
        }

        cv::flip(frame, frame, 1);   // ×óÓÒ¾µÏñ

        std::vector<uchar> buf;
        cvMatToJPG(frame, buf);

        QByteArray jpgData = QByteArray::fromRawData(reinterpret_cast<const char*>(buf.data()), buf.size());

        emit m_websocketServer->sendBinaryMessage(jpgData);
    }
}

void ImageToWeb::cvMatToJPG(const cv::Mat& input, std::vector<uchar>& buf)
{
    // jpeg±àÂë
    std::vector<int> params;
    params.resize(3, 0);
    params[0] = cv::IMWRITE_JPEG_QUALITY;
    params[1] = 90;     // Ñ¹ËõÂÊ

    cv::imencode(".jpg", input, buf, params);
}