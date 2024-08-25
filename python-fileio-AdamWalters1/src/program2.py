import os
import pandas as pd

def read_csv(file_name):
    """
    Reads a CSV file and returns a DataFrame with added 'Wisdom' and updated 'Strength' columns.

    The function uses pandas to read the CSV file into a DataFrame. It then calculates a new 'Wisdom' column
    as half of the 'Intelligence' column, and updates the 'Strength' column by increasing its values by 10%.

    Parameters:
    file_name (str): The name of the CSV file to read.

    Returns:
    DataFrame: A DataFrame containing the data from the CSV file with added 'Wisdom' and updated 'Strength' columns.
    """
    df = pd.read_csv(file_name)
    df['Wisdom']=df['Intelligence']*0.5
    df['Strength']=df['Strength']*1.1
    return df
    pass

def write_csv(df, file_name):
    """
    Writes a DataFrame to a CSV file.

    The function uses pandas to write the DataFrame to a CSV file. The index of the DataFrame is not included in the output file.

    Parameters:
    df (DataFrame): The DataFrame to write to the CSV file.
    file_name (str): The name of the CSV file to write to.
    """
    df.to_csv(file_name,index=False)
    pass

if __name__ == "__main__":
    input_file_path = os.path.join('data','mythical_creatures.csv')
    output_file_path = os.path.join('data','mythical_creatures_wisdom.csv')
    df = read_csv(input_file_path)
    write_csv(df, output_file_path)
    print(df)