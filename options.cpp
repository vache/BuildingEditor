#include "options.h"

Options& Options::GetOptions()
{
    static Options opt;
    return opt;
}
