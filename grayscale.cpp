#include "input_and_output.h"
#include "grayscale.h"

void FilterG(Image &copy) {
    for (size_t i = 0; i < copy.picture_height; ++i) {
        for (size_t j = 0; j < copy.picture_width; ++j) {
            float color = copy.values[i][j].r * 299 / 1000 + copy.values[i][j].g * 587 / 1000 +  // NOLINT
                          copy.values[i][j].b * 114 / 1000;                                      // NOLINT
            copy.values[i][j].b = color;
            copy.values[i][j].g = color;
            copy.values[i][j].r = color;
        }
    }
}

void GrayScale::ApplyFilter(Image &image, std::vector<std::string>) {
    FilterG(image);
}
