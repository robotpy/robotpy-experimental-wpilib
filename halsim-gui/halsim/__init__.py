
import os
from os.path import abspath, dirname, join

def enable_gui():
    import hal
    hal.initialize(500, 0)
    hal.setShowExtensionsNotFoundMessages(True)

    root = join(abspath(dirname(__file__)), '_impl', 'lib')
    ext = join(root, os.listdir(root)[0])
    hal.loadOneExtension(ext)

