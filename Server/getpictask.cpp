#include "getpictask.h"

GetPicTask::GetPicTask(QString picPath)
{
    _path = picPath;

    this->tesseract = new tesseract::TessBaseAPI();
    if (tesseract->Init(NULL, "eng"))
    {
        qDebug() << "error initializing tesseract";
        exit(0);
    }
    this->tesseract->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
}

void GetPicTask::run()
{
    platedetector           detector;
    std::vector<QString>    cropped_list;
    QString                 result;
    QString                 tmp_res;
    int                     tmp_diff;

    result = "";
    tmp_diff = 0;
    cropped_list = detector.run(this->_path.toStdString().c_str());
    for(std::vector<QString>::iterator it = cropped_list.begin(); it != cropped_list.end(); ++it)
    {
        tmp_res = this->startRecognize((*it));
        if (tmp_diff == 0)
        {
            tmp_diff = 7 - result.length();
            if (tmp_diff < 0) tmp_diff *= -1;
            result = tmp_res;
        }
        else
        {
            int diff = 7 - tmp_res.length();
            if (diff < 0) diff *= -1;
            if (diff < tmp_diff)
            {
                tmp_diff = diff;
                result = tmp_res;
            }
        }
    }
    emit Result(result);
}

QString GetPicTask::startRecognize(QString fileName)
{
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Images (*.bmp *.jpg)"));

    cv::Mat mat;
    cv::Mat output_mat_1;
    cv::Mat output_mat_2;
    cv::Mat black_pic;

    mat = cv::imread(fileName.toStdString().c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    mat.copyTo(output_mat_1);
    mat.copyTo(output_mat_2);

    //Add Sharpening
    cv::blur(output_mat_1, output_mat_2, cv::Size(1, 1));
    cv::addWeighted(output_mat_1, 1.5, output_mat_2, -0.5, 0, output_mat_1);

    //Add Threshold and Morphological correction
    cv::threshold(output_mat_1, output_mat_1, 195, 255, CV_THRESH_BINARY);
    //cv::adaptiveThreshold(output_mat_1, output_mat_1, 255, 0, 0, 33, 0);
    //cv::Mat rectangle_mat = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
    //cv::morphologyEx(output_mat_1, output_mat_1, cv::MORPH_CLOSE, rectangle_mat);
    output_mat_1.copyTo(output_mat_2);
    cv::bitwise_not(output_mat_2, output_mat_2);

    //Find Holes and Numbers
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> filtered_contours;

    cv::findContours(output_mat_1, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    black_pic.create(mat.size().height, mat.size().width, CV_8UC1);
    black_pic.setTo(cv::Scalar(0, 0, 0));

    for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin() ; it != contours.end(); ++it)
    {
        cv::Rect r = cv::boundingRect((*it));

        if ((*it).size() > 5 && r.height > 20 && r.width < 30)
        {
            filtered_contours.push_back((*it));
            cv::rectangle(black_pic, r, cv::Scalar(255, 0, 0), 1);

            /* COMPARE BLOCK BY BLOCK
            this->tesseract->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
            cv::Rect rect(r);

            rect.x -= 2;
            rect.y -= 2;
            rect += cv::Size(4, 4);

            if (rect.x < 0) rect.x = 0;
            if (rect.y < 0) rect.y = 0;
            if (rect.x + rect.width > mat.size().width)
                rect.width -= (rect.x + rect.width) - mat.size().width;
            if (rect.y + rect.height > mat.size().height)
                rect.height -= (rect.y + rect.height) - mat.size().height;

            cv::rectangle(black_pic, rect, cv::Scalar(255, 0, 0), 1);

            cv::Mat tmp = mat(rect);
            cv::Mat cropped = mat(rect);

            //tmp.copyTo(cropped);
            cv::blur(cropped, cropped, cv::Size(2, 2));
            cv::threshold(cropped, cropped, 195, 255, CV_THRESH_BINARY);

            cv::imwrite("/Users/antoinela/BJTU_Projects/Project Software Training 1/LicenseRecognizer/build-Server-Desktop_Qt_5_2_0_clang_64bit-Debug/Server.app/Contents/MacOS/temp.jpg", cropped);

            Pix *image = pixRead("/Users/antoinela/BJTU_Projects/Project Software Training 1/LicenseRecognizer/build-Server-Desktop_Qt_5_2_0_clang_64bit-Debug/Server.app/Contents/MacOS/temp.jpg");
            this->tesseract->SetImage(image);

            char *outText;
            outText = this->tesseract->GetUTF8Text();
            //qDebug() << "result" << outText;

            unsigned long i = 0;
            while (i < strlen(outText))
            {
                if (outText[i] == '\n' || outText[i] == ' ')
                {
                    outText[i] = 0;
                }
                i++;
            }
            tmp_result.append(outText); */
        }
    }
    cv::drawContours(black_pic, filtered_contours, -1, cv::Scalar(255, 255, 255));
    //cv::bitwise_not(black_pic, black_pic);

    // COMPARE ALL THE PLATE
    char *outText;
    cv::imwrite("/Users/antoinela/BJTU_Projects/Project Software Training 1/LicenseRecognizer/build-Server-Desktop_Qt_5_2_0_clang_64bit-Debug/Server.app/Contents/MacOS/temp.jpg", black_pic);
    Pix *image = pixRead("/Users/antoinela/BJTU_Projects/Project Software Training 1/LicenseRecognizer/build-Server-Desktop_Qt_5_2_0_clang_64bit-Debug/Server.app/Contents/MacOS/temp.jpg");
    this->tesseract->SetImage(image);
    outText = this->tesseract->GetUTF8Text();

    QString ret_val = "";
    for (unsigned long i = 0; i < strlen(outText); i++)
    {
        if (outText[i] != '\n' && outText[i] != ' ')
            ret_val.append(outText[i]);
    }
    qDebug() << "result" << ret_val;

    //cv::namedWindow(ret_val.toStdString(), cv::WINDOW_AUTOSIZE);
    //cv::imshow(ret_val.toStdString(), black_pic);

    return ret_val;
}
