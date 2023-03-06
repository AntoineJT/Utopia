import cardia_native as _cd


class Camera(_cd.Camera):
    def __init__(self) -> None:
        super().__init__()

    def get_view_projection_matrix(self) -> Matrix4:
        pass
