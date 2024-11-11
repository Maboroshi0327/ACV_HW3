#include "ImageProcessing.hpp"

namespace dip
{
    Size::Size()
    {
        this->rows = 0;
        this->columns = 0;
    }

    Size::Size(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
    }

    Size::Size(const Size& source)
    {
        this->rows = source.rows;
        this->columns = source.columns;
    }

    int Size::area() const
    {
        return this->rows * this->columns;
    }

    Size Size::operator=(const Size& other)
    {
        this->rows = other.rows;
        this->columns = other.columns;
        return *this;
    }

    Size Size::operator+(const int& other) const
    {
        return Size(this->rows + other, this->columns + other);
    }

    Size Size::operator-(const int& other) const
    {
        return Size(this->rows - other, this->columns - other);
    }

    Size Size::operator*(const double& other) const
    {
        return Size(int(this->rows * other), int(this->columns * other));
    }

    Size Size::operator/(const double& other) const
    {
        return Size(int(this->rows / other), int(this->columns / other));
    }

    bool Size::operator==(const Size& other) const
    {
        bool result = this->rows == other.rows;
        result &= this->columns == other.columns;
        return result;
    }

    bool Size::operator!=(const Size& other) const
    {
        bool result = this->rows != other.rows;
        result |= this->columns != other.columns;
        return result;
    }

    void Image::openBMP(const char* FileName)
    {
        BMP bmp;
        bmp.open_img(FileName, this->img_0, this->img_1, this->img_2);
        this->color = ColorSpace::RGB;
        this->size.rows = (int)Image::img_0.size();
        this->size.columns = (int)Image::img_0[0].size();
    }

    void Image::saveBMP(const char* FileName, bool printName) const
    {
        BMP bmp;

        bool flag = false;
        if (this->color == ColorSpace::RGB)
        {
            flag = true;
            bmp.save_img(FileName, this->img_0, this->img_1, this->img_2);
        }
        if (this->color == ColorSpace::GRAY)
        {
            flag = true;
            bmp.save_img(FileName, this->img_0, this->img_0, this->img_0);
        }

        if (printName && flag)
            std::cout << "Output file: " << FileName << std::endl;
    }

    void Image::saveBMP(const char* FileName, int channel, bool printName) const
    {
        if (this->color != ColorSpace::RGB)
        {
            std::printf("saveBMP: Image->color != RGB\n");
            std::exit(1);
        }
        if (channel != 0 && channel != 1 && channel != 2)
        {
            std::printf("saveBMP: Image doesn't have channel %d.\n", channel);
            std::exit(1);
        }

        BMP bmp;
        switch (channel)
        {
        case 0:
            bmp.save_img(FileName, this->img_0, this->img_0, this->img_0);
            break;

        case 1:
            bmp.save_img(FileName, this->img_1, this->img_1, this->img_1);
            break;

        case 2:
            bmp.save_img(FileName, this->img_2, this->img_2, this->img_2);
            break;
        }

        if (printName)
            std::cout << "Output file: " << FileName << std::endl;
    }

    void Image::setImg(const Image& source)
    {
        this->color = source.color;
        this->size = source.size;
        this->img_0 = source.img_0;
        this->img_1 = source.img_1;
        this->img_2 = source.img_2;
    }

    Image::Image()
    {
        this->size = Size(0, 0);
    }

    Image::Image(const Image& source)
    {
        this->color = source.color;
        this->size = source.size;
        this->img_0 = source.img_0;
        this->img_1 = source.img_1;
        this->img_2 = source.img_2;
    }

    Image::Image(const std::vector<std::vector<uint8_t>>& img_0)
    {
        this->color = ColorSpace::GRAY;
        this->size.rows = (int)img_0.size();
        this->size.columns = (int)img_0[0].size();
        this->img_0 = img_0;
    }

    Image::Image(const std::vector<std::vector<uint8_t>>& img_0, const std::vector<std::vector<uint8_t>>& img_1, const std::vector<std::vector<uint8_t>>& img_2)
    {
        this->color = ColorSpace::RGB;
        this->size.rows = (int)img_0.size();
        this->size.columns = (int)img_0[0].size();
        this->img_0 = img_0;
        this->img_1 = img_1;
        this->img_2 = img_2;
    }

