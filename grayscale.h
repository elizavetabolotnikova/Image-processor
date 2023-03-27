#include "filters.h"

void FilterG(Image& image);

class GrayScale : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~GrayScale() override = default;
};