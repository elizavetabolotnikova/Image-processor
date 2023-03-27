#include "input_and_output.h"
#include <string>
#include "negative.h"
#include "grayscale.h"
#include "sharpening.h"
#include "crop.h"
#include "edgedetection.h"
#include "myfilter.h"
#include "gaussianblur.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Filters list:" << std::endl;
        std::cout << "-crop обрезает картинку, принимая два параметра: высота и ширина желаемой картинки" << std::endl;
        std::cout << "-gs GrayScale фильтр" << std::endl;
        std::cout << "-neg Negative фильтр" << std::endl;
        std::cout << "-sharp увеличивает резкость" << std::endl;
        std::cout << "-edge Edge Detection принимает параметр threshold" << std::endl;
        std::cout << "-blur принимает параметр сигма,размывает картинку" << std::endl;
        std::cout << "-four четырехцветный фильтр" << std::endl;
        return 0;
    }
    if (argc == 2) {
        throw std::runtime_error("You specified the wrong path");
    }
    Image image(0, 0);
    image.Input(argv[1]);
    for (int i = 3; i < argc; ++i) {
        std::string argument = argv[i];
        if (argument == "-crop") {
            if (i > argc - 3) {
                throw std::runtime_error("Runtime error");
            }
            try {
                std::stoi(argv[i + 1]);
                std::stoi(argv[i + 2]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Command line argument is not correct");
            }
            Crop copy;
            copy.ApplyFilter(image, {argv[i + 1], argv[i + 2]});
        } else if (argument == "-gs") {
            GrayScale copy;
            copy.ApplyFilter(image, {});
        } else if (argument == "-neg") {
            Negative copy;
            copy.ApplyFilter(image, {});
        } else if (argument == "-sharp") {
            Sharpening copy;
            copy.ApplyFilter(image, {});
        } else if (argument == "-edge") {
            if (i > argc - 2) {
                throw std::runtime_error("Runtime error");
            }
            try {
                std::stof(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Command line argument is not correct");
            }
            EdgeDetection copy;
            copy.ApplyFilter(image, {argv[i + 1]});
        } else if (argument == "-blur") {
            if (i > argc - 2) {
                throw std::runtime_error("Runtime error");
            }
            try {
                std::stof(argv[i + 1]);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Command line argument is not correct");
            }
            Gaussianblur copy;
            copy.ApplyFilter(image, {argv[i + 1]});
        } else if (argument == "-four") {
            Four copy;
            copy.ApplyFilter(image, {});
        }
    }
    image.Export(argv[2]);
}
