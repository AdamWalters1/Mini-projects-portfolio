# main

import pygame
from player import Player
import sys
from obstacle import Obstacle
from obstacle import ObstacleCar
import random
from random import randint
import os
import time

# Initialize Pygame
pygame.init()

# Set up display
WIDTH, HEIGHT = 1200, 750
win = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Driving Among Idiots")

GREY = (128, 128, 128)  # RGB values for grey
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
DARK_GREY = (50, 50, 50)
D_GREY = (75, 75, 75)

car_images = []
for i in range(16):
    i +=1
    car_image = pygame.image.load(f'C:/Users/adamw/OneDrive/Documents/Comp Sci/DrivingAmongIdiots-adam/assets/cars___take2/cars-{i}.png').convert_alpha()
    car_images.append(car_image)
car1 = car_images[0:4]
car2 = car_images[4:8]
car3 = car_images[12:16]


# Define road grid
GRID_SIZE = 100  # Size of each grid square
ROAD_WIDTH = 60
NUM_ROWS = 8
NUM_COLS = 12

# Create grid layout (0 = road, 1 = building)
grid_layout = [
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],
]


buildings = []
for row in range(NUM_ROWS + 1):
    for col in range(NUM_COLS + 1):
        if grid_layout[row][col] == 1:
            building = Obstacle(col * GRID_SIZE, row * GRID_SIZE, GRID_SIZE+10, GREY)
            buildings.append(building)
            
# Create grid of roads
roads = []
for row in range(NUM_ROWS + 1):
    # Horizontal roads
    road_h = pygame.Rect(0, row * GRID_SIZE, WIDTH, ROAD_WIDTH)
    roads.append(road_h)
    
for col in range(NUM_COLS + 1):
    # Vertical roads
    road_v = pygame.Rect(col * GRID_SIZE, 0, ROAD_WIDTH, HEIGHT)
    roads.append(road_v)

# Obstacles
obstacles = [
    Obstacle(200, 300, 30, GREEN),  # Example tree
    Obstacle(600, 400, 20, WHITE)   # Example person
]

# Buildings as obstacles
#buildings = [
    #Obstacle(100, 0, 150, D_GREY),
    #Obstacle(300, 100, 100, D_GREY),
    #Obstacle(550, 100, 100, D_GREY),
    #Obstacle(100, 300, 100, D_GREY),
    #Obstacle(900, 450, 150, D_GREY),
    #Obstacle(600, 700, 50, D_GREY),
    #Obstacle(1000, 500, 100, D_GREY),
    #Obstacle(1100, 30, 150, D_GREY),
    #Obstacle(1050, 0, 200, D_GREY),
    #Obstacle(150, 650, 125, D_GREY),
#]

# Create obstacle cars
obstacle_cars = [
    ObstacleCar(100, 325, 50, 3, 'right', car1),
    ObstacleCar(100, 500, 50, 3, 'right', car3),
    ObstacleCar(300, 350, 50, 3, 'left', car2),
    ObstacleCar(525, 125, 50, 3, 'up', car1),
    ObstacleCar(550, 200, 50, 3, 'down', car2),
    ObstacleCar(700, 300, 50, 3, 'down', car3),
    ObstacleCar(800, 650, 50, 3, 'up', car2),
    ObstacleCar(900, 375, 50, 3, 'right',car2)
]

randomnum = randint(1,2)

