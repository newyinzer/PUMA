from openxc.interface import UsbVehicleInterface
from openxc.measurements import EventedMeasurement, Measurement
import time

def receive(measurement, **kwargs):
    # this callback will receive each message received as a dict
    if measurement['name'] == 'steering_wheel_angle':
        print "%s,steering_wheel_angle,%s" % ((time.time() - start_time), measurement['value'])        
    elif measurement['name'] == 'vehicle_speed':
        print "%s,vehicle_speed,%s" % ((time.time() - start_time), measurement['value'])        
    
vi = UsbVehicleInterface(callback=receive)
vi.start()
start_time = time.time()
end_time = start_time + 600;
iterator = 0;
while(time.time() < end_time):
	iterator = iterator + 1;

vi.stop()
