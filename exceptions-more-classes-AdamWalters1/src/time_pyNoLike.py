class InvalidHr(Exception):
    """
    Exception raised for errors in the input hour.

    Attributes:
        message -- explanation of the error
    """
    def __init__(self, message="The value of hr must be between 0 and 12."):
        self.message = message
        super().__init__(self.message)


class InvalidMin(Exception):
    """
    Exception raised for errors in the input minutes.

    Attributes:
        message -- explanation of the error
    """
    def __init__(self, message="The value of min must be between 0 and 59."):
        self.message = message
        super().__init__(self.message)


class InvalidSec(Exception):
    """
    Exception raised for errors in the input seconds.

    Attributes:
        message -- explanation of the error
    """
    def __init__(self, message="The value of sec must be between 0 and 59."):
        self.message = message
        super().__init__(self.message)


def get_hours():
    """
    Prompts the user for hours input and validates it.

    Returns:
        int: Validated hours input by the user.
    """
    while True:
        try:
            hr = int(input("Enter hours: "))
            if hr < 0 or hr >12:
                raise InvalidHr
            return hr
        except InvalidHr as e:
            print(e)


def get_minutes():
    """
    Prompts the user for minutes input and validates it.

    Returns:
        int: Validated minutes input by the user.
    """
    while True:
        try:
            Min = int(input("Enter minutes: "))
            if Min < 0 or Min >59:
                raise InvalidMin
            return Min
        except InvalidMin as e:
            print(e)

def get_seconds():
    """
    Prompts the user for seconds input and validates it.

    Returns:
        int: Validated seconds input by the user.
    """
    while True:
        try:
            sec = int(input("Enter seconds: "))
            if sec < 0 or sec >59:
                raise InvalidSec
            return sec
        except InvalidSec as e:
            print(e)


def print_24_hour_time(hr, min, sec, period):
    """
    Converts 12-hour time format to 24-hour format and prints it.

    Parameters:
        hr (int): Hours part of the time.
        min (int): Minutes part of the time.
        sec (int): Seconds part of the time.
        period (str): AM or PM indicator.
    """
    if period == "AM":
        if hr == 12:
            hr = 0
    elif period == "PM":
        if hr != 12:
            hr += 12
    print(f"The 24-hour time is {hr:02}:{min:02}:{sec:02}")


if __name__ == "__main__": 
    hours = get_hours()
    minutes = get_minutes()
    seconds = get_seconds()

    # Fill remainder of code here
    done = False
    while not done:
        try:
            period = input("Enter AM or PM: ").upper()
            if period in ["AM","PM"]:
                print_24_hour_time(hours,minutes,seconds,period)
                done = True  
            else:
                raise ValueError("Invalid Time period, please enter AM or PM")
        except ValueError as e:
            print(e)
