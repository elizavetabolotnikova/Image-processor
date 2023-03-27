#include "myfilter.h"
void FourFilter(Image& image) {

    int w = image.picture_width;
    int h = image.picture_height;
    Image copy(w, h);
    copy = Filter::ChangeShape(image);
    for (size_t i = 0; i < h / 2; ++i) {
        for (size_t j = 0; j < w / 2; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].b + (2) * copy.values[i + 2][j + 2].b +
                                    (2) * copy.values[i + 1][j].b + (1) * copy.values[i][j + 1].b +
                                    -8 * copy.values[i + 1][j + 1].b + (1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (1) * copy.values[i][j].b +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].b + (1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].g + (2) * copy.values[i + 2][j + 2].g +
                                    (2) * copy.values[i + 1][j].g + (1) * copy.values[i][j + 1].g +
                                    -8 * copy.values[i + 1][j + 1].g + (1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (1) * copy.values[i][j].g +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].g + (1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].r + (2) * copy.values[i + 2][j + 2].r +
                                    (3) * copy.values[i + 1][j].r + (1) * copy.values[i][j + 1].r +
                                    -8 * copy.values[i + 1][j + 1].r + (1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (1) * copy.values[i][j].r +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].r + (1) * copy.values[i + 1][j + 2].r)));
        }
    }
    for (size_t i = 0; i < h / 2; ++i) {
        for (size_t j = w / 2; j < w; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].b + (1) * copy.values[i + 2][j + 2].b +
                                    (1) * copy.values[i + 1][j].b + (1) * copy.values[i][j + 1].b +
                                    -8 * copy.values[i + 1][j + 1].b + (1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (1) * copy.values[i][j].b +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].b + (1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].g + (2) * copy.values[i + 2][j + 2].g +
                                    (3) * copy.values[i + 1][j].g + (1) * copy.values[i][j + 1].g +
                                    -8 * copy.values[i + 1][j + 1].g + (1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (1) * copy.values[i][j].g +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].g + (1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].r + (2) * copy.values[i + 2][j + 2].r +
                                    (3) * copy.values[i + 1][j].r + (1) * copy.values[i][j + 1].r +
                                    -8 * copy.values[i + 1][j + 1].r + (1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (1) * copy.values[i][j].r +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].r + (1) * copy.values[i + 1][j + 2].r)));
        }
    }
    for (size_t i = image.picture_height / 2; i < image.picture_height; ++i) {
        for (size_t j = image.picture_width / 2; j < image.picture_width; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].b + (1) * copy.values[i + 2][j + 2].b +
                                    (2) * copy.values[i + 1][j].b + (1) * copy.values[i][j + 1].b +
                                    -8 * copy.values[i + 1][j + 1].b + (1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (1) * copy.values[i][j].b +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].b + (1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].g + (2) * copy.values[i + 2][j + 2].g +
                                    (3) * copy.values[i + 1][j].g + (1) * copy.values[i][j + 1].g +
                                    -8 * copy.values[i + 1][j + 1].g + (1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (1) * copy.values[i][j].g +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].g + (1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].r + (1) * copy.values[i + 2][j + 2].r +
                                    (1) * copy.values[i + 1][j].r + (1) * copy.values[i][j + 1].r +
                                    -8 * copy.values[i + 1][j + 1].r + (1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (1) * copy.values[i][j].r +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].r + (1) * copy.values[i + 1][j + 2].r)));
        }
    }
    for (size_t i = image.picture_height / 2; i < image.picture_height; ++i) {
        for (size_t j = 0; j < image.picture_width / 2; ++j) {
            image.values[i][j].b = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].b + (2) * copy.values[i + 2][j + 2].b +
                                    (3) * copy.values[i + 1][j].b + (1) * copy.values[i][j + 1].b +
                                    -8 * copy.values[i + 1][j + 1].b + (1) * copy.values[i + 2][j + 1].b +  // NOLINT
                                    (1) * copy.values[i][j].b +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].b + (1) * copy.values[i + 1][j + 2].b)));
            image.values[i][j].g = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].g + (2) * copy.values[i + 2][j + 2].g +
                                    (2) * copy.values[i + 1][j].g + (1) * copy.values[i][j + 1].g +
                                    -8 * copy.values[i + 1][j + 1].g + (1) * copy.values[i + 2][j + 1].g +  // NOLINT
                                    (1) * copy.values[i][j].g +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].g + (1) * copy.values[i + 1][j + 2].g)));
            image.values[i][j].r = std::min(
                1.0, std::max(0.0, ((1) * copy.values[i + 2][j].r + (1) * copy.values[i + 2][j + 2].r +
                                    (1) * copy.values[i + 1][j].r + (1) * copy.values[i][j + 1].r +
                                    -8 * copy.values[i + 1][j + 1].r + (1) * copy.values[i + 2][j + 1].r +  // NOLINT
                                    (1) * copy.values[i][j].r +                                             // NOLINT
                                    +(1) * copy.values[i][j + 2].r + (1) * copy.values[i + 1][j + 2].r)));
        }
    }
}
void Four::ApplyFilter(Image& image, std::vector<std::string>) {
    FourFilter(image);
}
