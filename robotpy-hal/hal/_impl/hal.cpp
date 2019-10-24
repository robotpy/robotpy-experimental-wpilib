
#include "gensrc/module.hpp"

PYBIND11_MODULE(wpiHal, m)
{
    initWrapper(m);
}
