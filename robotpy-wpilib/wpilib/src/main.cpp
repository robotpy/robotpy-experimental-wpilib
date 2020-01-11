
#include "rpygen_wrapper.hpp"

void initRunWrapper(py::module &m);

RPYBUILD_PYBIND11_MODULE(m)
{
    initWrapper(m);
    initRunWrapper(m);
}