    Image::Image(Size size)
    {
        this->color = ColorSpace::RGB;
        this->size = size;
        this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
        this->img_1 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
        this->img_2 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
    }

    Image::Image(Size size, uint8_t value)
    {
        this->color = ColorSpace::RGB;
        this->size = size;
        this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
        this->img_1 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
        this->img_2 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
    }

    Image::Image(Size size, ColorSpace color)
    {
        this->color = color;
        this->size = size;
        if (color == ColorSpace::GRAY)
        {
            this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
        }
        else
        {
            this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
            this->img_1 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
            this->img_2 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, 0));
        }
    }

    Image::Image(Size size, ColorSpace color, uint8_t value)
    {
        this->color = color;
        this->size = size;
        if (color == ColorSpace::GRAY)
        {
            this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
        }
        else
        {
            this->img_0 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
            this->img_1 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
            this->img_2 = std::vector<std::vector<uint8_t>>(size.rows, std::vector<uint8_t>(size.columns, value));
        }
    }

    Image Image::operator=(const Image& other)
    {
        this->color = other.color;
        this->size = other.size;
        this->img_0 = other.img_0;
        this->img_1 = other.img_1;
        this->img_2 = other.img_2;
        return *this;
    }

    void pixelMove(const Image& imgIn, Image& imgOut, Coordinate<int> coord)
    {
        if (imgIn.color == ColorSpace::GRAY)
        {
            imgOut.img_0[coord.row][coord.column] = imgIn.img_0[coord.row][coord.column];
        }
        else
        {
            imgOut.img_0[coord.row][coord.column] = imgIn.img_0[coord.row][coord.column];
            imgOut.img_1[coord.row][coord.column] = imgIn.img_1[coord.row][coord.column];
            imgOut.img_2[coord.row][coord.column] = imgIn.img_2[coord.row][coord.column];
        }
    }

    void pixelMove(const Image& imgIn, Image& imgOut, Coordinate<int> coordIn, Coordinate<int> coordOut)
    {
        if (imgIn.color == ColorSpace::GRAY)
        {
            imgOut.img_0[coordOut.row][coordOut.column] = imgIn.img_0[coordIn.row][coordIn.column];
        }
        else
        {
            imgOut.img_0[coordOut.row][coordOut.column] = imgIn.img_0[coordIn.row][coordIn.column];
            imgOut.img_1[coordOut.row][coordOut.column] = imgIn.img_1[coordIn.row][coordIn.column];
            imgOut.img_2[coordOut.row][coordOut.column] = imgIn.img_2[coordIn.row][coordIn.column];
        }
    }

    void rgb2gray(const Image& imgIn, Image& imgOut)
    {
        if (imgIn.color == ColorSpace::GRAY)
        {
            imgOut = imgIn;
            return;
        }

        Image imgGray(Size(imgIn.size), ColorSpace::GRAY);
        for (int r = 0; r < imgIn.size.rows; r++)
        {
            for (int c = 0; c < imgIn.size.columns; c++)
            {
                double gray = std::round(
                    0.299 * imgIn.img_0[r][c]
                    + 0.587 * imgIn.img_1[r][c]
                    + 0.114 * imgIn.img_2[r][c]
                );

                imgGray.img_0[r][c] = static_cast<uint8_t>(gray);
            }
        }

        imgOut.setImg(imgGray);
    }

    void threshold(const Image& imgIn, Image& imgOut, uint8_t th)
    {
        Image imgTh(Size(imgIn.size), imgIn.color);

        if (imgIn.color == ColorSpace::RGB)
        {
            for (int r = 0; r < imgIn.size.rows; r++)
                for (int c = 0; c < imgIn.size.columns; c++)
                {
                    imgTh.img_0[r][c] = (imgIn.img_0[r][c] < th) ? 0 : 255;
                    imgTh.img_1[r][c] = (imgIn.img_1[r][c] < th) ? 0 : 255;
                    imgTh.img_2[r][c] = (imgIn.img_2[r][c] < th) ? 0 : 255;
                }
        }
        else if (imgIn.color == ColorSpace::GRAY)
        {
            for (int r = 0; r < imgIn.size.rows; r++)
                for (int c = 0; c < imgIn.size.columns; c++)
                    imgTh.img_0[r][c] = (imgIn.img_0[r][c] < th) ? 0 : 255;
        }

        imgOut.setImg(imgTh);
    }

    void padding(const Image& imgIn, Image& imgOut, int pad)
    {
        int rows = imgIn.size.rows;
        int columns = imgIn.size.columns;
        Image imgPad(imgIn.size + 2 * pad, imgIn.color);

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < columns; c++)
                pixelMove(imgIn, imgPad, Coordinate<int>(r, c), Coordinate<int>(r + pad, c + pad));

        for (int r = 0; r < rows + pad * 2; r++)
        {
            for (int c = 0; c < columns + pad * 2; c++)
            {
                if (r < pad && c < pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * pad - 1 - r, 2 * pad - 1 - c), Coordinate<int>(r, c));
                else if (r < pad && pad <= c && c < columns + pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * pad - 1 - r, c), Coordinate<int>(r, c));
                else if (r < pad && c >= columns + pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * pad - 1 - r, 2 * (columns + pad) - 1 - c), Coordinate<int>(r, c));
                else if (pad <= r && r < rows + pad && c < pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(r, 2 * pad - 1 - c), Coordinate<int>(r, c));
                else if (pad <= r && r < rows + pad && c >= columns + pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(r, 2 * (columns + pad) - 1 - c), Coordinate<int>(r, c));
                else if (r >= rows + pad && c < pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + pad) - 1 - r, 2 * pad - 1 - c), Coordinate<int>(r, c));
                else if (r >= rows + pad && pad <= c && c < columns + pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + pad) - 1 - r, c), Coordinate<int>(r, c));
                else if (r >= rows + pad && c >= columns + pad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + pad) - 1 - r, 2 * (columns + pad) - 1 - c), Coordinate<int>(r, c));
            }
        }

        imgOut.setImg(imgPad);
    }

    void padding(const Image& imgIn, Image& imgOut, int rowPad, int colPad)
    {
        int rows = imgIn.size.rows;
        int columns = imgIn.size.columns;
        Image imgPad(Size(rows + 2 * rowPad, columns + 2 * colPad), imgIn.color);

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < columns; c++)
                pixelMove(imgIn, imgPad, Coordinate<int>(r, c), Coordinate<int>(r + rowPad, c + colPad));

        for (int r = 0; r < rows + rowPad * 2; r++)
        {
            for (int c = 0; c < columns + colPad * 2; c++)
            {
                if (r < rowPad && c < colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * rowPad - 1 - r, 2 * colPad - 1 - c), Coordinate<int>(r, c));
                else if (r < rowPad && colPad <= c && c < columns + colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * rowPad - 1 - r, c), Coordinate<int>(r, c));
                else if (r < rowPad && c >= columns + colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * rowPad - 1 - r, 2 * (columns + colPad) - 1 - c), Coordinate<int>(r, c));
                else if (rowPad <= r && r < rows + rowPad && c < colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(r, 2 * colPad - 1 - c), Coordinate<int>(r, c));
                else if (rowPad <= r && r < rows + rowPad && c >= columns + colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(r, 2 * (columns + colPad) - 1 - c), Coordinate<int>(r, c));
                else if (r >= rows + rowPad && c < colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + rowPad) - 1 - r, 2 * colPad - 1 - c), Coordinate<int>(r, c));
                else if (r >= rows + rowPad && colPad <= c && c < columns + colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + rowPad) - 1 - r, c), Coordinate<int>(r, c));
                else if (r >= rows + rowPad && c >= columns + colPad)
                    pixelMove(imgPad, imgPad, Coordinate<int>(2 * (rows + rowPad) - 1 - r, 2 * (columns + colPad) - 1 - c), Coordinate<int>(r, c));
            }
        }

        imgOut.setImg(imgPad);
    }

    void PerspectiveTransformation(const Image& imgIn, Image& imgOut, Coordinate<int> xy[4], Coordinate<int> uv[4])
    {
        // Case 1
        double a, b, c, d, e, f, g, h;
        parameterPerspective(a, b, c, d, e, f, g, h, uv);
        std::vector<std::vector<double>> invMatrix(3, std::vector<double>(3));
        if (g == 0.0 || h == 0.0)   // affine
        {
            invMatrix[0][0] = a;    invMatrix[0][1] = b;    invMatrix[0][2] = c;
            invMatrix[1][0] = d;    invMatrix[1][1] = e;    invMatrix[1][2] = f;
            invMatrix[2][0] = 0.0;  invMatrix[2][1] = 0.0;  invMatrix[2][2] = 1.0;
            invMatrix = inverseMatrix(invMatrix);
        }

        // Case 2
        double aa, bb, cc, dd, ee, ff, gg, hh;
        parameterPerspective(aa, bb, cc, dd, ee, ff, gg, hh, xy);

        int newRows = std::max(uv[1].row, uv[2].row) + 1;
        int newCols = std::max(uv[2].column, uv[3].column) + 1;

        Image imageOut(Size(newRows, newCols), 0);
        for (int u = 0; u < newRows; u++)
            for (int v = 0; v < newCols; v++)
            {
                // Case 1
                if (g != 0.0 || h != 0.0)
                {
                    invMatrix[0][0] = a - g * u;    invMatrix[0][1] = b - h * u;    invMatrix[0][2] = c;
                    invMatrix[1][0] = d - g * v;    invMatrix[1][1] = e - h * v;    invMatrix[1][2] = f;
                    invMatrix[2][0] = 0.0;          invMatrix[2][1] = 0.0;          invMatrix[2][2] = 1.0;
                    invMatrix = inverseMatrix(invMatrix);
                }

                std::vector<std::vector<double>> uvMatrix(3, std::vector<double>(1));
                uvMatrix[0][0] = u;
                uvMatrix[1][0] = v;
                uvMatrix[2][0] = 1.0;

                std::vector<std::vector<double>> uuvvMatrix = multipleMatrix(invMatrix, uvMatrix);
                double uu = uuvvMatrix[0][0];
                double vv = uuvvMatrix[1][0];
                if (uu > 1 || uu < 0 || vv > 1 || vv < 0)
                    continue;

                // Case 2
                int x = (int)std::round((aa * uu + bb * vv + cc) / (gg * uu + hh * vv + 1));
                int y = (int)std::round((dd * uu + ee * vv + ff) / (gg * uu + hh * vv + 1));

                pixelMove(imgIn, imageOut, Coordinate<int>(x, y), Coordinate<int>(u, v));
            }

        imgOut.setImg(imageOut);
    }

    void PerspectiveTransformationFull(const Image& imgIn, Image& imgOut, Coordinate<int> xy[4], Coordinate<int> uv[4])
    {
        // Case 1
        double a, b, c, d, e, f, g, h;
        parameterPerspective(a, b, c, d, e, f, g, h, uv);
        std::vector<std::vector<double>> invMatrixCase1(3, std::vector<double>(3));
        invMatrixCase1[0][0] = a;    invMatrixCase1[0][1] = b;    invMatrixCase1[0][2] = c;
        invMatrixCase1[1][0] = d;    invMatrixCase1[1][1] = e;    invMatrixCase1[1][2] = f;
        invMatrixCase1[2][0] = g;    invMatrixCase1[2][1] = h;    invMatrixCase1[2][2] = 1.0;
        invMatrixCase1 = inverseMatrix(invMatrixCase1);

        // Case 2
        double aa, bb, cc, dd, ee, ff, gg, hh;
        parameterPerspective(aa, bb, cc, dd, ee, ff, gg, hh, xy);
        std::vector<std::vector<double>> invMatrixCase2(3, std::vector<double>(3));
        invMatrixCase2[0][0] = aa;    invMatrixCase2[0][1] = bb;    invMatrixCase2[0][2] = cc;
        invMatrixCase2[1][0] = dd;    invMatrixCase2[1][1] = ee;    invMatrixCase2[1][2] = ff;
        invMatrixCase2[2][0] = gg;    invMatrixCase2[2][1] = hh;    invMatrixCase2[2][2] = 1.0;
        invMatrixCase2 = inverseMatrix(invMatrixCase2);

        int minX = 0, minY = 0, maxX = 0, maxY = 0;
        for (int x = 0; x < imgIn.size.rows; x++)
            for (int y = 0; y < imgIn.size.columns; y++)
            {
                // Case 2
                if (gg != 0.0 || hh != 0.0)
                {
                    invMatrixCase2[0][0] = aa - gg * x;    invMatrixCase2[0][1] = bb - hh * x;    invMatrixCase2[0][2] = cc;
                    invMatrixCase2[1][0] = dd - gg * y;    invMatrixCase2[1][1] = ee - hh * y;    invMatrixCase2[1][2] = ff;
                    invMatrixCase2[2][0] = 0.0;            invMatrixCase2[2][1] = 0.0;            invMatrixCase2[2][2] = 1.0;
                    invMatrixCase2 = inverseMatrix(invMatrixCase2);
                }

                std::vector<std::vector<double>> xyMatrix(3, std::vector<double>(1));
                xyMatrix[0][0] = x;
                xyMatrix[1][0] = y;
                xyMatrix[2][0] = 1.0;

                std::vector<std::vector<double>> uuvvMatrix = multipleMatrix(invMatrixCase2, xyMatrix);
                double uu = uuvvMatrix[0][0];
                double vv = uuvvMatrix[1][0];

                // Case 1
                int u = (int)std::round((a * uu + b * vv + c) / (g * uu + h * vv + 1));
                int v = (int)std::round((d * uu + e * vv + f) / (g * uu + h * vv + 1));

                minX = std::min(minX, u);
                minY = std::min(minY, v);
                maxX = std::max(maxX, u);
                maxY = std::max(maxY, v);
            }

        int newRows = maxX - minX + 1;
        int newCols = maxY - minY + 1;
        Image imageOut(Size(newRows, newCols), 0);
        for (int u = minX; u < maxX + 1; u++)
            for (int v = minY; v < maxY + 1; v++)
            {
                // Case 1
                if (g != 0.0 || h != 0.0)
                {
                    invMatrixCase1[0][0] = a - g * u;    invMatrixCase1[0][1] = b - h * u;    invMatrixCase1[0][2] = c;
                    invMatrixCase1[1][0] = d - g * v;    invMatrixCase1[1][1] = e - h * v;    invMatrixCase1[1][2] = f;
                    invMatrixCase1[2][0] = 0.0;          invMatrixCase1[2][1] = 0.0;          invMatrixCase1[2][2] = 1.0;
                    invMatrixCase1 = inverseMatrix(invMatrixCase1);
                }

                std::vector<std::vector<double>> uvMatrix(3, std::vector<double>(1));
                uvMatrix[0][0] = u;
                uvMatrix[1][0] = v;
                uvMatrix[2][0] = 1.0;

                std::vector<std::vector<double>> uuvvMatrix = multipleMatrix(invMatrixCase1, uvMatrix);
                double uu = uuvvMatrix[0][0];
                double vv = uuvvMatrix[1][0];

                // Case 2
                int x = (int)std::round((aa * uu + bb * vv + cc) / (gg * uu + hh * vv + 1));
                int y = (int)std::round((dd * uu + ee * vv + ff) / (gg * uu + hh * vv + 1));
                if (x < 0 || x >= imgIn.size.rows || y < 0 || y >= imgIn.size.columns)
                    continue;

                pixelMove(imgIn, imageOut, Coordinate<int>(x, y), Coordinate<int>(u - minX, v - minY));
            }

        imgOut.setImg(imageOut);
    }

    void parameterPerspective(double& a, double& b, double& c, double& d, double& e, double& f, double& g, double& h, Coordinate<int> xy[4])
    {
        int x0 = xy[0].row, y0 = xy[0].column;
        int x1 = xy[1].row, y1 = xy[1].column;
        int x2 = xy[2].row, y2 = xy[2].column;
        int x3 = xy[3].row, y3 = xy[3].column;
        int xSigma = x0 - x1 + x2 - x3;
        int ySigma = y0 - y1 + y2 - y3;
        int xDelta1 = x1 - x2;
        int xDelta2 = x3 - x2;
        int yDelta1 = y1 - y2;
        int yDelta2 = y3 - y2;
        g = (double)(xSigma * yDelta2 - ySigma * xDelta2) / (xDelta1 * yDelta2 - yDelta1 * xDelta2);
        h = (double)(xDelta1 * ySigma - yDelta1 * xSigma) / (xDelta1 * yDelta2 - yDelta1 * xDelta2);
        a = x1 - x0 + g * x1;
        b = x3 - x0 + h * x3;
        c = x0;
        d = y1 - y0 + g * y1;
        e = y3 - y0 + h * y3;
        f = y0;
    }
}