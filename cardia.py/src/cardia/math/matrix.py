import cardia_native as _cd
from .vector import Vector4

class Matrix4(_cd.mat4):
    def __mul__(self, vec4: Vector4):
        pass
