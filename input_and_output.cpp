#include "input_and_output.h"
#include <iostream>
#include <fstream>
#include <utility>

Color::Color() : r(0), g(0), b(0){};

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {
}

Color::Color(const Color &other) : r(other.r), g(other.g), b(other.b){};

Color::~Color() {
}

bool Color::operator==(Color colour) const {
    if (r == colour.r && b == colour.b && g == colour.g) {
        return true;
    }
    return false;
}

Image::Image(int width, int height) {
    picture_width = width;
    picture_height = height;
    Color help(0, 0, 0);
    values.resize(height);
    for (size_t i = 0; i < height; ++i) {
        values[i].resize(width);
        for (size_t j = 0; j < width; ++j) {
            values[i][j] = help;
        }
    }
};

Image::Image(int width, int height, std::vector<std::vector<Color>> colors)
    : picture_width(width), picture_height(height), values(std::move(colors)){};

Image::~Image() = default;

Color Image::GetColor(int x, int y) const {
    return values[y][x];
}

void Image::SetColor(const Color &color, int x, int y) {
    values[y][x].r = color.r;
    values[y][x].g = color.g;
    values[y][x].b = color.b;
}

bool Image::operator==(const Image &other) const {
    if (picture_width != other.picture_width || picture_height != other.picture_height) {
        return false;
    }
    return values == other.values;
}

void Image::Input(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return;
    }
    const int file_header_size = 14;
    const int information_header_size = 40;
    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "This is not a bmp image" << std::endl;
        f.close();
        return;
    }
    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);
    picture_width = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) +    // NOLINT
                    (information_header[7] << 24);                                                            // NOLINT
    picture_height = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) +  // NOLINT
                     (information_header[11] << 24);                                                          // NOLINT
    Color help(0, 0, 0);
    values.resize(picture_height);
    for (size_t i = 0; i < picture_height; ++i) {
        values[i].resize(picture_width);
        for (size_t j = 0; j < picture_width; ++j) {
            values[i][j] = help;
        }
    }
    const int paddings = ((4 - (picture_width * 3) % 4) % 4);
    for (int y = 0; y < picture_height; y++) {
        for (int x = 0; x < picture_width; x++) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);
            values[y][x].r = static_cast<double>(color[2]) / 255.0f;  // NOLINT
            values[y][x].g = static_cast<double>(color[1]) / 255.0f;  // NOLINT
            values[y][x].b = static_cast<double>(color[0]) / 255.0f;  // NOLINT
        }
        f.ignore(paddings);
    }
    f.close();
};

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be opened\n";
        return;
    }
    unsigned char bmp[3] = {0, 0, 0};
    const int paddings = ((4 - (picture_width * 3) % 4) % 4);
    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size =
        file_header_size + information_header_size + picture_width * picture_height * 3 + paddings * picture_width;
    unsigned char file_header[file_header_size];
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;                               // NOLINT
    file_header[4] = file_size >> 16;                              // NOLINT
    file_header[5] = file_size >> 24;                              // NOLINT
    file_header[10] = file_header_size + information_header_size;  // NOLINT
    for (size_t i = 6; i <= 13; i++) {                             // NOLINT
        if (i % 10 != 0) {                                         // NOLINT
            file_header[i] = 0;
        }
    }
    unsigned char information_header[information_header_size];
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    information_header[4] = picture_width;
    information_header[5] = picture_width >> 8;     // NOLINT
    information_header[6] = picture_width >> 16;    // NOLINT
    information_header[7] = picture_width >> 24;    // NOLINT
    information_header[8] = picture_height;         // NOLINT
    information_header[9] = picture_height >> 8;    // NOLINT
    information_header[10] = picture_height >> 16;  // NOLINT
    information_header[11] = picture_height >> 24;  // NOLINT
    information_header[12] = 1;                     // NOLINT
    information_header[13] = 0;                     // NOLINT
    information_header[14] = 24;                    // NOLINT
    for (size_t i = 15; i <= 39; i++) {             // NOLINT
        information_header[i] = 0;
    }
    f.write(reinterpret_cast<char *>(file_header), file_header_size);
    f.write(reinterpret_cast<char *>(information_header), information_header_size);
    for (int y = 0; y < picture_height; y++) {
        for (int x = 0; x < picture_width; x++) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);  // NOLINT
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);  // NOLINT
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);  // NOLINT
            unsigned char color[] = {b, g, r};
            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp), paddings);
    }
    f.close();
}
