#!/usr/bin/env python3

import queue
from BaseApp import BaseApp
import message_pb2 as proto
import time
import statistics


class ClientAutonomyApp (BaseApp):
    def __init__(self) -> None:
        self.prop_data = dict()
        super().__init__("vehicle.depot_autonomy_app")
        

    def read_propMass(self):
        for msg in self.telemetry_queue:
            if msg.HasField("telemetry"):
                if msg.telemetry.HasField("depot_prop_mass"):
                    depot_prop_mass = msg.telemetry.depot_prop_mass.depot_prop_mass
                    depot_prop_mass = depot_prop_mass + 1.1111
                    print(depot_prop_mass)
    
    def send_stepper_command(self):                            
        msg = proto.Message()                                
        cmd = proto.Command()                                  
        step_command= proto.ClientStepperCommand()                  
        step_command.pos_deg = 250.0                 
        cmd.set_stepper_command.CopyFrom(step_command)            
        msg.command.CopyFrom(cmd)                             
        self.send_command(msg)                                                                
        print(msg)   
        
    def setup(self) -> None:
        self.manual_mode = False
        print("Client Autonomy System Online")

    def run(self) -> None:
        # Read commands and telem
        self.send_stepper_command()
        time.sleep(5)

        if len(self.command_queue):
            pass
        if len(self.telemetry_queue):
            self.read_propMass()

if __name__ == "__main__":
    a= ClientAutonomyApp()
    # a.run() # Runs the app
    
