#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
    static Options* GetOptions();

private:
    Options();
    Options(Options&){}
    Options& operator=(Options&){}

    static Options* OptionsInstance;
};

#endif // OPTIONS_H
