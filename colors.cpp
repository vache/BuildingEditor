#include "colors.h"

QStringList colorList = { "red", "blue", "green", "light_cyan", "brown", "light_red", "white", "black",
            "light_blue", "yellow", "magenta", "cyan", "light_gray", "dark_gray", "light_green",
            "pink", "white_red", "light_gray_red", "dark_gray_red", "red_red", "green_red",
            "blue_red", "cyan_red", "magenta_red", "brown_red", "light_red_red", "light_green_red",
            "light_cyan_red", "pink_red", "yellow_red" };

nc_color color_from_string(QString new_color){
    if ("red"==new_color){
        return c_red;
    } else if ("blue"==new_color){
        return c_blue;
    } else if ("green"==new_color){
        return c_green;
    } else if ("light_cyan"==new_color || "ltcyan"==new_color){
        return c_ltcyan;
    } else if ("brown"==new_color){
        return c_brown;
    } else if ("light_red"==new_color || "ltred"==new_color){
        return c_ltred;
    } else if ("white"==new_color){
        return c_white;
    } else if ("black"==new_color){
        return c_black;
    } else if ("light_blue"==new_color || "ltblue"==new_color){
        return c_ltblue;
    } else if ("yellow"==new_color){
        return c_yellow;
    } else if ("magenta"==new_color){
        return c_magenta;
    } else if ("cyan"==new_color){
        return c_cyan;
    } else if ("light_gray"==new_color || "ltgray"==new_color){
        return c_ltgray;
    } else if ("dark_gray"==new_color || "dkgray"==new_color){
        return c_dkgray;
    } else if ("light_green"==new_color || "ltgreen"==new_color){
        return c_ltgreen;
    } else if ("pink"==new_color){
        return c_pink;
    } else if ("white_red"==new_color){
        return c_white_red;//
    } else if ("ltgray_red"==new_color || "light_gray_red"==new_color){
        return c_ltgray_red;//
    } else if ("dkgray_red"==new_color || "dark_gray_red"==new_color){
        return c_dkgray_red;//
    } else if ("red_red"==new_color){
        return c_red_red;//
    } else if ("green_red"==new_color){
        return c_green_red;//
    } else if ("blue_red"==new_color){
        return c_blue_red;//
    } else if ("cyan_red"==new_color){
        return c_cyan_red;
    } else if ("magenta_red"==new_color){
        return c_magenta_red;//
    } else if ("brown_red"==new_color){
        return c_brown_red;//
    } else if ("ltred_red"==new_color || "light_red_red"==new_color){
        return c_ltred_red;//
    } else if ("ltgreen_red"==new_color || "light_green_red"==new_color){
        return c_ltgreen_red;
    } else if ("ltblue_red"==new_color || "light_blue_red"==new_color){
        return c_ltblue_red;//
    } else if ("ltcyan_red"==new_color || "light_cyan_red"==new_color){
        return c_ltcyan_red;//
    } else if ("pink_red"==new_color){
        return c_pink_red;//
    } else if ("yellow_red"==new_color){
        return c_yellow_red;//
    } else {
        return c_white;
    }
}

nc_color bgcolor_from_string(QString new_color) {
  if ("black" == new_color) {
    return i_black;
  } else if ("white" == new_color) {
    return i_white;
  } else if ("light_gray" == new_color || "ltgray" == new_color) {
    return i_ltgray;
  } else if ("dark_gray" == new_color || "dkgray" == new_color) {
    return i_dkgray;
  } else if ("red" == new_color) {
    return i_red;
  } else if ("green" == new_color) {
    return i_green;
  } else if ("blue" == new_color) {
    return i_blue;
  } else if ("cyan" == new_color) {
    return i_cyan;
  } else if ("magenta" == new_color) {
    return i_magenta;
  } else if ("brown" == new_color) {
    return i_brown;
  } else if ("light_red" == new_color || "ltred" == new_color) {
    return i_ltred;
  } else if ("light_blue" == new_color || "ltblue" == new_color) {
    return i_ltblue;
  } else if ("light_cyan" == new_color || "ltcyan" == new_color) {
    return i_ltcyan;
  } else if ("pink" == new_color) {
    return i_pink;
  } else if ("yellow" == new_color) {
    return i_yellow;
  } else {
    return i_white;
  }
}

