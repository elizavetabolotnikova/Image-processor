#include "filters.h"

void SharpeningFilter(Image& image);

class Sharpening : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~Sharpening() override = default;
};
