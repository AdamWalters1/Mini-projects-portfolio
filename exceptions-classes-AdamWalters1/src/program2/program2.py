def add_fractions(num1, den1, num2, den2):
    numfrac = num1 * den2 + num2 * den1
    denfrac = den1 * den2
    return numfrac, denfrac

def subtract_fractions(num1, den1, num2, den2):
    numfrac = num1 * den2 - num2 * den1
    denfrac = den1 * den2
    return numfrac, denfrac

def multiply_fractions(num1, den1, num2, den2):
    numfrac = num1 * num2
    denfrac = den1 * den2
    return numfrac, denfrac

def divide_fractions(num1, den1, num2, den2):
    while True:
        try:
            if num2 == 0:
                raise ValueError("Cannot divide by zero.")
            numfrac = num1 * den2
            denfrac = den1 * num2
            return numfrac, denfrac
        except ValueError as e:
            print(e)
            num2 = int(input("Numerator for frac 2: Enter an integer (nonzero): "))

def menu():
    print("""
This program performs operations on fractions. Enter
1: To add fractions
2: To subtract fractions
3: To multiply fractions
4: To divide fractions
9: To exit the program
""")

def get_fraction():
    while True:
        try:
            numerator = int(input("Numerator: Enter an integer: "))
            denominator = int(input("Denominator: Enter an integer: "))
            if denominator == 0:
                raise ValueError("Denominator must be nonzero.")
            return numerator, denominator
        except ValueError as e:
            print(e)

def show_result(operation, num1, den1, num2, den2, numfrac, denfrac):
    print(f"{num1}/{den1} {operation} {num2}/{den2} = {numfrac}/{denfrac}")

if __name__ == "__main__":
    while True:
        menu()
        choice = int(input())
        if choice == 9:
            break

        print("For fraction 1")
        numerator1, denominator1 = get_fraction()

        print("For fraction 2")
        numerator2, denominator2 = get_fraction()

        # TODO: Add code here
        # exceptions for division by zero and various cases
        if choice == 1:
            numfrac, denfrac = add_fractions(numerator1, denominator1, numerator2, denominator2)
        elif choice == 2:
            numfrac, denfrac = subtract_fractions(numerator1, denominator1, numerator2, denominator2)
        elif choice == 3:
            numfrac, denfrac = multiply_fractions(numerator1, denominator1, numerator2, denominator2)
        elif choice == 4:
            numfrac, denfrac = divide_fractions(numerator1, denominator1, numerator2, denominator2)

        show_result(['+', '-', '*', '/'][choice-1], numerator1, denominator1, numerator2, denominator2, numfrac, denfrac)