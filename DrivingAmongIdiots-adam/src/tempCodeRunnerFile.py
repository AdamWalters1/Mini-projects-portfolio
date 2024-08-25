for row in range(NUM_ROWS + 1):
    # Horizontal roads
    road_h = pygame.Rect(0, row * GRID_SIZE, WIDTH, ROAD_WIDTH)
    roads.append(road_h)
    
for col in range(NUM_COLS + 1):
    # Vertical roads
    road_v = pygame.Rect(col * GRID_SIZE, 0, ROAD_WIDTH, HEIGHT)
    roads.append(road_v)
