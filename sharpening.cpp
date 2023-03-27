#include "sharpening.h"
#include <algorithm>
Image Filter::ChangeShape(Image &image) {
    Image copy(image.picture_width + 2, image.picture_height + 2);
    for (size_t i = 1; i < copy.picture_width - 1; ++i) {
        copy.values[0][i] = image.values[0][i - 1];  // нижняя
    }
    for (size_t i = 1; i < copy.picture_width - 1; ++i) {
        copy.values[copy.picture_height - 1][i] = image.values[image.picture_height - 1][i - 1];  // верх
    }
    for (size_t i = 1; i < copy.picture_height - 1; ++i) {
        copy.values[i][copy.picture_width - 1] = image.values[i - 1][image.picture_width - 1];  // справа
    }
    for (size_t i = 1; i < copy.picture_height - 1; ++i) {
        copy.values[i][0] = image.values[i - 1][0];  // слева
    }
    for (size_t i = 1; i < copy.picture_height - 1; ++i) {
        for (size_t j = 1; j < copy.picture_width - 1; ++j) {
            copy.values[i][j] = image.values[i - 1][j - 1];
        }
    }
    return copy;
}
void SharpeningFilter(Image &image) {
    int w = image.picture_width;
    int h = image.picture_height;
    Image copy(w, h);
    copy = Filter::ChangeShape(image);
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].b + (-1) * copy.values[i][j + 1].b +
                                    5 * copy.values[i + 1][j + 1].b + (-1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].g + (-1) * copy.values[i][j + 1].g +
                                    5 * copy.values[i + 1][j + 1].g + (-1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].r + (-1) * copy.values[i][j + 1].r +
                                    5 * copy.values[i + 1][j + 1].r + (-1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].r)));
        }
    }
}
void Sharpening::ApplyFilter(Image &image, std::vector<std::string>) {
    SharpeningFilter(image);
}