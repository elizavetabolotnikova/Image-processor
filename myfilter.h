#include "filters.h"

void FourFilter(Image& image);

class Four : public Filter {
public:
    void ApplyFilter(Image& image, std::vector<std::string>) override;
    ~Four() override = default;
};