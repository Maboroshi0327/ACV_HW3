#ifndef _ImageProcessing_
#define _ImageProcessing_

#include <cmath>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <algorithm>
#include <vector>

#include "bmp.hpp"

namespace dip
{
    enum class ColorSpace
    {
        RGB,
        GRAY,
    };

    class Size
    {
    public:
        int rows;
        int columns;
        Size();
        Size(int rows, int columns);
        Size(const Size& source);
        int area() const;
        Size operator=(const Size& other);
        Size operator+(const int& other) const;
        Size operator-(const int& other) const;
        Size operator*(const double& other) const;
        Size operator/(const double& other) const;
        bool operator==(const Size& other) const;
        bool operator!=(const Size& other) const;
    };

    template<typename T>
    class Coordinate
    {
    public:
        T row;
        T column;
        void setCoord(T row, T column);

        Coordinate();
        Coordinate(T row, T column);
        Coordinate operator=(const Coordinate& other);
        bool operator==(const Coordinate& other) const;
        bool operator!=(const Coordinate& other) const;
    };

    class Image
    {
    public:
        ColorSpace color;
        Size size;
        std::vector<std::vector<uint8_t>> img_0;	// R, Gray
        std::vector<std::vector<uint8_t>> img_1;	// G
        std::vector<std::vector<uint8_t>> img_2;	// B
        void openBMP(const char* FileName);
        void saveBMP(const char* FileName, bool printName) const;
        void saveBMP(const char* FileName, int channel, bool printName) const;
        void setImg(const Image& source);

        Image();
        Image(const Image& source);
        Image(const std::vector<std::vector<uint8_t>>& img_0);
        Image(const std::vector<std::vector<uint8_t>>& img_0, const std::vector<std::vector<uint8_t>>& img_1, const std::vector<std::vector<uint8_t>>& img_2);
        Image(Size size);
        Image(Size size, uint8_t value);
        Image(Size size, ColorSpace color);
        Image(Size size, ColorSpace color, uint8_t value);
        Image operator=(const Image& other);
    };

    void pixelMove(const Image& imgIn, Image& imgOut, Coordinate<int> coord);
    void pixelMove(const Image& imgIn, Image& imgOut, Coordinate<int> coordIn, Coordinate<int> coordOut);
    void rgb2gray(const Image& imgIn, Image& imgOut);
    void threshold(const Image& imgIn, Image& imgOut, uint8_t th);
    void padding(const Image& imgIn, Image& imgOut, int pad);
    void padding(const Image& imgIn, Image& imgOut, int rowPad, int colPad);

    /*
          origin                                                                   new
    * * * * * * * * * *                     1                               * * * * * * * * * *
     *  0        3   *                 *********** vv                      *  0          3   *
      *             *      case2       *    *             case1           *                 *
       *           *     < ======     1******            ====== >        *     1           *
        * 1     2 *                    *                (inverse)             *       2   *
         * * * * *                     *                                           *     *
          (x, y)                       uu                                  (u, v)       *
    */
    void PerspectiveTransformation(const Image& imgIn, Image& imgOut, Coordinate<int> xy[4], Coordinate<int> uv[4]);
    void parameterPerspective(double& a, double& b, double& c, double& d, double& e, double& f, double& g, double& h, Coordinate<int> xy[4]);

    template<typename T1, typename T2>
    std::vector<std::vector<double>> multipleMatrix(const std::vector<std::vector<T1>>& left, const std::vector<std::vector<T2>>& right);

    template<typename T>
    std::vector<std::vector<double>> inverseMatrix(const std::vector<std::vector<T>>& matrix);

    template<typename T>
    T determinant(const std::vector<std::vector<T>>& matrix);

    template<typename T>
    std::vector<std::vector<T>> transposeMatrix(const std::vector<std::vector<T>>& matrix);

    template<typename T>
    std::vector<std::vector<T>> subMatrix(const std::vector<std::vector<T>>& matrix, Coordinate<int> coord);

}

#include "ImageProcessing.ipp"

#endif // _ImageProcessing_
