#include "filters.h"

void FilterN(Image& image);

class Negative : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~Negative() override = default;
};
