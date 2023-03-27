#include "filters.h"

void CropFilter(Image &copy, int x, int y);

class Crop : public Filter {
public:
    void ApplyFilter(Image &image, std::vector<std::string>) override;

    ~Crop() override = default;
};
