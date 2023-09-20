#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>
#include <time.h>
#include <algorithm>
#include <numeric>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "Lib/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Lib/stb/stb_image_write.h"

#define N8_MENU_X 890
#define N8_MENU_Y 240
#define N8_MENU_W 494
#define N8_MENU_H 479
#define BLACK     15000000

struct RGB
{
    uint8_t r, g, b;
};

struct BGR
{
    uint8_t b, g, r;
};

struct RGBSum
{
    uint64_t r, g, b;
};

int alive = 1;

bool is_n8_menu_open(uint64_t n8_menu_slice_sum_r, uint64_t n8_menu_slice_sum_g, uint64_t n8_menu_slice_sum_b)
{
    return false;
}

float average(std::vector<uint8_t> const& v)
{
    if (v.empty()) {
        return 0;
    }
    auto const count = static_cast<uint8_t>(v.size());
    return std::reduce(v.begin(), v.end()) / count;
}

int main()
{
    cv::VideoCapture capture(0);
    cv::Mat frame;

    int alive = 1;
    struct timespec requested = {0};
    requested.tv_nsec = 4000000L;

    int _x = 897;
    int _y = 260;
    int _w = 507;
    int _h = 492;

    int _min = -1;
    int _max = -1;

    int _BLACK     = 15000000;
    int _N8MENUMIN = 68388555;
    int _N8MENUMAX = 68543359;
    time_t _prev_press = 0;

    int frame_count = 0;

    while (alive)
    {
        capture.read(frame);

        char filename[128] = {0};
        char pixels[frame.rows * frame.cols * 3] = {0};

        uint64_t sum = 0;
        int color_count = 0;

        std::vector<uint8_t> reds;
        std::vector<uint8_t> greens;
        std::vector<uint8_t> blues;

        reds.reserve(frame.rows * frame.cols);
        greens.reserve(frame.rows * frame.cols);
        blues.reserve(frame.rows * frame.cols);

        std::vector<RGB> texture;

        for (int i = 0, j = 0; i < frame.rows * frame.cols * 3; i += 3, j++)
        {
            int x = j % frame.cols;
            int y = j / frame.cols;

            texture.push_back({frame.data[i+2], frame.data[i+1], frame.data[i]});

            if (x >= N8_MENU_X && x <= (N8_MENU_X + N8_MENU_W)) {
                if (y >= N8_MENU_Y && y <= (N8_MENU_Y + N8_MENU_H)) {
                    std::string value;

                    value += std::to_string(x);
                    value += ":";
                    value += std::to_string(y);
                    value += ":";
                    value += std::to_string(frame.data[i+2]);
                    value += "\n";

                    reds.push_back(frame.data[i+2]);
                    greens.push_back(frame.data[i+1]);
                    blues.push_back(frame.data[i]);

                    pixels[i+2] = frame.data[i];
                    pixels[i+1] = frame.data[i+1];
                    pixels[i] = frame.data[i+2];
                }
            }
        }

        std::cout << (int)*std::min_element(reds.begin(), reds.end()) << std::endl;
        std::cout << (int)*std::max_element(reds.begin(), reds.end()) << std::endl << std::endl;

        std::cout << (int)*std::min_element(greens.begin(), greens.end()) << std::endl;
        std::cout << (int)*std::max_element(greens.begin(), greens.end()) << std::endl << std::endl;

        std::cout << (int)*std::min_element(blues.begin(), blues.end()) << std::endl;
        std::cout << (int)*std::max_element(blues.begin(), blues.end()) << std::endl << std::endl;

        for (int i = _x; i < _x + _w; i++) {
            for (int j = _y; j < _y + _h; j++) {
                sum += ((BGR*)frame.data)[j * frame.cols + i].r + ((BGR*)frame.data)[j * frame.cols + i].g + ((BGR*)frame.data)[j * frame.cols + i].b;
                color_count += 3;
            }
        }

        stbi_write_png("frames/frame1.png", frame.cols, frame.rows, 3, texture.data(), frame.cols * 3);
        stbi_write_png("frames/frame2.png", frame.cols, frame.rows, 3, pixels, frame.cols * 3);
        alive = 0;
        return 0;

        frame_count += 1;

        if (_min == -1 || sum < _min) {
            _min = sum;
        }

        if (_max == -1 || sum > _max) {
            _max = sum;
        }

        if ((time(NULL) - _prev_press) > 10 && sum < _BLACK) {
            std::cout << "BLACK" << std::endl;
            _prev_press = time(NULL);
        }

        //std::cout << _min << " | " << _max << std::endl;
        //std::cout << _min << std::endl;

        if (sum >= _N8MENUMIN && sum <= _N8MENUMAX) {
            std::cout << "MENU OPEN" << std::endl;
        } else {
            std::cout << "MENU IS NOT OPEN" << std::endl;
        }

        nanosleep(&requested, NULL);
    }

    return 0;
}
