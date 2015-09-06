#include "colors.h"

nc_color color_from_string(QString new_color){
    if("red"==new_color){
        return c_red;
    } else if("blue"==new_color){
        return c_blue;
    } else if("green"==new_color){
        return c_green;
    } else if("light_cyan"==new_color || "ltcyan"==new_color){
        return c_ltcyan;
    } else if("brown"==new_color){
        return c_brown;
    } else if("light_red"==new_color || "ltred"==new_color){
        return c_ltred;
    } else if("white"==new_color){
        return c_white;
    } else if("black"==new_color){
        return c_black;
    } else if("light_blue"==new_color || "ltblue"==new_color){
        return c_ltblue;
    } else if("yellow"==new_color){
        return c_yellow;
    } else if("magenta"==new_color){
        return c_magenta;
    } else if("cyan"==new_color){
        return c_cyan;
    } else if("light_gray"==new_color || "ltgray"==new_color){
        return c_ltgray;
    } else if("dark_gray"==new_color || "dkgray"==new_color){
        return c_dkgray;
    } else if("light_green"==new_color || "ltgreen"==new_color){
        return c_ltgreen;
    } else if("pink"==new_color){
        return c_pink;
    } else if("white_red"==new_color){
        return c_white_red;//
    } else if("ltgray_red"==new_color || "light_gray_red"==new_color){
        return c_ltgray_red;//
    } else if("dkgray_red"==new_color || "dark_gray_red"==new_color){
        return c_dkgray_red;//
    } else if("red_red"==new_color){
        return c_red_red;//
    } else if("green_red"==new_color){
        return c_green_red;//
    } else if("blue_red"==new_color){
        return c_blue_red;//
    } else if("cyan_red"==new_color){
        return c_cyan_red;
    } else if("magenta_red"==new_color){
        return c_magenta_red;//
    } else if("brown_red"==new_color){
        return c_brown_red;//
    } else if("ltred_red"==new_color || "light_red_red"==new_color){
        return c_ltred_red;//
    } else if("ltgreen_red"==new_color || "light_green_red"==new_color){
        return c_ltgreen_red;
    } else if("ltblue_red"==new_color || "light_blue_red"==new_color){
        return c_ltblue_red;//
    } else if("ltcyan_red"==new_color || "light_cyan_red"==new_color){
        return c_ltcyan_red;//
    } else if("pink_red"==new_color){
        return c_pink_red;//
    } else if("yellow_red"==new_color){
        return c_yellow_red;//
    } else {
        return c_white;
    }
}

nc_color bgcolor_from_string(QString new_color) {
  if("black" == new_color) {
    return i_black;
  } else if("white" == new_color) {
    return i_white;
  } else if("light_gray" == new_color || "ltgray" == new_color) {
    return i_ltgray;
  } else if("dark_gray" == new_color || "dkgray" == new_color) {
    return i_dkgray;
  } else if("red" == new_color) {
    return i_red;
  } else if("green" == new_color) {
    return i_green;
  } else if("blue" == new_color) {
    return i_blue;
  } else if("cyan" == new_color) {
    return i_cyan;
  } else if("magenta" == new_color) {
    return i_magenta;
  } else if("brown" == new_color) {
    return i_brown;
  } else if("light_red" == new_color || "ltred" == new_color) {
    return i_ltred;
  } else if("light_blue" == new_color || "ltblue" == new_color) {
    return i_ltblue;
  } else if("light_cyan" == new_color || "ltcyan" == new_color) {
    return i_ltcyan;
  } else if("pink" == new_color) {
    return i_pink;
  } else if("yellow" == new_color) {
    return i_yellow;
  } else {
    return i_white;
  }
}
