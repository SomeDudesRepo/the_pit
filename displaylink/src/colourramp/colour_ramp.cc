#include <bitset>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <sstream>

#include "colourramp/colour_ramp.h"
#include "colourramp/exception.h"
#include "colourramp/number_utils.h"

void ProcessArguments(int argc, char *argv[]) {
  std::string display_name(CheckArguments(argc, argv));
  RgbNumber tl(GetIntFromConsoleArgument(argv[2])),
            tr(GetIntFromConsoleArgument(argv[3])),
            bl(tl),
            br(tr);
  if (argc == 6) {
    bl = GetIntFromConsoleArgument(argv[4]);
    br = GetIntFromConsoleArgument(argv[5]);
    FourCornersDisplay(display_name, tl, tr, bl, br);
  } else {
    TwoCornersDisplay(display_name, tl, tr);
  }

//  PrintMaskedValues(tl);
//  PrintMaskedValues(tr);
//  PrintMaskedValues(bl);
//  PrintMaskedValues(br);
}

std::string CheckArguments(int argc, char *argv[]) {
  if (argc != 4 && argc != 6)
    throw GeneralException("Error: Wrong number of arguments.");


  std::string display(argv[1]);
  if (!ValidDisplay(display))
    throw GeneralException("Error: Wrong number of arguments.");

  return display;
}

bool ValidDisplay(const std::string& display) {
  return !display.empty();
}

RgbNumber GenerateColourMix(double tl,
                            double tr,
                            double bl,
                            double br,
                            double width,
                            double height,
                            double col,
                            double row,
                            int shift) {
  double t(col / (width - 1));
  double s(row / (height - 1));
  return RgbNumber((tl * (1-t) * (1-s) +
                   tr * t * (1-s) +
                   bl * (1-t) * s +
                   br * t * s)) << shift;
}

RgbNumber RedComponent(RgbNumber tl,
                       RgbNumber tr,
                       RgbNumber bl,
                       RgbNumber br,
                       double width,
                       double height,
                       double col,
                       double row) {
  return GenerateColourMix(tl, tr, bl, br, width, height, col, row, 11);
}

RgbNumber GreenComponent(RgbNumber tl,
                         RgbNumber tr,
                         RgbNumber bl,
                         RgbNumber br,
                         double width,
                         double height,
                         double col,
                         double row) {
  return GenerateColourMix(tl, tr, bl, br, width, height, col, row, 5);
}

RgbNumber BlueComponent(RgbNumber tl,
                        RgbNumber tr,
                        RgbNumber bl,
                        RgbNumber br,
                        double width,
                        double height,
                        double col,
                        double row) {
  return GenerateColourMix(tl, tr, bl, br, width, height, col, row, 0);
}

std::vector<RgbNumber> CalculateRow(const std::array<RgbNumber, 3>& tl_rgb,
                                    const std::array<RgbNumber, 3>& tr_rgb,
                                    const std::array<RgbNumber, 3>& bl_rgb,
                                    const std::array<RgbNumber, 3>& br_rgb,
                                    int width,
                                    int height,
                                    int row) {
  std::vector<RgbNumber> line;
  for (int col(0); col != width; ++col) {
    RgbNumber red(RedComponent(tl_rgb[2], tr_rgb[2], bl_rgb[2], br_rgb[2],
                               width, height, col, row)),
              green(GreenComponent(tl_rgb[1], tr_rgb[1], bl_rgb[1], br_rgb[1],
                                   width, height, col, row)),
              blue(BlueComponent(tl_rgb[0], tr_rgb[0], bl_rgb[0], br_rgb[0],
                                 width, height, col, row));
    line.push_back(red + green + blue);
  }
  return line;
}

void FourCornersDisplay(const std::string& display_id,
                        RgbNumber tl,
                        RgbNumber tr,
                        RgbNumber bl,
                        RgbNumber br) {
  std::array<RgbNumber, 3> tl_rgb(GetRgbComponents(tl)),
                           tr_rgb(GetRgbComponents(tr)),
                           bl_rgb(GetRgbComponents(bl)),
                           br_rgb(GetRgbComponents(br));
  int width, height;
  Display display(GetDisplay(display_id, width, height));
  std::vector<RgbNumber> line;
  for (int y(0); y != height; ++y) {
    line = CalculateRow(tl_rgb, tr_rgb, bl_rgb, br_rgb, width, height, y);
    display.draw_raster(0, y, line.data(), width);
  }
}

double GetDelta(int width, double tl_rgb, double tr_rgb) {
  double delta((tl_rgb - tr_rgb) / (width - 1));
  return -delta;
}

std::vector<RgbNumber> CalculateLine(int width,
                                     const std::array<RgbNumber, 3>& tl_rgb,
                                     const std::array<RgbNumber, 3>& tr_rgb) {
  double red_delta(GetDelta(width, tl_rgb[2], tr_rgb[2])),
         green_delta(GetDelta(width, tl_rgb[1], tr_rgb[1])),
         blue_delta(GetDelta(width, tl_rgb[0], tr_rgb[0]));
  std::vector<RgbNumber> line;
  for (int x(0); x != width; ++x) {
    RgbNumber red(RgbNumber(tl_rgb[2] + (red_delta * x)) << 11),
              green(RgbNumber(tl_rgb[1] + (green_delta * x)) << 5),
              blue(RgbNumber(tl_rgb[0] + (blue_delta * x)));
    line.push_back(red + green + blue);
  }

  return line;
}

Display GetDisplay(const std::string& display_id, int& width, int& height) {
  Display display;
  if (!display.connect(display_id.c_str())) {
    std::string message("Failed to connect to display " + display_id);
    throw GeneralException(message);
  }
  display.get_size(width, height);
  return display;
}

void TwoCornersDisplay(const std::string& display_id, RgbNumber tl, RgbNumber tr) {
  std::array<RgbNumber, 3> tl_rgb(GetRgbComponents(tl)), tr_rgb(GetRgbComponents(tr));
  int width, height;
  Display display(GetDisplay(display_id, width, height));

  std::vector<RgbNumber> line(CalculateLine(width, tl_rgb, tr_rgb));
  for (int y(0); y != height; ++y)
    display.draw_raster(0, y, line.data(), width);
}
