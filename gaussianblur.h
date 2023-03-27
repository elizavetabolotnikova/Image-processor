#include "filters.h"

void GaussianblurFilter(Image& image, float sigma);

class Gaussianblur : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~Gaussianblur() override = default;
};