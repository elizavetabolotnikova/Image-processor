#include "input_and_output.h"

#pragma once

class Filter {
public:
    virtual void ApplyFilter(Image& image, std::vector<std::string>) = 0;
    static Image ChangeShape(Image& image);
    virtual ~Filter(){};
};