#pragma once
#include <string>
#include <vector>

struct Color {
    double r, g, b;

    Color();

    Color(double r, double g, double b);

    Color(const Color &other);

    ~Color();

    bool operator==(Color col) const;
};

class Image {
public:
    Image(int width, int height, std::vector<std::vector<Color>> colors);

    Image(int width, int height);

    ~Image();

    Color GetColor(int x, int y) const;

    void SetColor(const Color &color, int x, int y);

    int GetWidth() const;

    int GetHeight() const;

    bool operator==(const Image &other) const;

    void Input(const char *path);

    void Export(const char *path) const;

    int picture_width;
    int picture_height;
    std::vector<std::vector<Color>> values;
};
