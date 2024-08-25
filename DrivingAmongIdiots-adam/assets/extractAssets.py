import pygame


# Initialize Pygame
pygame.init()

# Load the sprite sheet
car_sprite_sheet = pygame.image.load('cars.png').convert_alpha()

# Assume each car sprite is 64x64 pixels
CAR_WIDTH = 64
CAR_HEIGHT = 64

# Extract individual car images from the sprite sheet
car_images = []

for i in range(4):
    car_image = car_sprite_sheet.subsurface((i * CAR_WIDTH, 0, CAR_WIDTH, CAR_HEIGHT))
    car_images.append(car_image)
