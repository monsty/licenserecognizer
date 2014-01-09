#include "getpictask.h"

GetPicTask::GetPicTask(QString picPath)
{
    _path = picPath;
    this->tmp_count = 0;

    this->tesseract = new tesseract::TessBaseAPI();
    if (tesseract->Init(NULL, "eng"))
    {
        qDebug() << "error initializing tesseract";
        exit(0);
    }
    this->tesseract->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

    QFileInfoList tmp_list;
    QDir dir;

    QString letters_dir(QDir::currentPath());
    letters_dir.append(QDir::separator()).append("letters");
    letters_dir = QDir::toNativeSeparators(letters_dir);

    if (dir.cd(letters_dir))
    {
        tmp_list = dir.entryInfoList();
        for (int i = 0; i < tmp_list.size(); ++i)
        {
            QString tmp_name = tmp_list.at(i).fileName();
            if (tmp_name.endsWith(".jpg", Qt::CaseInsensitive) == 1)
            {
                cv::Mat letter;
                QString tmp_path = "";
                tmp_path.append(letters_dir);
                tmp_path.append("/");
                tmp_path.append(tmp_list.at(i).fileName());

                letter = cv::imread(tmp_path.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
                this->alphalist.push_back(letter);
                this->alphaname.push_back(tmp_list.at(i).fileName());

                qDebug() << "loaded" << tmp_list.at(i).fileName();
            }
        }
    }
    else
    {
        qDebug() << "CANNOT FIND LETTERS DIRECTORY";
        exit(1);
    }

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
        if (tmp_res.length() > tmp_diff)
        {
            tmp_diff = tmp_res.length();
            result = tmp_res;
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
            //cv::rectangle(black_pic, r, cv::Scalar(255, 0, 0), 1);

            cv::Rect rect(r);
            cv::Mat tmp = mat(rect);
            cv::Mat cropped;

            tmp.copyTo(cropped);
            cv::blur(cropped, cropped, cv::Size(2, 2));
            cv::threshold(cropped, cropped, 195, 255, CV_THRESH_BINARY);

            //QString path = "/Users/antoinela/BJTU_Projects/Project Software Training 1/";
            //path.append(QString::number(this->tmp_count++));
            //path.append(".jpg");


            int count = 0;
            int difference = 0;
            int score_save = 999999;
            QString alpha;

            for (std::vector<cv::Mat>::iterator it = this->alphalist.begin(); it != this->alphalist.end(); ++it)
            {
                cv::Mat compare;

                (*it).copyTo(compare);
                cv::resize(compare, compare, cropped.size(), 0, 0, cv::INTER_CUBIC);

                difference = 0;
                for (int i = 0; i < compare.size().width; i++)
                {
                    for (int j = 0; j < compare.size().height; j++)
                    {
                        cv::Scalar color_1 = compare.at<uchar>(cv::Point(i, j));
                        cv::Scalar color_2 = cropped.at<uchar>(cv::Point(i, j));

                        if (color_1.val[0] != color_2.val[0])
                            difference++;
                    }
                }

                if (difference < score_save)
                {
                    alpha = this->alphaname.at(count);
                    score_save = difference;
                }

                count++;
            }
            qDebug() << "difference" << score_save << alpha;

            cv::rectangle(mat, r, cv::Scalar(255, 0, 0), 1);
            //cv::imwrite(path.toStdString(), cropped);
        }
    }
    cv::drawContours(black_pic, filtered_contours, -1, cv::Scalar(255, 255, 255));
    //cv::bitwise_not(black_pic, black_pic);

    // COMPARE ALL THE PLATE
    char *outText;

    QString tmp_file_path(QDir::currentPath());
    tmp_file_path.append(QDir::separator()).append("temp.jpg");
    tmp_file_path = QDir::toNativeSeparators(tmp_file_path);

    cv::imwrite(tmp_file_path.toStdString(), black_pic);
    Pix *image = pixRead(tmp_file_path.toStdString().c_str());
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
    //cv::imshow(ret_val.toStdString(), mat);

    return ret_val;
}
