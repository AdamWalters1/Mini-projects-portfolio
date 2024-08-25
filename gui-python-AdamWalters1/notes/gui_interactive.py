import tkinter as tk

def perform_addition():
	"""
	Performs addition of two numbers entered in entry1 and entry2.
	Updates the result_label with the sum of the two numbers.
	"""
	number1 = int(entry1.get())
	number2 = int(entry2.get())
	result = number1 + number2
	result_label.config(text=f"Result: {result}")

# Create the main window
root = tk.Tk()
root.title("Simple Calculator")
root.geometry("400x300")

# Create entry widgets for numbers
entry1 = tk.Entry(root, font=('Arial', 16))
entry1.pack(pady=10)

entry2 = tk.Entry(root, font=('Arial', 16))
entry2.pack(pady=10)

# Create a button to perform addition
add_button = tk.Button(root, text="Add", command=perform_addition)
add_button.pack(pady=10)

# Create a label to display the result
result_label = tk.Label(root, text="Result: ", font=('Arial', 16))
result_label.pack(pady=20)

# Start the GUI event loop
root.mainloop()