player_size = 50
player_speed = 5
player = Player(WIDTH // 2 - player_size // 2 +20, HEIGHT // 2 - player_size // 2 + 10, player_size, player_speed, car_images)
# Initialize font
font = pygame.font.Font(None, 36)

# Initialize timer
start_time = time.time()

# Load background music and sound effects
if randomnum == 1:  
    # Replace all before the game name "DrivingAmongIdiots" with your file path
    # (Local file pathing wasnt working)
    background_music_path = 'C:/Users/adamw/OneDrive/Documents/Comp Sci/DrivingAmongIdiots-adam/assets/sounds/backgroundTraffic1.wav'
else:
    background_music_path = 'C:/Users/adamw/OneDrive/Documents/Comp Sci/DrivingAmongIdiots-adam/assets/sounds/backgroundTraffic2.wav'

effect_path = 'C:/Users/adamw/OneDrive/Documents/Comp Sci/DrivingAmongIdiots-adam/assets/sounds/passing.wav'

pygame.mixer.music.load(background_music_path)
pygame.mixer.music.play(-1)  # Play the background music in a loop

effect = pygame.mixer.Sound(effect_path)

def welcome_screen(win):
    font = pygame.font.Font(None, 74)
    title_text = font.render('Driving Among Idiots', True, (255, 0, 0))
    title_rect = title_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 50))

    start_font = pygame.font.Font(None, 36)
    start_text = start_font.render('Press Space to Start', True, (255, 255, 255))
    start_rect = start_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 50))

    win.fill((0, 0, 0))
    win.blit(title_text, title_rect)
    win.blit(start_text, start_rect)
    pygame.display.update()

    waiting_for_start = True
    while waiting_for_start:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    waiting_for_start = False
                    
# Game over screen, option to restart
def game_over_screen(win):
    font = pygame.font.Font(None, 74)
    text = font.render('Game Over', True, (255, 0, 0))
    text_rect = text.get_rect(center=(WIDTH // 2, HEIGHT // 2))

    restart_font = pygame.font.Font(None, 36)
    restart_text = restart_font.render('Press R to Restart', True, (255, 255, 255))
    restart_rect = restart_text.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 100))

    win.fill((0, 0, 0))
    win.blit(text, text_rect)
    win.blit(restart_text, restart_rect)
    pygame.display.update()

    waiting_for_restart = True
    while waiting_for_restart:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    waiting_for_restart = False
                    return True

    return False

# Main game loop
def main():
    pygame.init()
    win = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Driving Among Idiots")

    # Call the welcome screen
    welcome_screen(win)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()
        player.move(keys, obstacles, obstacle_cars)
        
        player.check_collision(obstacles + buildings, obstacle_cars)

        #if keys[pygame.K_UP] or keys[pygame.K_DOWN]:
            #effect.play()
        if player.damage >= player.max_damage:
            if game_over_screen(win):
                # Reset the game state
                player.x = WIDTH // 2 - player_size // 2 + 20  # Adjusted spawn point
                player.y = HEIGHT // 2 - player_size // 2
                player.angle = 0
                player.damage = 0

                # Reset obstacle cars
                for obstacle_car in obstacle_cars:
                    obstacle_car.crashed = False
                    # Optionally, reset positions or create new obstacle cars
                    obstacle_car.x = random.randint(0, WIDTH)
                    obstacle_car.y = random.randint(0, HEIGHT)
            else:
                game_over_screen(win)
                
        for obstacle_car in obstacle_cars:
            obstacle_car.move()
            
        elapsed_time = time.time() - start_time
        elapsed_minutes = int(elapsed_time // 60)
        elapsed_seconds = int(elapsed_time % 60)
        timer_text = f"Time: {elapsed_minutes:02}:{elapsed_seconds:02}"
    
        # background
        win.fill(WHITE)
        
        # Draw roads
        for row in range(NUM_ROWS):
            for col in range(NUM_COLS):
                if grid_layout[row][col] == 0:
                    road_rect = pygame.Rect(col * GRID_SIZE, row * GRID_SIZE, GRID_SIZE, GRID_SIZE)
                    pygame.draw.rect(win, DARK_GREY, road_rect)

        # Draw buildings
        for building in buildings:
            building.draw(win)

        for obstacle in obstacles:
            obstacle.draw(win)
            
        for obstacle_car in obstacle_cars:
            obstacle_car.draw(win)

        # Draw game objects
        player.draw(win)

        # Displaying damage
        font = pygame.font.SysFont(None, 36)
        damage_text = font.render(f"Damage: {player.damage}/{player.max_damage}", True, RED)
        win.blit(damage_text, (10, 10))

        timer_surface = font.render(timer_text, True, (0, 0, 0))
        win.blit(timer_surface, (1000, 10))
    
        pygame.display.update()  # Update display
        pygame.time.Clock().tick(30)
        
# Quit Pygame
    pygame.quit()
    sys.exit()
    
if __name__ == "__main__":
    main()
