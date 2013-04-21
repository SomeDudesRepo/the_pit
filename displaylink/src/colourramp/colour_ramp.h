#include <array>
#include <string>
#include <vector>

#include "colourramp/display.h"

typedef unsigned short RgbNumber;

void ProcessArguments(int argc, char *argv[]);

std::string CheckArguments(int argc, char *argv[]);

bool ValidDisplay(const std::string& display);

double GetDelta(int width, double tl_rgb, double tr_rgb);

Display GetDisplay(const std::string& display_id, int& width, int& height);

std::vector<RgbNumber> CalculateRow(const std::array<RgbNumber, 3>& tl_rgb,
                                    const std::array<RgbNumber, 3>& tr_rgb,
                                    const std::array<RgbNumber, 3>& bl_rgb,
                                    const std::array<RgbNumber, 3>& br_rgb,
                                    int width,
                                    int height,
                                    int row);

void FourCornersDisplay(const std::string& /*display_id*/,
                        RgbNumber /*tl*/,
                        RgbNumber /*tr*/,
                        RgbNumber /*bl*/,
                        RgbNumber /*br*/);

std::vector<RgbNumber> CalculateLine(int width,
                                     const std::array<RgbNumber, 3>& tl_rgb,
                                     const std::array<RgbNumber, 3>& tr_rgb);

void TwoCornersDisplay(const std::string& display_id, RgbNumber tl, RgbNumber tr);
