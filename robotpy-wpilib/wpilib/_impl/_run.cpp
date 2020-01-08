
#include "rpygen_wrapper.hpp"
#include <pybind11/functional.h>

// .. don't judge me
#define RunHALInitialization RobotPyHALInitialization
#include "frc/RobotBase.h"

#include <hal/FRCUsageReporting.h>
#include <hal/HALBase.h>

namespace frc {

int RobotPyHALInitialization() {
  if (!HAL_Initialize(500, 0)) {
    wpi::errs() << "FATAL ERROR: HAL could not be initialized\n";
    return -1;
  }
  HAL_Report(HALUsageReporting::kResourceType_Language,
             HALUsageReporting::kLanguage_Python, 0, VERSION_INFO);
  // wpi::outs() << "\n********** Robot program starting **********\n";
  return 0;
}

} // namespace frc

std::function<void()> g_CreateRobot;
std::function<void()> g_StartCompetition;
std::function<void()> g_EndCompetition;

// Allows us to use the StartRobot function provided by WPILib, since it
// wants to create a robot instance itself and we don't want it to
struct FakeRobot {

  FakeRobot() {
    if (g_CreateRobot)
      g_CreateRobot();
  }

  void StartCompetition() {
    if (g_StartCompetition)
      g_StartCompetition();
  }

  void EndCompetition() {
    if (g_EndCompetition)
      g_EndCompetition();
  }
};

// calls startrobot, must not be called twice!
void _run(std::function<void()> createRobot,
          std::function<void()> startCompetition,
          std::function<void()> endCompetition) {

  static wpi::mutex m;
  static bool running = false;
  {
    std::unique_lock lock(m);
    if (running) {
      return;
    }
    running = true;
  }

  g_CreateRobot = createRobot;
  g_StartCompetition = startCompetition;
  g_EndCompetition = endCompetition;

  frc::StartRobot<FakeRobot>();

  // clear these before exiting, otherwise it'll hang
  g_CreateRobot = nullptr;
  g_StartCompetition = nullptr;
  g_EndCompetition = nullptr;

  {
    std::unique_lock lock(m);
    running = false;
  }
}

void initRunWrapper(py::module &m) {
  m.def("_run", &_run, release_gil(), "internal function to start a robot");
}