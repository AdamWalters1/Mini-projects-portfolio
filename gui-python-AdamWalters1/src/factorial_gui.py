import tkinter as tk
from tkinter import messagebox
from math import factorial

def calculate_factorial():
    try:
        num = float(entry.get())
        if num <0:
            raise ValueError("You cant enter a negative number!")
        
        result = factorial(num)
        result_label.config(text=f"{result} ")
    except ValueError as e:
        messagebox.showerror("Invalid input. Try again!", e)
        entry.delete(0,tk.END)
def factorial(n):
    
    # single line to find factorial
    return 1 if (n==1 or n==0) else n * factorial(n - 1) 

# Create the main window
root = tk.Tk()
root.title("Factorial Calculator")
root.geometry("400x300")

# Create an entry widget for input
entry = tk.Entry(root)
entry.pack(pady=10)

# Create a button to calculate the factorial
calculate_button = tk.Button(root, text="Calculate Factorial", command=calculate_factorial)
calculate_button.pack(pady=10)

# Create a label to display the result
result_label = tk.Label(root, text="Result: ")
result_label.pack(pady=10)

# Start the GUI event loop
root.mainloop()

