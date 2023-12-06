#include "bmp.hpp"

void BitmapFileHeader::buf2param()
{
    int b0, b1, b2, b3;

    b0 = (this->buf[0] & 0xff);
    b1 = (this->buf[1] & 0xff);
    this->B = (uint8_t)b0;
    this->M = (uint8_t)b1;

    b0 = (this->buf[2] & 0xff);
    b1 = (this->buf[3] & 0xff);
    b2 = (this->buf[4] & 0xff);
    b3 = (this->buf[5] & 0xff);
    this->bfSize = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[6] & 0xff);
    b1 = (this->buf[7] & 0xff);
    this->bfReserved1 = (uint16_t)((b1 << 8) + b0);

    b0 = (this->buf[8] & 0xff);
    b1 = (this->buf[9] & 0xff);
    this->bfReserved2 = (uint16_t)((b1 << 8) + b0);

    b0 = (this->buf[10] & 0xff);
    b1 = (this->buf[11] & 0xff);
    b2 = (this->buf[12] & 0xff);
    b3 = (this->buf[13] & 0xff);
    this->bfOffBits = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
}

void BitmapFileHeader::param2buf()
{
    this->buf[0] = this->B;
    this->buf[1] = this->M;

    this->buf[2] = this->bfSize & 0xff;
    this->buf[3] = (this->bfSize >> 8) & 0xff;
    this->buf[4] = (this->bfSize >> 16) & 0xff;
    this->buf[5] = (this->bfSize >> 24) & 0xff;

    this->buf[6] = this->bfReserved1 & 0xff;
    this->buf[7] = (this->bfReserved1 >> 8) & 0xff;

    this->buf[8] = this->bfReserved2 & 0xff;
    this->buf[9] = (this->bfReserved2 >> 8) & 0xff;

    this->buf[10] = this->bfOffBits & 0xff;
    this->buf[11] = (this->bfOffBits >> 8) & 0xff;
    this->buf[12] = (this->bfOffBits >> 16) & 0xff;
    this->buf[13] = (this->bfOffBits >> 24) & 0xff;
}

void BitmapInfoHeader::buf2param()
{
    int b0, b1, b2, b3;

    b0 = (this->buf[0] & 0xff);
    b1 = (this->buf[1] & 0xff);
    b2 = (this->buf[2] & 0xff);
    b3 = (this->buf[3] & 0xff);
    this->biSize = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[4] & 0xff);
    b1 = (this->buf[5] & 0xff);
    b2 = (this->buf[6] & 0xff);
    b3 = (this->buf[7] & 0xff);
    this->biWidth = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[8] & 0xff);
    b1 = (this->buf[9] & 0xff);
    b2 = (this->buf[10] & 0xff);
    b3 = (this->buf[11] & 0xff);
    this->biHeight = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[12] & 0xff);
    b1 = (this->buf[13] & 0xff);
    this->biPlanes = (uint16_t)((b1 << 8) + b0);

    b0 = (this->buf[14] & 0xff);
    b1 = (this->buf[15] & 0xff);
    this->biBitCount = (uint16_t)((b1 << 8) + b0);

    b0 = (this->buf[16] & 0xff);
    b1 = (this->buf[17] & 0xff);
    b2 = (this->buf[18] & 0xff);
    b3 = (this->buf[19] & 0xff);
    this->biCompression = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[20] & 0xff);
    b1 = (this->buf[21] & 0xff);
    b2 = (this->buf[22] & 0xff);
    b3 = (this->buf[23] & 0xff);
    this->biSizeImage = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[24] & 0xff);
    b1 = (this->buf[25] & 0xff);
    b2 = (this->buf[26] & 0xff);
    b3 = (this->buf[27] & 0xff);
    this->biXPelsPerMeter = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[28] & 0xff);
    b1 = (this->buf[29] & 0xff);
    b2 = (this->buf[30] & 0xff);
    b3 = (this->buf[31] & 0xff);
    this->biYPelsPerMeter = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[32] & 0xff);
    b1 = (this->buf[33] & 0xff);
    b2 = (this->buf[34] & 0xff);
    b3 = (this->buf[35] & 0xff);
    this->biClrUsed = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

    b0 = (this->buf[36] & 0xff);
    b1 = (this->buf[37] & 0xff);
    b2 = (this->buf[38] & 0xff);
    b3 = (this->buf[39] & 0xff);
    this->biClrImportant = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
}

