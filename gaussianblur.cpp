#include "gaussianblur.h"
#include "math.h"
#include "cmath"
#include <algorithm>
#include <vector>
void GaussianblurFilter(Image& image, float sigma) {
    float red_result = 0.0f;
    float blue_result = 0.0f;
    float green_result = 0.0f;

    std::vector<float> vector;
    auto coef = std::pow((1 / (static_cast<float>(2 * M_PI * sigma * sigma))), 0.5);  // NOLINT
    for (auto i = static_cast<int>(std::ceil(sigma * 3)); i > -static_cast<int>(std::ceil(sigma * 3)); --i) {
        vector.push_back(static_cast<float>(std::pow(M_E, static_cast<float>(-i * i) / (2 * sigma * sigma))));
    }
    Image copy(image.picture_width, image.picture_height);
    for (auto i = 0; i < image.picture_height; i++) {
        for (auto j = 0; j < image.picture_width; j++) {
            copy.values[i][j] = image.values[i][j];
        }
    }
    for (auto y0 = 0; y0 < image.picture_height; y0++) {
        for (auto x0 = 0; x0 < image.picture_width; x0++) {
            red_result = 0.0f;
            blue_result = 0.0f;
            green_result = 0.0f;
            for (auto y = static_cast<int>((-1) * std::ceil(sigma * 3)); y < static_cast<int>(std::ceil(sigma * 3));
                 y++) {
                auto normalize_y = std::min(image.picture_height - 1, std::max(0, y + y0));
                red_result += static_cast<float>(vector[y - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                              static_cast<float>(image.values[normalize_y][x0].r) * static_cast<float>(coef);
                blue_result += static_cast<float>(vector[y - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                               static_cast<float>(image.values[normalize_y][x0].b) * static_cast<float>(coef);
                green_result += static_cast<float>(vector[y - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                                static_cast<float>(image.values[normalize_y][x0].g) * static_cast<float>(coef);
            }
            copy.values[y0][x0].r = red_result;
            copy.values[y0][x0].b = blue_result;
            copy.values[y0][x0].g = green_result;
        }
    }
    for (auto y0 = 0; y0 < image.picture_height; y0++) {
        for (auto x0 = 0; x0 < image.picture_width; x0++) {
            red_result = 0.0f;
            blue_result = 0.0f;
            green_result = 0.0f;
            for (auto x = static_cast<int>((-1) * std::ceil(sigma * 3)); x < static_cast<int>(std::ceil(sigma * 3));
                 x++) {
                auto normalize_x = std::min(image.picture_width - 1, std::max(0, x + x0));
                red_result += static_cast<float>(vector[x - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                              static_cast<float>(copy.values[y0][normalize_x].r) * static_cast<float>(coef);
                blue_result += static_cast<float>(vector[x - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                               static_cast<float>(copy.values[y0][normalize_x].b) * static_cast<float>(coef);
                green_result += static_cast<float>(vector[x - static_cast<int>((-1) * std::ceil(sigma * 3))]) *
                                static_cast<float>(copy.values[y0][normalize_x].g) * static_cast<float>(coef);
            }
            image.values[y0][x0].r = red_result;
            image.values[y0][x0].b = blue_result;
            image.values[y0][x0].g = green_result;
        }
    }
}

void Gaussianblur::ApplyFilter(Image& image, std::vector<std::string> v) {
    GaussianblurFilter(image, std::stof(v[0]));
}