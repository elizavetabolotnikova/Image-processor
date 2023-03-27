#include "input_and_output.h"
#include "negative.h"

void FilterN(Image &copy) {
    for (size_t i = 0; i < copy.picture_height; ++i) {
        for (size_t j = 0; j < copy.picture_width; ++j) {
            copy.values[i][j].b = 1 - copy.values[i][j].b;
            copy.values[i][j].g = 1 - copy.values[i][j].g;
            copy.values[i][j].r = 1 - copy.values[i][j].r;
        }
    }
}

void Negative::ApplyFilter(Image &image, std::vector<std::string>) {
    FilterN(image);
}