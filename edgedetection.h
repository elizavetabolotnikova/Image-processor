#include "filters.h"

void EdgeDetectionFilter(Image& image, float threshold);

class EdgeDetection : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~EdgeDetection() override = default;
};
