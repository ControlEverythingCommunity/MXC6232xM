# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MXC6232xM
# This code is designed to work with the MXC6232xM_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Accelorometer?sku=MXC6232xM_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# MXC6232xM address, 0x10(16)
# Select Internal configuration register
#		0x00(00)	Power ON, Self-test OFF, Bandgap test normal
#					Temperature disabled
data = [0x00]
i2c.write(0x10, data)

time.sleep(0.5)

# MXC6232xM address, 0x10(16)
# Read data back from 0x00(0), 5 bytes
# Internal register, X-Axis MSB, X-Axis LSB, Y-Axis MSB, Y-Axis LSB
data = i2c.readBytes(0x10, 0x00, 5)

# Convert the data
xAccl = (data[1] & 0x0F) * 256 + data[2]
if xAccl > 2047 :
	xAccl -= 4096

yAccl = (data[3] & 0x0F) * 256 + data[4]
if yAccl > 2047 :
	yAccl -= 4096

# Output data to screen
print "Acceleration in X-Axis : %d" %xAccl
print "Acceleration in Y-Axis : %d" %yAccl
