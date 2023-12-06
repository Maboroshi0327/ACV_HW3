#include "hw.hpp"

#include <cmath>

#include <thread>
#include <vector>

#include <opencv2\opencv.hpp>

#include "ImageProcessing.hpp"

void HW3_2_front(dip::Image& front);
void HW3_2_back(dip::Image& back);

void HW3_1()
{
    dip::Image distortion;
    distortion.openBMP("distortion.bmp");

    int Hd = distortion.size.rows;
    int Wd = distortion.size.columns;
    int Hdo = Hd / 2;
    int Wdo = Wd / 2;
    double rd_max = std::sqrt(Hdo * Hdo + Wdo * Wdo);
    double theta = std::atan((double)Wdo / Hdo);

    int r1 = 4;
    double omega = 0.0036;
    double ru_max = std::tan(rd_max * omega) / (2.0 * std::tan(omega / 2.0));
    int Hu = static_cast<int>(ru_max * std::cos(theta) / r1);
    int Wu = static_cast<int>(ru_max * std::sin(theta) / r1);
    int Huo = Hu / 2;
    int Wuo = Wu / 2;

    dip::Image unwarp(dip::Size(Hu, Wu), 128);
    for (int r = 0; r < Hu; r++)
    {
        for (int c = 0; c < Wu; c++)
        {
            int xu = (r - Huo) * r1;
            int yu = (c - Wuo) * r1;
            double ru = std::sqrt(xu * xu + yu * yu);
            double rd = 1.0 / omega * std::atan(2.0 * ru * std::tan(omega / 2.0));

            if (xu > 0 && yu >= 0)
                theta = std::atan((double)yu / xu);
            else if (xu < 0 && yu >= 0)
                theta = std::atan((double)yu / xu) + M_PI;
            else if (xu < 0 && yu < 0)
                theta = std::atan((double)yu / xu) + M_PI;
            else if (xu > 0 && yu < 0)
                theta = std::atan((double)yu / xu);
            else if (xu == 0 && yu > 0)
                theta = M_PI_2;
            else if (xu == 0 && yu < 0)
                theta = -M_PI_2;
            else if (xu == 0 && yu == 0)
                theta = 0.0;

            int xd = static_cast<int>(rd * std::cos(theta));
            int yd = static_cast<int>(rd * std::sin(theta));
            xd += Hdo;
            yd += Wdo;

            if (0 <= xd && xd < Hd && 0 <= yd && yd < Wd)
            {
                unwarp.img_0[r][c] = distortion.img_0[xd][yd];
                unwarp.img_1[r][c] = distortion.img_1[xd][yd];
                unwarp.img_2[r][c] = distortion.img_2[xd][yd];
            }
        }
    }

    unwarp.saveBMP("HW3-1.bmp", true);
}

void HW3_2()
{
    dip::Image front, back;

    std::thread t1(HW3_2_front, std::ref(front));
    std::thread t2(HW3_2_back, std::ref(back));
    t1.join();
    t2.join();

    for (int r = 0; r < 1649; r++)
        for (int c = 0; c < 2479; c++)
            dip::pixelMove(back, front, dip::Coordinate<int>(r, c));

    front.saveBMP("HW3-2.bmp", true);
}

void HW3_Bonus()
{
    std::vector<cv::Mat> imgs;

    imgs.push_back(cv::imread("left.bmp"));
    imgs.push_back(cv::imread("right.bmp"));

    cv::Mat scans;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(cv::Stitcher::SCANS);
    cv::Stitcher::Status status = stitcher->stitch(imgs, scans);

    if (status != cv::Stitcher::OK)
    {
        std::cout << "Can't stitch images, error code = " << int(status) << std::endl;
        return;
    }

    cv::imwrite("HW3-Bonus.bmp", scans);
    cv::imshow("HW3-Bonus.bmp", scans);
    cv::waitKey();
}

void HW3_2_front(dip::Image& front)
{
    front.openBMP("front.bmp");

    dip::Coordinate<int> xy[4], uv[4];

    xy[0].setCoord(1248, 2479);
    xy[1].setCoord(29, 1838);
    xy[2].setCoord(41, 678);
    xy[3].setCoord(1248, 0);

    uv[0].setCoord(1648, 0);
    uv[1].setCoord(3506, 0);
    uv[2].setCoord(3506, 2478);
    uv[3].setCoord(1648, 2478);

    dip::PerspectiveTransformation(front, front, xy, uv);
}

void HW3_2_back(dip::Image& back)
{
    back.openBMP("back.bmp");

    dip::Coordinate<int> xy[4], uv[4];

    xy[0].setCoord(34, 683);
    xy[1].setCoord(1240, 0);
    xy[2].setCoord(1240, 2479);
    xy[3].setCoord(27, 1836);

    uv[0].setCoord(0, 0);
    uv[1].setCoord(1648, 0);
    uv[2].setCoord(1648, 2478);
    uv[3].setCoord(0, 2478);

    dip::PerspectiveTransformation(back, back, xy, uv);
}
