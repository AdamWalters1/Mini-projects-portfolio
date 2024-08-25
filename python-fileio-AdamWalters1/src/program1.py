import os, csv

def read_csv(file_name):
    """
    Reads a CSV file and returns the header and data.

    The function opens the file in read mode, reads the header and appends a new column 'Wisdom'.
    For each row in the CSV file, it calculates the 'Strength' and 'Wisdom' values and appends them to the row.
    The modified row is then added to the 'creatures' list.

    Parameters:
    file_name (str): The name of the CSV file to read.

    Returns:
    list: A list containing the header and the data from the CSV file.
    """
    
    creatures = []

    with open(file_name, 'r') as file:
    
        csv_reader = csv.reader(file)
        header = next(csv_reader)
        header.append('Strength')
        header.append('Wisdom')
        
        for row in csv_reader:
            
            strength = int(float(row[2])*1.1)
            intelligence = float(row[4])
            wisdom = int(intelligence /2)
            
            row.append(strength)
            row.append(wisdom)
            creatures.append(row)
    return header, creatures
    pass

def write_csv(header, creatures, file_name):
    """
    Writes the header and data to a CSV file.

    The function opens the file in write mode and writes the header and data to the file.

    Parameters:
    header (list): The header to write to the CSV file.
    creatures (list): The data to write to the CSV file.
    file_name (str): The name of the CSV file to write to.
    """
    with open(file_name, 'w', newline = '') as file:
        
        csv.writer(file).writerow(header)
        csv.writer(file).writerows(creatures)
    pass

def print_data(header, creatures):
    """
    Prints the header and data.

    The function formats and prints the header and each row of data.

    Parameters:
    header (list): The header to print.
    creatures (list): The data to print.
    """
        
    format_string = "{:<12} {:<10} {:<10} {:<20} {:<12} {:<8}"

    # Print the formatted header
    print(format_string.format(*header))

    # Print the formatted data rows
    for creature in creatures:
        print(format_string.format(*creature))

    pass

if __name__ == "__main__":
    input_file_path = os.path.join('data','mythical_creatures.csv')

    output_file_path = os.path.join('data','mythical_creatures_wisdom.csv')

    header, creatures = read_csv(input_file_path)
    write_csv(header, creatures, output_file_path)
    print_data(header, creatures)
