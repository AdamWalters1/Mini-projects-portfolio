import tkinter as tk
from tkinter import messagebox
from tkinter import scrolledtext
import datetime

def calculate_total(*args):
    """
    Calculates and updates the total charges based on selected services
    and car type price adjustments.
    
    This function should iterate over the service_vars dictionary to check
    which services have been selected. It should then calculate the total cost
    by applying the base cost and any car type adjustments. Finally, it should
    update the total_label widget to display the calculated total.
    
    *args is used here to allow this function to be called directly or by a trace.
    """
    # TODO: Implement the calculation of total charges
    tcost = 0.00
    if oilVar.get():
        tcost += 30.00
    if brakeVar.get():
        tcost += 20.00
    if radiatorVar.get():
        tcost += 40.00
    if transVar.get():
        tcost += 100.00
    if inspectVar.get():
        tcost += 35.00
    if clutchVar.get():
        tcost += 50.00
    if tireVar.get():
        tcost += 20.00
    
    if germanVar.get():
        tcost *= 1.75
    elif italianVar.get():
        tcost *= 2.50

    cost_label.config(text=f"Total Cost: ${tcost:.2f}")
    return tcost
def handle_german_car_check():
    """
    Handles the event where the German car checkbox is selected.
    
    When the German car checkbox is selected, this function should ensure that
    the Italian car checkbox is deselected (mutual exclusivity) and then
    recalculate the total charges.
    """
    if germanVar.get():
        italianVar = False
def handle_italian_car_check():
    """
    Handles the event where the Italian car checkbox is selected.
    
    Similar to the handle_german_car_check function, this ensures mutual exclusivity
    between the German and Italian car checkboxes and recalculates the total charges.
    """
    if italianVar.get():
        germanVar = False
def finalize_transaction():
    """
    Finalizes the transaction by calculating the total with tax, generating a receipt,
    and saving it to a file with a timestamp. It also notifies the user with the name
    of the file where the receipt was saved.
    
    This function should gather all necessary information, including selected services,
    total cost, tax, and customer comments, and then format and save this information
    to a text file. It should then display a message box to inform the user that the
    transaction has been finalized and the receipt has been saved.
    """
    total_cost = float(calculate_total())

    total_with_tax = total_cost * 1.07
    tax_amount = total_with_tax - total_cost

    receipt = f"Automotive Receipt\n"
    receipt += "Selected Services and Total:\n"
    receipt += f"Total Charges: ${total_cost:.2f}\n\n"
    receipt += f"Tax: ${tax_amount:.2f}\n"
    receipt += f"Total with Tax: ${total_with_tax:.2f}\n\n"
    receipt += "Customer Comments:\n" + comments_entry.get("1.0", tk.END)

    filename = f"receipt_{datetime.datetime.now().strftime('%Y%m%d%H%M%S')}.txt"
    with open(filename, 'w') as file:
        file.write(receipt)

    messagebox.showinfo("Transaction Complete", f"Receipt saved to {filename}")

    return total_cost

def electric_car_message():
    """
    Displays a message informing the user that services for electric cars are unavailable.
    
    This function is triggered when the "Click here if your car is electric" button is pressed.
    It should display a messagebox with an appropriate message regarding electric car services.
    """
    try:
        raise ValueError("We do not provide services for electric cars. You should've bought a manual Miata. Would've been cheaper and more fun")
    except ValueError as e:
        messagebox.showerror("Service Unavailable",e)
        
# Setup the main application window
root = tk.Tk()
root.title("Automotive Services")
root.geometry("400x600")

oilVar = tk.BooleanVar()
brakeVar = tk.BooleanVar()
radiatorVar = tk.BooleanVar()
transVar = tk.BooleanVar()
inspectVar = tk.BooleanVar()
clutchVar = tk.BooleanVar()
tireVar = tk.BooleanVar()
italianVar = tk.BooleanVar()
germanVar = tk.BooleanVar()
# TODO: Declare and initialize variables for services and car types
oil = tk.Checkbutton(root,text="Oil Change",
                                variable=oilVar,
                                onvalue=True,
                                offvalue=False)
oil.pack(pady=1,anchor=tk.W)
brake = tk.Checkbutton(root,text="Brake Fluid Flush",
                                variable=brakeVar,
                                onvalue=True,
                                offvalue=False)
brake.pack(pady=4, anchor=tk.W)
radiator = tk.Checkbutton(root,text="Radiator Flush",
                                variable=radiatorVar,
                                onvalue=True,
                                offvalue=False)
radiator.pack(pady=4, anchor=tk.W)
trans = tk.Checkbutton(root,text="Transmission Flush",
                                variable=transVar,
                                onvalue=True,
                                offvalue=False)
trans.pack(pady=4, anchor=tk.W)
inspect = tk.Checkbutton(root,text="Inspection",
                                variable=inspectVar,
                                onvalue=True,
                                offvalue=False)
inspect.pack(pady=4, anchor=tk.W)
clutch = tk.Checkbutton(root,text="Clutch Replacement",
                                variable=clutchVar,
                                onvalue=True,
                                offvalue=False)
clutch.pack(pady=4, anchor=tk.W)
tire = tk.Checkbutton(root,text="Tire Rotation",
                                variable=tireVar,
                                onvalue=True,
                                offvalue=False)
tire.pack(pady=4, anchor=tk.W)
# TODO: Create check buttons for each service and configure them to update the total charges when selected

# TODO: Create check buttons for German and Italian car types and configure them for mutual exclusivity
tk.Checkbutton(root, text="German", variable=germanVar, command=lambda: italianVar.set(False)).pack(anchor=tk.W)
tk.Checkbutton(root, text="Italian", variable=italianVar, command=lambda: germanVar.set(False)).pack(anchor=tk.W)


electricB = tk.Button(root,text="Electric Vehicle",command=electric_car_message)
electricB.pack(pady=4)

costButton = tk.Button(root,text="Check cost",command=calculate_total)
costButton.pack(pady=4)
# TODO: Create a text box for customer comments
comments_label = tk.Label(root, text="Customer Comments:")
comments_label.pack(anchor=tk.W)
comments_entry = tk.Text(root, height=5, width=50)
comments_entry.pack(anchor=tk.W)

# TODO: Create a label to display the total charges

# TODO: Create a button to finalize the transaction and generate a receipt
tk.Button(root, text="Finalize Transaction", command=finalize_transaction).pack(anchor=tk.W)

cost_label = tk.Label(root, text="Total Cost: $0.00")
cost_label.pack(anchor=tk.W)

root.mainloop()

