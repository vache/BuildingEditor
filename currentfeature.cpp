#include "currentfeature.h"

CurrentFeature & CurrentFeature::Get()
{
    static CurrentFeature instance;

    return instance;
}

CurrentFeature::CurrentFeature()
{
}