void BitmapInfoHeader::param2buf()
{
    this->buf[0] = this->biSize & 0xff;
    this->buf[1] = (this->biSize >> 8) & 0xff;
    this->buf[2] = (this->biSize >> 16) & 0xff;
    this->buf[3] = (this->biSize >> 24) & 0xff;

    this->buf[4] = this->biWidth & 0xff;
    this->buf[5] = (this->biWidth >> 8) & 0xff;
    this->buf[6] = (this->biWidth >> 16) & 0xff;
    this->buf[7] = (this->biWidth >> 24) & 0xff;

    this->buf[8] = this->biHeight & 0xff;
    this->buf[9] = (this->biHeight >> 8) & 0xff;
    this->buf[10] = (this->biHeight >> 16) & 0xff;
    this->buf[11] = (this->biHeight >> 24) & 0xff;

    this->buf[12] = this->biPlanes & 0xff;
    this->buf[13] = (this->biPlanes >> 8) & 0xff;

    this->buf[14] = this->biBitCount & 0xff;
    this->buf[15] = (this->biBitCount >> 8) & 0xff;

    this->buf[16] = this->biCompression & 0xff;
    this->buf[17] = (this->biCompression >> 8) & 0xff;
    this->buf[18] = (this->biCompression >> 16) & 0xff;
    this->buf[19] = (this->biCompression >> 24) & 0xff;

    this->buf[20] = this->biSizeImage & 0xff;
    this->buf[21] = (this->biSizeImage >> 8) & 0xff;
    this->buf[22] = (this->biSizeImage >> 16) & 0xff;
    this->buf[23] = (this->biSizeImage >> 24) & 0xff;

    this->buf[24] = this->biXPelsPerMeter & 0xff;
    this->buf[25] = (this->biXPelsPerMeter >> 8) & 0xff;
    this->buf[26] = (this->biXPelsPerMeter >> 16) & 0xff;
    this->buf[27] = (this->biXPelsPerMeter >> 24) & 0xff;

    this->buf[28] = this->biYPelsPerMeter & 0xff;
    this->buf[29] = (this->biYPelsPerMeter >> 8) & 0xff;
    this->buf[30] = (this->biYPelsPerMeter >> 16) & 0xff;
    this->buf[31] = (this->biYPelsPerMeter >> 24) & 0xff;

    this->buf[32] = this->biClrUsed & 0xff;
    this->buf[33] = (this->biClrUsed >> 8) & 0xff;
    this->buf[34] = (this->biClrUsed >> 16) & 0xff;
    this->buf[35] = (this->biClrUsed >> 24) & 0xff;

    this->buf[36] = this->biClrImportant & 0xff;
    this->buf[37] = (this->biClrImportant >> 8) & 0xff;
    this->buf[38] = (this->biClrImportant >> 16) & 0xff;
    this->buf[39] = (this->biClrImportant >> 24) & 0xff;
}

BMP::~BMP()
{
    this->delete_image_data();
}

void BMP::open_img(const char* filename, std::vector<std::vector<uint8_t>>& img_R, std::vector<std::vector<uint8_t>>& img_G, std::vector<std::vector<uint8_t>>& img_B)
{
    FILE* fp;
    if ((fp = std::fopen(filename, "rb")) == NULL)
    {
        std::printf("Couldn't find file %s.\n", filename);
        std::exit(1);
    }

    std::fread(this->file_header.buf, sizeof(uint8_t), 14, fp);
    this->file_header.buf2param();

    std::fread(this->info_header.buf, sizeof(uint8_t), 40, fp);
    this->info_header.buf2param();

    if (this->info_header.biBitCount == 8)
    {
        std::fread(this->rgbquad.buf, sizeof(uint8_t), sizeof(this->rgbquad.buf), fp);
        int size = ((this->info_header.biWidth + 3) & (~3)) * this->info_header.biHeight;
        this->delete_image_data();
        this->image_data = new uint8_t[size];
        std::fread(this->image_data, sizeof(uint8_t), size, fp);
    }
    else if (this->info_header.biBitCount == 24)
    {
        int size = ((this->info_header.biWidth * 3 + 3) & (~3)) * this->info_header.biHeight;
        this->delete_image_data();
        this->image_data = new uint8_t[size];
        std::fread(this->image_data, sizeof(uint8_t), size, fp);
    }
    else
    {
        std::printf("Not supported format!\n");
        std::exit(1);
    }

    std::fclose(fp);

    img_data_to_vector(img_R, img_G, img_B);
}

