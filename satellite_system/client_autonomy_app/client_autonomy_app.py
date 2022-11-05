#!/usr/bin/env python3

import queue
from BaseApp import BaseApp
import message_pb2 as proto
import time
import statistics


class ClientAutonomyApp (BaseApp):
    def __init__(self) -> None:
        self.prop_data = dict()
        self.client_magnetic_x = 0.0
        self.client_magnetic_y = 0.0
        self.client_magnetic_z = 0.0
        super().__init__("vehicle.depot_autonomy_app")
        

    def read_propMass(self):
        for msg in self.telemetry_queue:
            if msg.HasField("telemetry"):
                if msg.telemetry.HasField("client_prop_mass"):
                    client_prop_mass = msg.telemetry.client_prop_mass.client_prop_mass
                    print(client_prop_mass)

    def read_magnetic(self):
        for msg in self.telemetry_queue:
            if msg.HasField("telemetry"):
                if msg.telemetry.HasField("gnc_client_magnetic"):
                    self.client_magnetic_x = msg.telemetry.gnc_client_magnetic.x
                    self.client_magnetic_y = msg.telemetry.gnc_client_magnetic.y
                    self.client_magnetic_z = msg.telemetry.gnc_client_magnetic.z
                    print(self.client_magnetic_x)
    
    def send_stepper_command(self):                            
        msg = proto.Message()                                
        cmd = proto.Command()                                  
        step_command= proto.ClientStepperCommand()        

        # Simply align with Y as a test          
        step_command.pos_deg = self.client_magnetic_y               
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
            self.read_magnetic()

if __name__ == "__main__":
    a= ClientAutonomyApp()
    # a.run() # Runs the app
    
