#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
    static Options& GetOptions();

private:
    Options() {}
    Options(Options&) = delete;
    Options& operator=(Options&) = delete;
};

#endif // OPTIONS_H
