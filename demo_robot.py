
# need to install
# - robotpy-wpiutil
# - hal
# - robotpy-wpilib
# - halsim_gui

import wpilib

class MyRobot(wpilib.TimedRobot):
    def robotInit(self):
        print("Robot init")
        self.input = wpilib.DigitalInput(1)
        self.timer = wpilib.Timer()
        self.timer.start()
    
    def teleopInit(self):
        print("teleopInit?")
        self.timer.reset()
    
    def teleopPeriodic(self):
        if self.timer.hasPeriodPassed(0.5):
            print('digital input:', self.input.get())

if __name__ == '__main__':
    # this won't be necessary for the released version
    import halsim
    halsim.enable_gui()

    r = MyRobot()

    # nor will this
    wpilib._impl.wpilibc._run(None, r.startCompetition, r.endCompetition)
