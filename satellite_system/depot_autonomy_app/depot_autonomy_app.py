#!/usr/bin/env python3

import queue
from BaseApp import BaseApp
import message_pb2 as proto
import time
import statistics


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
                    depot_prop_mass = depot_prop_mass + 1.1111
                    print(depot_prop_mass)
        
    
    def setup(self) -> None:
        self.manual_mode = False
        print("Depot Autonomy System Online")

    def run(self) -> None:
        # Read commands and telem
        if len(self.command_queue):
            pass
        if len(self.telemetry_queue):
            self.read_propMass()

if __name__ == "__main__":
    a= DepotAutonomyApp()
    # a.run() # Runs the app
    
