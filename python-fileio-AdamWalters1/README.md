# Python File I/O

![Assignment meme](images/1_Q55X1gfHjKi1knx96UVdZQ.png)
## Objectives

Refresher on working with files in Python.

## Program 1

Write a python program that reads data from the csv file `mythical_creatures.csv` and prints the data to the console.

The dataset contains the following information:

| Column          | Description                                 |
| --------------- | ------------------------------------------- |
| Creature        | The name of the creature                    |
| Type            | The type of creature                        |
| Strength        | The strength of the creature from 0-120     |
| Special Ability | Fire breath, healing, rebirth, etc.         |
| Intelligence    | The intelligence of the creature from 0-100 |

### Steps

1. Read the data from the csv file using the `csv` module.
2. Increase the strength of each creature by **10%**.
3. Add a new column `Wisdom` which is calculated as $0.5 \times intelligence$
4. Print the modified data to the console in a nicely formatted table.
5. Write the modified data to a new csv file `mythical_creatures_wisdom.csv`.

### Required Functions

- `read_csv`
- `write_csv`
- `print_data`

### Sample Output

```text
Creature   Type       Strength   Special Ability      Intelligence Wisdom    
Dragon     Fire       114.95     Fire Breath          80         40.0      
Unicorn    Magical    84.7       Healing              85         42.5      
Phoenix    Fire       102.85     Rebirth              78         39.0      
Griffin    Beast      96.8       Flight               70         35.0      
Mermaid    Aquatic    72.6       Siren Song           75         37.5      
Cyclops    Giant      108.9      Super Strength       40         20.0      
Banshee    Spectral   60.5       Wail                 65         32.5      
Centaur    Beast      90.75      Archery              60         30.0      
Minotaur   Giant      106.48     Labyrinth Guardian   55         27.5      
Goblin     Gremlin    54.45      Trickery             50         25.0      
```

## Program 2

Redo program 1 using the `pandas` module and only using the `read_csv` and `write_csv` functions.
