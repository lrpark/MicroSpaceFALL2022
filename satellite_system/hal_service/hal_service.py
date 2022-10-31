#!/usr/bin/env python3

from TCPServer import TCPServer
from BaseApp import BaseApp
from Arduino import Arduino
import message_pb2 as proto
import queue
import serial
import time

"""
Purpose: This app is supposed to expose/emulate much of the hardware functions to the applications running

Use Cases:
    1. Abstract serial connection to arduino/wowki
    2. ????
"""



class HalService(BaseApp):
    def __init__(self) -> None:
        self.arduino = None
        self.sent_configs = None
        self.start = None
        super().__init__(id="vehicle.hal_service")

    def _send_to_arduino(self):
        if self.config_params.emulate_arduino:
            # Connect to Wowki server instead
            pass
        else:
            # Send data over serial
            pass

    def setup(self):
        config = self.config_params
        self.arduino = Arduino(port=config.arduino_address, baudrate=config.serial_baudrate)
        self.sent_configs = False
        self.start = time.time()

    def run(self):
        # Send the config parameters once
        if not self.sent_configs:
            msg = proto.Message()
            msg.config_params.CopyFrom(self.config_params)
            self.arduino.send_msg(msg)
            self.sent_configs = True

        # Send any command messages
        if len(self.command_queue):
            self.arduino.send_msg(self.command_queue.pop())
        
        # Read any messages from arduino
        if len(self.arduino.messages):
            msg = self.arduino.messages.pop()
            print(msg)
            self.send_telemetry(msg)
        if (time.time() - self.start) > 2:
            message = proto.Message()
            telemetry = proto.Telemetry()
            propFillLevel = proto.PropFillLevel()
            propFillLevel.level = 4.0
            telemetry.level.CopyFrom(propFillLevel)
            message.telemetry.CopyFrom(telemetry)
            self.send_telemetry(message)
            self.start = time.time()



            message = proto.Message()
            telemetry = proto.Telemetry()
            propMass = proto.PropDepotTankPropMass()
            propMass.prop_depot_tank_prop_mass = 3.0
            telemetry.prop_depot_tank_prop_mass.CopyFrom(propMass)
            message.telemetry.CopyFrom(telemetry)

    def shutdown(self):
        pass


if __name__ == "__main__":
    HalService()
    # ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    # ser.reset_input_buffer()
    # while True:
    #     if ser.in_waiting > 0:
    #         ser.write(b"Hello from Raspberry Pi!\n")
    #         line = ser.readline().decode('utf-8').rstrip()
    #         print(line)
    #         time.sleep(1)
            