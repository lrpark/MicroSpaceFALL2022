#!/usr/bin/env python3

import queue
from BaseApp import BaseApp
import message_pb2 as proto
import time
import statistics
import math


class DepotAutonomyApp (BaseApp):
    def __init__(self) -> None:
        self.prop_data = dict()
        self.manual_mode = None
        super().__init__("vehicle.depot_autonomy_app")
        

    def read_propMass(self):
        for msg in self.telemetry_queue:
            if msg.HasField("telemetry"):
                if msg.telemetry.HasField("depot_prop_mass"):
                    depot_prop_mass = msg.telemetry.depot_prop_mass.depot_prop_mass
                    print(depot_prop_mass)

    def read_magnetic(self):
        for msg in self.telemetry_queue:
            if msg.HasField("telemetry"):
                if msg.telemetry.HasField("gnc_depot_magnetic"):
                    self.depot_magnetic_x = msg.telemetry.gnc_depot_magnetic.x
                    self.depot_magnetic_y = msg.telemetry.gnc_depot_magnetic.y
                    self.depot_magnetic_z = msg.telemetry.gnc_depot_magnetic.z
                    print(self.depot_magnetic_x)
        
    
    def setup(self) -> None:
        self.manual_mode = False
        print("Depot Autonomy System Online")

    def run(self) -> None:
        # Read commands and telem
        time.sleep(1.0)

        if len(self.command_queue):
            pass
        if len(self.telemetry_queue):
            self.read_propMass()
            self.read_magnetic()

if __name__ == "__main__":
    a= DepotAutonomyApp()
    # a.run() # Runs the app
    
