# Player
import pygame
import time

class Player:
    def __init__(self, x, y, size, speed, car_images):
        self.x = x
        self.y = y
        self.size = size
        self.speed = speed
        self.car_images = car_images
        self.direction = 1
        self.current_speed = 0
        self.angle = 0  # Angle in degrees (0, 90, 180, 270)
        self.damage = 0
        self.max_damage = 100
        self.last_collision_time = 0
        self.collision_cooldown = 2  # Cooldown period in seconds
        self.last_turn_time = 0
        self.turn_cooldown = 1  # Cooldown period in seconds between turns
        self.crashed = False
        self.image = car_images[9]
        self.rect = self.image.get_rect(center=(self.x,self.x))
        self.collision_occured = False
        
    def move(self, keys, obstacles, obstacle_cars):
        if self.crashed:
            return

        if keys[pygame.K_UP]:
            self.current_speed = self.speed
        elif keys[pygame.K_DOWN]:
            self.current_speed = -self.speed
        else:
            self.current_speed = 0
        if keys[pygame.K_LEFT] and time.time() - self.last_turn_time > self.turn_cooldown:
            self.angle = (self.angle - 90) % 360
            self.last_turn_time = time.time()
        elif keys[pygame.K_RIGHT] and time.time() - self.last_turn_time > self.turn_cooldown:
            self.angle = (self.angle + 90) % 360
            self.last_turn_time = time.time()

        new_x = self.x
        new_y = self.y
        
        if self.angle == 0:
            self.y += self.current_speed
            self.direction = 11
        elif self.angle == 90:
            self.x += self.current_speed
            self.direction = 10
        elif self.angle == 180:
            self.y -= self.current_speed
            self.direction = 12
        elif self.angle == 270:
            self.x -= self.current_speed
            self.direction = 9
        
        new_rect = pygame.Rect(new_x, new_y, self.size, self.size)
        self.collision_occured = False
        
        for obstacle in obstacles:
            if new_rect.colliderect(obstacle.rect):
                self.collision_occurred = True
                break

        for obstacle_car in obstacle_cars:
            if new_rect.colliderect(obstacle_car.rect):
                self.collision_occurred = True
                break

        if self.collision_occurred:
            self.x, self.y = self.avoid_collision(self.x, self.y, new_rect, obstacles, obstacle_cars)
            
        self.rect.topleft = (self.x, self.y)
        self.x = max(0, min(self.x, 1200 - self.size))
        self.y = max(0, min(self.y, 750 - self.size))

    def draw(self, surface):
        car_image = self.car_images[self.direction-1]
        surface.blit(car_image, (self.x, self.y))

    def check_collision(self, obstacles, obstacle_cars):
        # Check collision with obstacles
        for obstacle in obstacles:
            if self.rect.colliderect(obstacle.rect):
                if time.time() - self.last_collision_time > self.collision_cooldown:
                    self.damage += 10
                    self.last_collision_time = time.time()
                break

        # Check collision with obstacle cars
        for obstacle_car in obstacle_cars:
            if self.rect.colliderect(obstacle_car.rect):
                if time.time() - self.last_collision_time > self.collision_cooldown:
                    self.damage += 20
                    self.last_collision_time = time.time()
                    obstacle_car.crashed = True
                    
                    break
                
    def avoid_collision(self, x, y, player_rect, obstacles, obstacle_cars):
        
        # Calculate the distance between the player and the obstacle
        for obstacle in obstacles:
            if player_rect.colliderect(obstacle.rect):
                dx = player_rect.centerx - obstacle.rect.centerx
                dy = player_rect.centery - obstacle.rect.centery

                if abs(dx) > abs(dy):
                    if dx > 0:
                        x = obstacle.rect.right
                    else:
                        x = obstacle.rect.left - self.size
                else:
                    if dy > 0:
                        y = obstacle.rect.bottom
                    else:
                        y = obstacle.rect.top - self.size
        for obstacle_car in obstacle_cars:
            if player_rect.colliderect(obstacle_car.rect):
                dx = player_rect.centerx - obstacle_car.rect.centerx
                dy = player_rect.centery - obstacle_car.rect.centery

                if abs(dx) > abs(dy):
                    if dx > 0:
                        x = obstacle_car.rect.right
                    else:
                        x = obstacle_car.rect.left - self.size
                else:
                    if dy > 0:
                        y = obstacle_car.rect.bottom
                    else:
                        y = obstacle_car.rect.top - self.size

        return x, y
    def spawn_new_car(self):
        # Randomly generate new coordinates for the obstacle car
        x = random.randint(0, 1200 - self.size)
        y = random.randint(0, 750 - self.size)
        return x, y

    