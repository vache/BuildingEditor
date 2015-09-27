#ifndef COLORS_H
#define COLORS_H

#include <QColor>
#include <QList>
#include <QString>

struct nc_color {
    QColor fg;
    QColor bg;

    nc_color()
    {
        fg = QColor(Qt::black);
        bg = QColor(Qt::black);
    }

    nc_color(QColor f, QColor b)
    {
        fg = f;
        bg = b;
    }

    bool operator == (const nc_color & other) const
    {
        return ((fg == other.fg) && (bg == other.bg));
    }
};

extern nc_color color_from_string(QString);
extern nc_color bgcolor_from_string(QString);
extern QString string_from_color(nc_color color);
extern QString string_from_bgcolor(nc_color color);
extern QString string_from_any_color(nc_color color);
extern QStringList colorList;

const nc_color c_white(QColor(Qt::white), QColor(Qt::black));
const nc_color c_black(QColor(Qt::black), QColor(Qt::black));
const nc_color c_brown(QColor(0xA5,0x2A,0x2A), QColor(Qt::black));
const nc_color c_yellow(QColor(Qt::yellow), QColor(Qt::black));
const nc_color c_green(QColor(Qt::green), QColor(Qt::black));
const nc_color c_ltred(QColor(0xFF, 0x63, 0x47), QColor(Qt::black));
const nc_color c_ltgray(QColor(Qt::lightGray), QColor(Qt::black));
const nc_color c_cyan(QColor(Qt::cyan), QColor(Qt::black));
const nc_color c_ltcyan(QColor(0xE0,0xFF,0xFF), QColor(Qt::black));
const nc_color c_dkgray(QColor(Qt::darkGray), QColor(Qt::black));
const nc_color c_ltgreen(QColor(0x90,0xEE,0x90), QColor(Qt::black));
const nc_color c_ltblue(QColor(0xAD,0xD8,0xE6), QColor(Qt::black));
const nc_color c_magenta(QColor(Qt::magenta), QColor(Qt::black));
const nc_color c_blue(QColor(Qt::blue), QColor(Qt::black));
const nc_color c_red(QColor(Qt::red), QColor(Qt::black));
const nc_color c_cyan_red(QColor(Qt::cyan), QColor(Qt::red));
const nc_color c_pink(QColor(0xf8, 0xb8, 0xd8), QColor(Qt::black));

const nc_color c_white_red(QColor(Qt::white), QColor(Qt::red));
const nc_color c_ltgray_red(QColor(Qt::lightGray), QColor(Qt::red));
const nc_color c_dkgray_red(QColor(Qt::black), QColor(Qt::red));
const nc_color c_red_red(QColor(Qt::black), QColor(Qt::red));
const nc_color c_green_red(QColor(Qt::green), QColor(Qt::red));
const nc_color c_blue_red(QColor(Qt::blue), QColor(Qt::red));
const nc_color c_magenta_red(QColor(Qt::magenta), QColor(Qt::red));
const nc_color c_brown_red(QColor(0xA5,0x2A,0x2A), QColor(Qt::red));
const nc_color c_ltred_red(QColor(0xFF, 0x63, 0x47), QColor(Qt::red));
const nc_color c_ltgreen_red(QColor(0x90,0xEE,0x90), QColor(Qt::red));
const nc_color c_ltblue_red(QColor(0xAD,0xD8,0xE6), QColor(Qt::red));
const nc_color c_ltcyan_red(QColor(0xE0,0xFF,0xFF), QColor(Qt::red));
const nc_color c_pink_red(QColor(0xf8, 0xb8, 0xd8), QColor(Qt::red));
const nc_color c_yellow_red(QColor(Qt::yellow), QColor(Qt::red));

const nc_color i_brown(QColor(Qt::black), QColor(0xA5,0x2A,0x2A));
const nc_color i_white(QColor(Qt::black), QColor(Qt::white));
const nc_color i_red(QColor(Qt::black), QColor(Qt::red));
const nc_color i_black(QColor(Qt::black), QColor(Qt::black));
const nc_color i_ltgray(QColor(Qt::black), QColor(Qt::lightGray));
const nc_color i_dkgray(QColor(Qt::black), QColor(Qt::darkGray));
const nc_color i_green(QColor(Qt::black), QColor(Qt::green));
const nc_color i_blue(QColor(Qt::black), QColor(Qt::blue));
const nc_color i_cyan(QColor(Qt::black), QColor(Qt::cyan));
const nc_color i_magenta(QColor(Qt::black), QColor(Qt::magenta));
const nc_color i_ltred(QColor(Qt::black), QColor(0xFF, 0x63, 0x47));
const nc_color i_ltblue(QColor(Qt::black), QColor(0xAD,0xD8,0xE6));
const nc_color i_pink(QColor(Qt::black), QColor(0xf8, 0xb8, 0xd8));
const nc_color i_yellow(QColor(Qt::black), QColor(Qt::yellow));
const nc_color i_ltcyan(QColor(Qt::black), QColor(0xE0,0xFF,0xFF));


#endif // COLORS_H
