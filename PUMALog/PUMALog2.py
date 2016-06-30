from openxc.interface import UsbVehicleInterface
from openxc.measurements import EventedMeasurement, Measurement
from datetime import datetime

def receive(measurement, **kwargs):
    # this callback will receive each message received as a dict
    if measurement.name == 'steering_wheel_angle':
        print datetime.now()
        print ',steering_wheel_angle,'
        print measurement.value
        print '\n'
    elif measurement.name == 'vehicle_speed':
        print datetime.now()
        print ',vehicle_speed,'
        print vehicle_speed
        print '\n'
        
    
vi = UsbVehicleInterface(callback=receive)
vi.start()
# This will block until the connection dies or you exit the program
vi.join()
