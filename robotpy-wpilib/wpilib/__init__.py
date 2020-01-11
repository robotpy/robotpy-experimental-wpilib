
from . import _init_wpilib
from ._wpilib import *
del _init_wpilib

try:
    from .version import version as __version__
except ImportError:
    __version__ = 'master'
