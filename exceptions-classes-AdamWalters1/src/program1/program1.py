if __name__ == "__main__":
    str_invalid_input = "Invalid input. You must enter numbers."
    
    try:
        # TODO: Add code here
        num1 = float(input("Enter first number: "))
        num2 = float(input("Enter seconds number: "))
        opr = input("Enter an operator (+,-,*,/): ")
        
        print(str(num1)+" "+opr+" "+str(num2)+" = ")
        
        
            
        while True:
            try:
                if opr not in ["+","-","*","/"]:
                    raise ValueError
                result = eval(f"{num1}{opr}{num2}")
                break
            except ZeroDivisionError as e:
                print(e)
                num2 = float(input("Enter the divisor again"))
                
        print(result)
    except Exception:
        print(str_invalid_input)
        print("Program Terminates")
           
                