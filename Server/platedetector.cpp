#include "platedetector.h"

platedetector::platedetector()
{
}

void        platedetector::set_original(const char *filename)
{
    this->original = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
}

QImage  platedetector::MatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
               for ( int i = 0; i < 256; ++i )
                  sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

            image.setColorTable( sColorTable );

            return image;
         }

         default:
                qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
      }

      return QImage();
   }

QPixmap    platedetector::get_original()
{
   return QPixmap::fromImage( MatToQImage(this->original) );
}

void        platedetector::set_gray()
{
    cv::cvtColor(this->original, this->gray_img, CV_BGR2GRAY);
    cv::blur(this->gray_img, this->gray_img, cv::Size(5,5));
}

QPixmap       platedetector::get_gray()
{
    return QPixmap::fromImage( MatToQImage(this->gray_img));
}

void        platedetector::set_sobel()
{
    cv::Sobel(this->gray_img, this->sobel, CV_8U, 1, 0, 3, 1, 0);
}

QPixmap       platedetector::get_sobel()
{
    return QPixmap::fromImage( MatToQImage(this->sobel));
}

void        platedetector::set_threshold()
{
    cv::threshold(this->sobel, this->threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
}

QPixmap         platedetector::get_threshold()
{
    return QPixmap::fromImage(MatToQImage(this->threshold));
}

bool            platedetector::VerifySizes(cv::RotatedRect test)
{
    float   error = 0.4;
    // ratio aspect car plate size (width / height)
    const float aspect = 3.4193;
    // const float aspect = 4.7272;
    // min - max area
    int min = 25  * aspect * 25;
    int max = 120 * aspect * 120;
    // get ratio apect with margin error
    float rmin = aspect - aspect * error;
    float rmax = aspect + aspect * error;

    int area = test.size.height * test.size.width;
    float r = (float)test.size.width / (float)test.size.height;
    if (r < 1)
        r = 1 / r;
    if (( area < min || area > max) || (r < rmin || r > rmax))
        return false;
    return true;
}

void        platedetector::set_contours()
{
    std::vector<std::vector<cv::Point>> contours;
    //finding rectangle plate
    this->rectangle_mat = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(17,3));
    cv::morphologyEx(this->threshold, this->threshold, CV_MOP_CLOSE, this->rectangle_mat);

    //getting external points
    cv::findContours(this->threshold, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    //keeping interesting area
    std::vector<std::vector<cv::Point>>::iterator it= contours.begin();
    while (it != contours.end())
    {
        cv::RotatedRect mr = minAreaRect(cv::Mat(*it));
        if(!VerifySizes(mr))
            it = contours.erase(it);
        else
        {
            ++it;
            this->rects.push_back(mr);
        }
    }

    //drawing contours into another images
    this->original.copyTo(this->draw_img);
    cv::drawContours(this->draw_img, contours, -1, // draw all contours
                     cv::Scalar(0,255,0), // color
                     1); // thickness
}

QPixmap         platedetector::get_contours()
{
    return QPixmap::fromImage(MatToQImage(this->draw_img));
}

cv::Mat         platedetector::histeq(cv::Mat in)
{
    cv::Mat out(in.size(), in.type());
    if (in.channels()==3)
    {
        cv::Mat hsv;
        std::vector<cv::Mat> hsvSplit;
        cv::cvtColor(in, hsv, CV_BGR2HSV);
        split(hsv, hsvSplit);
        equalizeHist(hsvSplit[2], hsvSplit[2]);
        merge(hsvSplit, hsv);
        cvtColor(hsv, out, CV_HSV2BGR);
    }
    else if(in.channels()==1)
        equalizeHist(in, out);

    return out;
}

void            platedetector::create_tmp_file()
{
    qDebug() << gray_tab.size();
    for (int i = 0; i < this->gray_tab.size(); i++)
    {
        QString tmp_path(QDir::currentPath());
        tmp_path.append(QDir::separator()).append("cropped").append(QString::number(i)).append(".jpg");
        imwrite(tmp_path.toStdString().c_str(), this->gray_tab[i]);
        this->tmp_list.push_back(tmp_path);
    }
}

void            platedetector::crop_img()
{
    for(int k=0; k< this->rects.size(); k++)
     {
         cv::Point2f rect_points[4]; this->rects[k].points( rect_points );
         for( int j = 0; j < 4; j++ )
             cv::line(this->draw_img, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,0,255), 1, 8 );
         //Get rotation matrix
         float r= (float)this->rects[k].size.width / (float)this->rects[k].size.height;
         float angle=this->rects[k].angle;
         if(r<1)
             angle=90+angle;
        cv::Mat rotmat = cv::getRotationMatrix2D(this->rects[k].center, angle,1);

         //Create and rotate image
         cv::Mat img_rotated;
         cv::warpAffine(this->original, img_rotated, rotmat, this->original.size(), CV_INTER_CUBIC);

         //Crop image
         cv::Size rect_size = this->rects[k].size;
         if(r < 1)
             std::swap(rect_size.width, rect_size.height);

         cv::Mat img_crop;
         getRectSubPix(img_rotated, rect_size, rects[k].center, img_crop);

         //Create resize
         cv::Mat resultResized;
         resultResized.create(40,140, CV_8UC3);
         cv::resize(img_crop, resultResized, resultResized.size(), 0, 0, cv::INTER_CUBIC);

         //Put to gray
         cv::Mat grayResult;
         cv::cvtColor(resultResized, grayResult, CV_BGR2GRAY);
         cv::blur(grayResult, grayResult, cv::Size(3,3));
         grayResult = histeq(grayResult);
         gray_tab.push_back(grayResult);
    }
}

std::vector<QString>           platedetector::run(const char *filename)
{
    this->set_original(filename);
    this->set_gray();
    this->set_sobel();
    this->set_threshold();
    this->set_contours();
    this->crop_img();
    this->create_tmp_file();
    return (this->tmp_list);
}


