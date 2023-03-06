from cardia import Behavior, Time


class Moving(Behavior):
    velocity: int
    _x_vec: int
    _y_vec: int

    def __init__(self):
        super().__init__()
        self._x_vec = -1
        self._y_vec = -1

    def on_create(self):
        pass

    def on_update(self):
        if self.transform.position.x <= 0:
            self._x_vec = 1
        self.transform.position.x += self._x_vec * self.velocity * Time.delta_time.seconds()

        if self.transform.position.y <= 0:
            self._y_vec = 1
        self.transform.position.y += self._y_vec * self.velocity * Time.delta_time.seconds()

        