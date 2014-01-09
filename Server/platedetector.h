#ifndef PLATEDETECTOR_H
#define PLATEDETECTOR_H

#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <opencv2/opencv.hpp>

class platedetector
{
public:
    platedetector();
    void            set_original(const char *);
    QPixmap         get_original();
    void            set_gray();
    QPixmap         get_gray();
    void            set_sobel();
    QPixmap         get_sobel();
    void            set_threshold();
    QPixmap         get_threshold();
    void            set_contours();
    QPixmap         get_contours();
    bool            VerifySizes(cv::RotatedRect);
    QImage          MatToQImage( const cv::Mat &i);
    void            crop_img();
    cv::Mat         histeq(cv::Mat in);
    void            create_tmp_file();
    std::vector<QString>            run(const char *);

    /* ---------------------------------------------------------------- */

    cv::Mat         original;
    cv::Mat         gray_img;
    cv::Mat         sobel;
    cv::Mat         threshold;
    cv::Mat         rectangle_mat;
    cv::Mat         draw_img;

    std::vector<cv::RotatedRect>    rects;

    std::vector<cv::Mat>     gray_tab;

    std::vector<QString>     tmp_list;
};

#endif // PLATEDETECTOR_H
