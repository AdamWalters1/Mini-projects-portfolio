import tkinter as tk
from tkinter import messagebox

def convert_distance():
    """
    Converts the distance entered in kilometers to either nanometers or miles,
    based on the state of the checkbox.

    If the checkbox is checked, the distance is converted to nanometers.
    If the checkbox is not checked, the distance is converted to miles.

    The converted distance is displayed in the result_label widget.

    Raises:
        ValueError: If the value entered in the km_entry widget is not a valid number.
    """
    try:
        km = float(km_entry.get())
        if km <0:
            raise ValueError("You cant enter a negative number!")
        if convert_to_nm.get():
            result = km*1e12
            result_label.config(text=f"{result:.2e} nanometers")
        else:
            miles = km* 0.621371
            result_label.config(text=f"{miles} miles")
    except ValueError as e:
        messagebox.showerror("Invalid input. Try again!", e)
        km_entry.delete(0,tk.END)
# Create the main window
root = tk.Tk()
root.title("Distance Converter")
root.geometry("400x300")

km_entry = tk.Entry(root)
km_entry.pack(pady=10)

convert_to_nm = tk.BooleanVar()

nm_checkbutton = tk.Checkbutton(root,text="Convert to Nanometers",
                                variable=convert_to_nm,
                                onvalue=True,
                                offvalue=False)
nm_checkbutton.pack(pady=10)

convert_button = tk.Button(root,text="Convert",command=convert_distance)
convert_button.pack(pady=10)

result_label = tk.Label(root,text = "Enter a value and choose a conversion")
result_label.pack(pady=10)


# Start the GUI event loop
root.mainloop()
