

#include <rpygen_wrapper.hpp>

PYBIND11_MODULE(wpiHal, m) {
    initWrapper(m);
}
