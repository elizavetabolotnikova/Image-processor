#include "edgedetection.h"
#include "grayscale.h"

void EdgeDetectionFilter(Image &image, float threshold) {
    GrayScale helper;
    helper.ApplyFilter(image, {});
    int w = image.picture_width;
    int h = image.picture_height;
    Image copy(w, h);
    copy = Filter::ChangeShape(image);
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].b + (-1) * copy.values[i][j + 1].b +
                                    4 * copy.values[i + 1][j + 1].b + (-1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].g + (-1) * copy.values[i][j + 1].g +
                                    4 * copy.values[i + 1][j + 1].g + (-1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((-1) * copy.values[i + 1][j].r + (-1) * copy.values[i][j + 1].r +
                                    4 * copy.values[i + 1][j + 1].r + (-1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (-1) * copy.values[i + 1][j + 2].r)));
        }
    }
    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            if (image.values[i][j].b > threshold) {
                image.values[i][j].b = 1;
            } else {
                image.values[i][j].b = 0;
            }
            if (image.values[i][j].g > threshold) {
                image.values[i][j].g = 1;
            } else {
                image.values[i][j].g = 0;
            }
            if (image.values[i][j].r > threshold) {
                image.values[i][j].r = 1;
            } else {
                image.values[i][j].r = 0;
            }
        }
    }
}

void EdgeDetection::ApplyFilter(Image &image, std::vector<std::string> v) {
    EdgeDetectionFilter(image, std::stof(v[0]));
}