void BMP::save_img(const char* filename, const std::vector<std::vector<uint8_t>>& img_R, const std::vector<std::vector<uint8_t>>& img_G, const std::vector<std::vector<uint8_t>>& img_B)
{
    FILE* fp;
    if ((fp = std::fopen(filename, "wb")) == NULL)
    {
        std::printf("Couldn't save file %s.\n", filename);
        std::exit(1);
    }

    this->file_header.B = 'B';
    this->file_header.M = 'M';
    int height = (int)img_R.size();
    int width = (int)img_R[0].size();
    int size = ((width * 3 + 3) & (~3)) * height;
    this->file_header.bfSize = 54 + size;
    this->file_header.bfReserved1 = 0;
    this->file_header.bfReserved2 = 0;
    this->file_header.bfOffBits = 54;
    this->file_header.param2buf();
    std::fwrite(this->file_header.buf, sizeof(uint8_t), 14, fp);

    this->info_header.biSize = 40;
    this->info_header.biWidth = width;
    this->info_header.biHeight = height;
    this->info_header.biPlanes = 1;
    this->info_header.biBitCount = 24;
    this->info_header.biCompression = 0;
    this->info_header.biSizeImage = 0;
    this->info_header.biXPelsPerMeter = 3779;
    this->info_header.biYPelsPerMeter = 3779;
    this->info_header.biClrUsed = 0;
    this->info_header.biClrImportant = 0;
    this->info_header.param2buf();
    std::fwrite(this->info_header.buf, sizeof(uint8_t), 40, fp);

    this->delete_image_data();
    this->image_data = new uint8_t[size];
    vector_to_img_data(img_R, img_G, img_B);
    std::fwrite(this->image_data, sizeof(uint8_t), size, fp);

    std::fclose(fp);
}

void BMP::img_data_to_vector(std::vector<std::vector<uint8_t>>& img_R, std::vector<std::vector<uint8_t>>& img_G, std::vector<std::vector<uint8_t>>& img_B)
{
    int width = this->info_header.biWidth;
    int height = this->info_header.biHeight;
    img_R.resize(height);
    img_G.resize(height);
    img_B.resize(height);
    for (int y = 0; y < height; y++)
    {
        img_R[y].resize(width);
        img_G[y].resize(width);
        img_B[y].resize(width);
    }
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            uint8_t r, g, b;
            this->get_bmp_pixel(x, y, r, g, b);
            img_R[height - 1 - y][x] = r;
            img_G[height - 1 - y][x] = g;
            img_B[height - 1 - y][x] = b;
        }
    }
}

void BMP::vector_to_img_data(const std::vector<std::vector<uint8_t>>& img_R, const std::vector<std::vector<uint8_t>>& img_G, const std::vector<std::vector<uint8_t>>& img_B)
{
    int width = this->info_header.biWidth;
    int height = this->info_header.biHeight;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int r = img_R[height - 1 - y][x];
            int g = img_G[height - 1 - y][x];
            int b = img_B[height - 1 - y][x];
            set_bmp_pixel(x, y, r, g, b);
        }
    }
}

void BMP::delete_image_data()
{
    delete[] this->image_data;
    this->image_data = nullptr;
}

void BMP::get_bmp_pixel(int x, int y, uint8_t& pixel_r, uint8_t& pixel_g, uint8_t& pixel_b)
{
    int width, height;
    int offset;

    if (this->info_header.biBitCount == 8)
    {
        width = this->info_header.biWidth;
        height = this->info_header.biHeight;
        offset = y * ((width + 3) & (~3)) + x;
        pixel_b = *(this->image_data + offset);
        pixel_g = pixel_b;
        pixel_r = pixel_b;
    }
    else if (this->info_header.biBitCount == 24)
    {
        width = this->info_header.biWidth;
        height = this->info_header.biHeight;
        offset = y * ((width * 3 + 3) & (~3)) + x * 3;
        pixel_b = *(this->image_data + offset);
        pixel_g = *(this->image_data + offset + 1);
        pixel_r = *(this->image_data + offset + 2);
    }
    else
    {
        std::printf("Not supported format!\n");
        std::exit(1);
    }
}

void BMP::set_bmp_pixel(int x, int y, uint8_t pixel_r, uint8_t pixel_g, uint8_t pixel_b)
{
    int width, height;
    int offset;

    if (this->info_header.biBitCount == 8)
    {
        width = this->info_header.biWidth;
        height = this->info_header.biHeight;
        offset = y * ((width + 3) & (~3)) + x;
        *(this->image_data + offset) = pixel_b;
    }
    else if (this->info_header.biBitCount == 24)
    {
        width = this->info_header.biWidth;
        height = this->info_header.biHeight;
        offset = y * ((width * 3 + 3) & (~3)) + x * 3;
        *(this->image_data + offset) = pixel_b;
        *(this->image_data + offset + 1) = pixel_g;
        *(this->image_data + offset + 2) = pixel_r;
    }
    else
    {
        std::printf("Not supported format!\n");
        std::exit(1);
    }
}