QString string_from_color(nc_color color)
{
    if (c_red == color){
        return "red";
    } else if (c_blue == color){
        return "blue";
    } else if (c_green == color){
        return "green";
    } else if (c_ltcyan == color){
        return "light_cyan";
    } else if (c_brown == color){
        return "brown";
    } else if (c_ltred == color){
        return "light_red";
    } else if (c_white == color){
        return "white";
    } else if (c_black == color){
        return "black";
    } else if (c_ltblue == color){
        return "light_blue";
    } else if (c_yellow == color){
        return "yellow";
    } else if (c_magenta == color){
        return "magenta";
    } else if (c_cyan == color){
        return "cyan";
    } else if (c_ltgray == color){
        return "light_gray";
    } else if (c_dkgray == color){
        return "dark_gray";
    } else if (c_ltgreen == color){
        return "light_green";
    } else if (c_pink == color){
        return "pink";
    } else if (c_white_red == color){
        return "white_red";
    } else if (c_ltgray_red == color){
        return "light_gray_red";
    } else if (c_dkgray_red == color){
        return "dark_gray_red";
    } else if (c_red_red == color){
        return "red_red";
    } else if (c_green_red == color){
        return "green_red";
    } else if (c_blue_red == color){
        return "blue_red";
    } else if (c_cyan_red == color){
        return "cyan_red";
    } else if (c_magenta_red == color){
        return "magenta_red";
    } else if (c_brown_red == color){
        return "brown_red";
    } else if (c_ltred_red == color){
        return "light_red_red";
    } else if (c_ltgreen_red == color){
        return "light_green_red";
    } else if (c_ltblue_red == color){
        return "light_blue_red";
    } else if (c_ltcyan_red == color){
        return "light_cyan_red";
    } else if (c_pink_red == color){
        return "pink_red";
    } else if (c_yellow_red == color){
        return "yellow_red";
    } else {
        return "";
    }
}

QString string_from_bgcolor(nc_color color)
{
    if (i_black == color) {
        return "black";
    } else if (i_white == color) {
        return "white";
    } else if (i_ltgray == color) {
        return "light_gray";
    } else if (i_dkgray == color) {
        return "dark_gray";
    } else if (i_red == color) {
        return "red";
    } else if (i_green == color) {
        return "green";
    } else if (i_blue == color) {
        return "blue";
    } else if (i_cyan == color) {
        return "cyan";
    } else if (i_magenta == color) {
        return "magenta";
    } else if (i_brown == color) {
        return "brown";
    } else if (i_ltred == color) {
        return "light_red";
    } else if (i_ltblue == color) {
        return "light_blue";
    } else if (i_ltcyan == color) {
        return "light_cyan";
    } else if (i_pink == color) {
        return "pink";
    } else if (i_yellow == color) {
        return "yellow";
    } else {
        return "";
    }
}

QString string_from_any_color(nc_color color)
{
    if (c_red == color){
        return "red";
    } else if (c_blue == color){
        return "blue";
    } else if (c_green == color){
        return "green";
    } else if (c_ltcyan == color){
        return "light_cyan";
    } else if (c_brown == color){
        return "brown";
    } else if (c_ltred == color){
        return "light_red";
    } else if (c_white == color){
        return "white";
    } else if (c_black == color){
        return "black";
    } else if (c_ltblue == color){
        return "light_blue";
    } else if (c_yellow == color){
        return "yellow";
    } else if (c_magenta == color){
        return "magenta";
    } else if (c_cyan == color){
        return "cyan";
    } else if (c_ltgray == color){
        return "light_gray";
    } else if (c_dkgray == color){
        return "dark_gray";
    } else if (c_ltgreen == color){
        return "light_green";
    } else if (c_pink == color){
        return "pink";
    } else if (c_white_red == color){
        return "white_red";
    } else if (c_ltgray_red == color){
        return "light_gray_red";
    } else if (c_dkgray_red == color){
        return "dark_gray_red";
    } else if (c_red_red == color){
        return "red_red";
    } else if (c_green_red == color){
        return "green_red";
    } else if (c_blue_red == color){
        return "blue_red";
    } else if (c_cyan_red == color){
        return "cyan_red";
    } else if (c_magenta_red == color){
        return "magenta_red";
    } else if (c_brown_red == color){
        return "brown_red";
    } else if (c_ltred_red == color){
        return "light_red_red";
    } else if (c_ltgreen_red == color){
        return "light_green_red";
    } else if (c_ltblue_red == color){
        return "light_blue_red";
    } else if (c_ltcyan_red == color){
        return "light_cyan_red";
    } else if (c_pink_red == color){
        return "pink_red";
    } else if (c_yellow_red == color){
        return "yellow_red";
    } else if (i_black == color) {
        return "black";
    } else if (i_white == color) {
        return "white";
    } else if (i_ltgray == color) {
        return "light_gray";
    } else if (i_dkgray == color) {
        return "dark_gray";
    } else if (i_red == color) {
        return "red";
    } else if (i_green == color) {
        return "green";
    } else if (i_blue == color) {
        return "blue";
    } else if (i_cyan == color) {
        return "cyan";
    } else if (i_magenta == color) {
        return "magenta";
    } else if (i_brown == color) {
        return "brown";
    } else if (i_ltred == color) {
        return "light_red";
    } else if (i_ltblue == color) {
        return "light_blue";
    } else if (i_ltcyan == color) {
        return "light_cyan";
    } else if (i_pink == color) {
        return "pink";
    } else if (i_yellow == color) {
        return "yellow";
    } else {
        return "";
    }
}
