import tkinter as tk

def display_input():
	"""
	Updates the label text with the text entered in the entry widget.
	"""
	entered_text = entry.get()  # Get the text from entry widget
	label.config(text=entered_text)

# Create the main window
root = tk.Tk()
root.title("Simple Form")
root.geometry("400x300")

# Create an entry widget
entry = tk.Entry(root, font=('Arial', 16))
entry.pack(pady=20)

# Create a submit button
submit_button = tk.Button(root, text="Submit", command=display_input)
submit_button.pack(pady=10)

# Create a label widget to display the text from the entry widget
label = tk.Label(root, text="", font=('Arial', 16))
label.pack(pady=20)

# submit_button.bind('<Return>', display_input)

# Start the GUI event loop
root.mainloop()
