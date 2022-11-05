#!/usr/bin/env python3

import queue
from BaseApp import BaseApp
import message_pb2 as proto
import time
import statistics
import math 


class ClientAutonomyApp (BaseApp):
    def __init__(self) -> None:
        self.prop_data = dict()
        self.client_magnetic_x = 0.0
        self.client_magnetic_y = 0.0
        self.client_magnetic_z = 0.0
        self.is_initiate = False
        super().__init__("vehicle.depot_autonomy_app")

    def initiate_refuel(self): 
        for msg in self.command_queue:
            if msg.HasField("command"):
                if msg.command.HasField("refuel"):
                    is_refuel = msg.command.refuel.refuel
                    print("Initiate Refuel") 
                    self.is_initiate = True

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

        step_command.pos_deg = 90 - math.atan2(self.client_magnetic_y, self.client_magnetic_x) * 180/math.pi

        cmd.set_stepper_command.CopyFrom(step_command)            
        msg.command.CopyFrom(cmd)                             
        self.send_command(msg)                                                                
        print(msg)   
        
    def setup(self) -> None:
        self.manual_mode = False
        print("Client Autonomy System Online")

    def run(self) -> None:
        # Read commands and telem
        if (self.is_initiate == True):
            self.send_stepper_command()
        time.sleep(1.0)

        if len(self.command_queue):
            self.initiate_refuel()
        if len(self.telemetry_queue):
            self.read_propMass()
            self.read_magnetic()

if __name__ == "__main__":
    a= ClientAutonomyApp()
    # a.run() # Runs the app
    
