#include "crop.h"
#include <string>

void CropFilter(Image &copy, int x, int y) {
    int normalize_x = std::min(x, copy.picture_width);
    int normalize_y = std::min(y, copy.picture_height);
    Image tmp(normalize_x, normalize_y);
    for (size_t i = (copy.picture_height - normalize_y); i < copy.picture_height; ++i) {
        for (size_t j = 0; j < normalize_x; ++j) {
            tmp.values[i - copy.picture_height + normalize_y][j] = copy.values[i][j];
        }
    }
    copy = tmp;
}

void Crop::ApplyFilter(Image &image, std::vector<std::string> v) {
    CropFilter(image, std::stoi(v[0]), std::stoi(v[1]));
}