def divide(numerator, denominator):
    if denominator == 0:
        # Raise a ZeroDivisionError if denominator is 0
        raise ZeroDivisionError("Division by zero error")
    return numerator / denominator

try:
    # Attempt to divide 10 by 0 - this will raise an exception
    result = divide(10, 0)
 # result = divide(10, 2) # This will not raise an exception
except ZeroDivisionError as e:
    # Handle ZeroDivisionError exceptions
    print(f"Caught a division by zero error: {e}")
except Exception as e:
    # Handle other exceptions
    print(f"Caught an exception: {e}")
else:
    # This block executes if the try block doesn't raise an exception
    print(f"The result is {result}")
finally:
    # This block executes no matter what, even if an exception is raised
    print("Execution of the division operation is complete.")
