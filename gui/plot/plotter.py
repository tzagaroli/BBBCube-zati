from PyQt5.QtWidgets import QWidget, QGridLayout
from .imu_plot import IMUPlot
from .state_plot import StatePlot

class PlotManager:
    def __init__(self, mode):
        self.widget = QWidget()
        self.layout = QGridLayout()
        self.widget.setLayout(self.layout)
        self.plots = []

        if mode == "imu+state":
            imu_plot = IMUPlot()
            state_plot = StatePlot()
            self.plots = [imu_plot, state_plot]

            self.layout.addWidget(imu_plot.get_widget(), 0, 0)
            self.layout.addWidget(state_plot.get_widget(), 0, 1)

        elif mode == "imu":
            imu_plot = IMUPlot()
            self.plots = [imu_plot]
            self.layout.addWidget(imu_plot.get_widget(), 0, 0)

        elif mode == "state":
            state_plot = StatePlot()
            self.plots = [state_plot]
            self.layout.addWidget(state_plot.get_widget(), 0, 0)


        else:
            raise ValueError(f"Unknown mode: {mode}")

    def get_widget(self):
        return self.widget

    def update(self, ccontent):
        for plot in self.plots:
            plot.update(ccontent)
