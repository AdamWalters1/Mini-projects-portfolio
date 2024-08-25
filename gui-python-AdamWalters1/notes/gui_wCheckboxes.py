import tkinter as tk

def show_selections():
	"""
	Updates the label text to show the selected hobbies based on the state of each checkbox.

	Returns:
		None
	"""
	selections = []
	# Check the state of each checkbox and add the hobby to the selections list if checked
	for hobby, var in hobbies.items():
		if var.get():
			selections.append(hobby)
	# Update the label text to show the selected hobbies
	selections_label.config(text="Selected hobbies: " + ", ".join(selections))

# Create the main window
root = tk.Tk()
root.title("Hobby Selector")
root.geometry("300x200")

# Dictionary to store hobbies and their associated BooleanVars
hobbies = {
    "Reading": tk.BooleanVar(),
    "Writing": tk.BooleanVar(),
    "Hiking": tk.BooleanVar(),
    "Cooking": tk.BooleanVar(),
    "Gaming": tk.BooleanVar()
}

# Create a Checkbutton for each hobby
for hobby, var in hobbies.items():
    tk.Checkbutton(root, text=hobby, variable=var).pack(anchor=tk.W)

# Create a button to show selections
show_button = tk.Button(root, text="Show Selections", command=show_selections)
show_button.pack(pady=10)

# Create a label to display the selected hobbies
selections_label = tk.Label(root, text="Selected hobbies: None")
selections_label.pack(pady=10)

# Start the GUI event loop
root.mainloop()
