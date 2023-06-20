import time
import board
import digitalio
import busio
import analogio

def check_gpio_pins():
    print("Checking GPIO Pins...")
    for pin_number in range(62):
        pin_name = f'D{pin_number}'
        try:
            pin = getattr(board, pin_name)
            with digitalio.DigitalInOut(pin) as p:
                print(f'GPIO Pin {pin_name} is functional.')
        except AttributeError:
            print(f'GPIO Pin {pin_name} does not exist.')
        except ValueError:
            print(f'GPIO Pin {pin_name} is in use or non-configurable.')

def check_analog_pins():
    print("Checking Analog Pins...")
    for pin_number in range(16):
        pin_name = f'A{pin_number}'
        try:
            pin = getattr(board, pin_name)
            with analogio.AnalogIn(pin) as p:
                print(f'Analog Pin {pin_name} is functional. Voltage: {p.value} (Raw)')
        except AttributeError:
            print(f'Analog Pin {pin_name} does not exist.')
        except ValueError:
            print(f'Analog Pin {pin_name} is in use or non-configurable.')

def check_i2c():
    print("Checking I2C...")
    try:
        i2c = busio.I2C(board.SCL, board.SDA)
        while not i2c.try_lock():
            pass
        print(f'I2C addresses found: {i2c.scan()}')
        i2c.unlock()
    except ValueError:
        print('I2C initialization failed.')

def check_spi():
    print("Checking SPI...")
    try:
        spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
        if spi.try_lock():
            spi.unlock()
            print('SPI is functional.')
        else:
            print('SPI failed to lock.')
    except ValueError:
        print('SPI initialization failed.')

def check_uart():
    print("Checking UART...")
    try:
        uart = busio.UART(board.TX, board.RX)
        if uart is not None:
            print('UART is functional.')
    except ValueError:
        print('UART initialization failed.')

if __name__ == "__main__":
    check_gpio_pins()
    check_analog_pins()
    check_i2c()
    check_spi()
    check_uart()
