import hal

class HALError(Exception):
    pass

class Solenoid:

    def __init__(self, channel):
        portHandle = hal.getPortWithModule(0, channel)
        handle, status = hal.initializeSolenoidPort(portHandle)
        if status != 0:
            raise HALError(status)
        self.solenoidHandle = handle
    
    def get(self):
        return hal.getSolenoid(self.solenoidHandle)
    
    def set(self, on):
        print(f"Solenoid::set({on})")
        hal.setSolenoid(self.solenoidHandle, on)


print(hal.initialize(100, 0))

s = Solenoid(5)
print(s.get())

s.set(True)
print(s.get())

s.set(False)
print(s.get())
