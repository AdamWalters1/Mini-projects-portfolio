// Starter code for Project 3. Good luck!

/* TI includes */
#include <LcdDriver/Crystalfontz128x128_ST7735.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

/* Standard includes */
#include <stdio.h>
#include <stdbool.h>

/* HAL includes */
#include "HAL/Buzzer.h"
#include "HAL/Button.h"
#include "HAL/LED.h"
#include "HAL/Timer.h"
#include "HAL/TimerA.h"
#include "HAL/pitches.h"

// State machine definitions
typedef enum {
    STATE_TITLE,
    STATE_MENU,
    STATE_INSTRUCTIONS,
    STATE_GAME
} game_state_t;

// Menu options
typedef enum {
    MENU_PLAY,
    MENU_INSTRUCTIONS,
    MENU_COUNT
} menu_option_t;

// Building types
typedef enum {
    BUILDING_CURSOR,
    BUILDING_GRANDMA,
    BUILDING_FACTORY,
    BUILDING_COUNT
} building_type_t;

// Buy/Sell mode
typedef enum {
    MODE_BUY,
    MODE_SELL
} transaction_mode_t;

// Event types
typedef enum {
    EVENT_NONE,
    EVENT_GOLDEN_COOKIE,
    EVENT_COOKIE_STORM
} event_type_t;

// Building structure
typedef struct {
    const char* name;
    uint32_t quantity;              // Number of buildings owned
    uint64_t current_price;         // Current cost to buy next building
    uint32_t starting_price;        // Initial price
    uint32_t price_multiplier;     // Multiplier for price after each purchase
    uint32_t starting_multiplier;  // Cookies per second per building (base)
    uint32_t upgrade_multiplier;   // Multiplier applied per upgrade tier
    uint32_t generation_interval_ms; // Time between cookie generation (1s or 5s)
    uint32_t last_generation_time; // Last time this building generated cookies
} building_t;

// Upgrade structure
typedef struct {
    building_type_t building_type; // Which building this upgrade belongs to
    const char* name;
    uint32_t tier;                  // Current upgrade tier (0 = not purchased)
    uint64_t current_price;         // Current cost to buy next tier
    uint32_t starting_price;        // Initial price for tier 1
    uint32_t price_multiplier;     // Multiplier for price per tier
} upgrade_t;

// Application structure to hold game state
typedef struct {
    game_state_t current_state;
    menu_option_t menu_cursor;
    uint32_t title_start_time;
    bool screen_needs_redraw;
    bool game_loaded;
    // Joystick state for tap detection
    unsigned joystickX;
    unsigned joystickY;
    unsigned last_joystickY;
    unsigned last_joystickX;
    bool joystick_was_centered;
    uint32_t last_joystick_change_time;
    uint32_t last_up_tap_time;
    uint32_t last_down_tap_time;
    uint32_t last_left_tap_time;
    uint32_t last_right_tap_time;
    bool joystick_up_active;
    bool joystick_down_active;
    bool joystick_left_active;
    bool joystick_right_active;
    // Game state
    uint64_t cookie_count;
    uint32_t cookies_per_second;
    transaction_mode_t transaction_mode;
    building_type_t building_cursor;
    uint32_t upgrade_cursor;       // Index into upgrades array
    building_t buildings[BUILDING_COUNT];
    upgrade_t upgrades[BUILDING_COUNT]; // One upgrade per building
    // Event state
    event_type_t active_event;
    uint32_t event_start_time;
    uint32_t event_duration_ms;
    uint32_t last_event_spawn_time;
    uint32_t event_spawn_interval_ms;
    uint32_t base_cps_backup;  // For cookie storm event
} application_t;

// Constants
#define TITLE_SCREEN_DURATION_MS 2000
#define DEVELOPER_NAME "Adam Walters"
#define GAME_NAME "Cookie Clicker"

// Building configuration constants
#define CURSOR_STARTING_PRICE 2
#define CURSOR_PRICE_MULTIPLIER 2
#define CURSOR_STARTING_MULTIPLIER 2
#define CURSOR_UPGRADE_MULTIPLIER 2
#define CURSOR_GENERATION_INTERVAL_MS 1000

#define GRANDMA_STARTING_PRICE 2
#define GRANDMA_PRICE_MULTIPLIER 5
#define GRANDMA_STARTING_MULTIPLIER 10
#define GRANDMA_UPGRADE_MULTIPLIER 5
#define GRANDMA_GENERATION_INTERVAL_MS 5000

#define FACTORY_STARTING_PRICE 10
#define FACTORY_PRICE_MULTIPLIER 3
#define FACTORY_STARTING_MULTIPLIER 50
#define FACTORY_UPGRADE_MULTIPLIER 3
#define FACTORY_GENERATION_INTERVAL_MS 10000

// Upgrade configuration constants
#define CURSOR_UPGRADE_STARTING_PRICE 1
#define CURSOR_UPGRADE_PRICE_MULTIPLIER 5
#define GRANDMA_UPGRADE_STARTING_PRICE 2
#define GRANDMA_UPGRADE_PRICE_MULTIPLIER 10
#define FACTORY_UPGRADE_STARTING_PRICE 5
#define FACTORY_UPGRADE_PRICE_MULTIPLIER 7

// Event configuration constants
#define GOLDEN_COOKIE_DURATION_MS 10000  // 10 seconds to click
#define GOLDEN_COOKIE_REWARD_MULTIPLIER 100  // Gives 100x current CPS
#define COOKIE_STORM_DURATION_MS 15000  // 15 seconds
#define COOKIE_STORM_CPS_MULTIPLIER 3  // 3x CPS during storm
#define EVENT_SPAWN_INTERVAL_MIN_MS 30000  // Minimum 30 seconds between events
#define EVENT_SPAWN_INTERVAL_MAX_MS 90000  // Maximum 90 seconds between events

// Custom colors for pixelated retro style
#define COLOR_DARK_RED    0x800000  // Dark red background (RGB: 128, 0, 0)
#define COLOR_BRIGHT_BLUE 0x0080FF  // Bright blue for banners/text (RGB: 0, 128, 255)
#define COLOR_LIGHT_BLUE  0x40A0FF  // Light blue for some elements (RGB: 64, 160, 255)

// Function declarations
void initialize();
void initGraphics(Graphics_Context *g_sContext_p);
void main_loop(Graphics_Context *g_sContext_p, application_t *app);
void sleep();
void handleTitleState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons);
void handleMenuState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons);
void handleInstructionsState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons);
void handleGameState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons);
void handleGameBuzzer(application_t *app);
void handleGameCookieClick(application_t *app, buttons_t *buttons);
void handleGameCookieGeneration(application_t *app);
void handleGameNavigation(application_t *app);
void handleGameBuildingTransaction(application_t *app, buttons_t *buttons);
void handleGameUpgradeTransaction(application_t *app, buttons_t *buttons);
void drawTitleScreen(Graphics_Context *g_sContext_p);
void drawMenuScreen(Graphics_Context *g_sContext_p, application_t *app);
void drawInstructionsScreen(Graphics_Context *g_sContext_p);
void drawGameScreen(Graphics_Context *g_sContext_p, application_t *app);
void drawGameCookieSection(Graphics_Context *g_sContext_p, application_t *app);
void drawGameBuildingSection(Graphics_Context *g_sContext_p, application_t *app);
void drawGameUpgradeSection(Graphics_Context *g_sContext_p, application_t *app);
void drawBanner(Graphics_Context *g_sContext_p);  // Helper function for consistent banner
bool checkJoystickUp(application_t *app);
bool checkJoystickDown(application_t *app);
bool checkJoystickLeft(application_t *app);
bool checkJoystickRight(application_t *app);
uint32_t getCurrentTimeMs();
void initJoystick();
void sampleJoystick(application_t *app);
void initGameState(application_t *app);
uint64_t calculateBuildingPrice(building_t *building);
uint64_t calculateUpgradePrice(upgrade_t *upgrade);
void formatNumber(uint64_t value, char *buffer, uint8_t buffer_size);
uint32_t calculateCPS(application_t *app);
void updateEvents(application_t *app);
void spawnRandomEvent(application_t *app);
void handleEventClick(application_t *app);
void drawEvents(Graphics_Context *g_sContext_p, application_t *app);
uint32_t randomRange(uint32_t min, uint32_t max);

int main(void) {
    initialize();

    /* Graphics context. Works in the same as it did in the previous projects.
     You may choose to make a HAL struct and store the Graphics context in there
     instead. You may also choose to use the GFX struct from Guess the Color. */
    Graphics_Context g_sContext;
    initGraphics(&g_sContext);

    // Initialize joystick ADC
    initJoystick();
    
    // Initialize application state
    application_t app;
    app.current_state = STATE_TITLE;
    app.menu_cursor = MENU_PLAY;
    app.title_start_time = getCurrentTimeMs();
    app.screen_needs_redraw = true;
    app.game_loaded = false;
    app.joystickX = 8192;  // Center value (14-bit ADC range 0-16383)
    app.joystickY = 8192;
    app.last_joystickY = 8192;
    app.last_joystickX = 8192;
    app.joystick_was_centered = true;
    app.last_joystick_change_time = 0;
    app.last_up_tap_time = 0;
    app.last_down_tap_time = 0;
    app.last_left_tap_time = 0;
    app.last_right_tap_time = 0;
    app.joystick_up_active = false;
    app.joystick_down_active = false;
    app.joystick_left_active = false;
    app.joystick_right_active = false;
    
    // Initialize game state
    initGameState(&app);

    // Draw initial title screen before entering sleep loop
    drawTitleScreen(&g_sContext);
    
    // Small delay to ensure screen is drawn
    volatile uint32_t delay = 0;
    for (delay = 0; delay < 100000; delay++);

    // Run main loop once to initialize state
    main_loop(&g_sContext, &app);

    while (1) {
        sleep();

        main_loop(&g_sContext, &app);
    }
}

void sleep() {
    // The Launchpad Green LED is used to signify the processor is in low-power
    // mode. From the human perspective, it should seem the processor is always
    // asleep except for fractions of second here and there.

    TurnOn_LLG();
    // Enters the Low Power Mode 0 - the processor is asleep and only responds to
    // interrupts
    PCM_gotoLPM0();
    TurnOff_LLG();
}
void main_loop(Graphics_Context *g_sContext_p, application_t *app) {
    // Sample joystick ADC values
    sampleJoystick(app);
    
    // Update button tapping status
    buttons_t buttons = updateButtons();
    
    // Non-blocking code requirement: LB1 controls LL1
    if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) {
        TurnOn_LL1();  // Button pressed (active low)
    } else {
        TurnOff_LL1();  // Button released
    }

    // Handle state machine
    switch (app->current_state) {
        case STATE_TITLE:
            handleTitleState(g_sContext_p, app, &buttons);
            break;
        case STATE_MENU:
            handleMenuState(g_sContext_p, app, &buttons);
            break;
        case STATE_INSTRUCTIONS:
            handleInstructionsState(g_sContext_p, app, &buttons);
            break;
        case STATE_GAME:
            handleGameState(g_sContext_p, app, &buttons);
            break;
    }
}

// Initialization part is always device dependent and therefore does not change
// much with HAL
// State handler implementations
void handleTitleState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons) {
    // Draw title screen on first entry
    if (app->screen_needs_redraw) {
        drawTitleScreen(g_sContext_p);
        app->title_start_time = getCurrentTimeMs();
        app->screen_needs_redraw = false;
    }

    // Transition to menu on any interrupt (for HW9)
    // Also auto-transition after 2 seconds
    uint32_t elapsed = getCurrentTimeMs() - app->title_start_time;
    bool any_button_tapped = buttons->LB1tapped || buttons->LB2tapped || 
                            buttons->BB1tapped || buttons->BB2tapped || 
                            buttons->JSBtapped || checkJoystickUp(app) || checkJoystickDown(app);
    
    if (any_button_tapped || elapsed >= TITLE_SCREEN_DURATION_MS) {
        app->current_state = STATE_MENU;
        app->screen_needs_redraw = true;
    }
}

void handleMenuState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons) {
    // Draw menu screen if needed
    if (app->screen_needs_redraw) {
        drawMenuScreen(g_sContext_p, app);
        app->screen_needs_redraw = false;
    }

    // Handle joystick navigation (up/down taps)
    if (checkJoystickUp(app)) {
        app->menu_cursor = (app->menu_cursor == 0) ? (MENU_COUNT - 1) : (app->menu_cursor - 1);
        app->screen_needs_redraw = true;
    }
    if (checkJoystickDown(app)) {
        app->menu_cursor = (app->menu_cursor + 1) % MENU_COUNT;
        app->screen_needs_redraw = true;
    }

    // Handle JSB selection
    if (buttons->JSBtapped) {
        if (app->menu_cursor == MENU_PLAY) {
            app->current_state = STATE_GAME;
            app->screen_needs_redraw = true;
            app->game_loaded = false;
        } else if (app->menu_cursor == MENU_INSTRUCTIONS) {
            app->current_state = STATE_INSTRUCTIONS;
            app->screen_needs_redraw = true;
        }
    }
}

void handleInstructionsState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons) {
    // Draw instructions screen if needed
    if (app->screen_needs_redraw) {
        drawInstructionsScreen(g_sContext_p);
        app->screen_needs_redraw = false;
    }

    // Return to menu on JSB tap
    if (buttons->JSBtapped) {
        app->current_state = STATE_MENU;
        app->screen_needs_redraw = true;
    }
}

void handleGameBuzzer(application_t *app) {
    // On first load, play buzzer sound
    if (!app->game_loaded) {
        note_t note = Note_Construct(NOTE_C4, 1000, 0.5);
        Buzzer_Play(&note);
        app->game_loaded = true;
    }
    // Stop buzzer after duration expires
    if (app->game_loaded && HWTimer1Expired()) {
        Buzzer_Stop();
    }
}

void handleGameCookieClick(application_t *app, buttons_t *buttons) {
    // Handle cookie clicking (JSB tap = +1 cookie) or event clicking
    if (buttons->JSBtapped) {
        if (app->active_event == EVENT_GOLDEN_COOKIE) {
            handleEventClick(app);
        } else {
            app->cookie_count++;
            app->screen_needs_redraw = true;
        }
    }
}

void handleGameCookieGeneration(application_t *app) {
    // Handle automatic cookie generation
    uint32_t current_time = getCurrentTimeMs();
    uint32_t i;
    for (i = 0; i < BUILDING_COUNT; i++) {
        building_t *building = &app->buildings[i];
        if (building->quantity > 0) {
            uint32_t time_since_last = current_time - building->last_generation_time;
            if (time_since_last >= building->generation_interval_ms) {
                uint32_t base_cookies = building->starting_multiplier;
                upgrade_t *upgrade = &app->upgrades[i];
                uint32_t upgrade_mult = 1;
                uint32_t j;
                for (j = 0; j < upgrade->tier; j++) {
                    upgrade_mult *= building->upgrade_multiplier;
                }
                uint32_t cookies_per_building = base_cookies * upgrade_mult;
                uint32_t total_cookies = cookies_per_building * building->quantity;
                app->cookie_count += total_cookies;
                building->last_generation_time = current_time;
                app->screen_needs_redraw = true;
            }
        }
    }
    // Update CPS
    uint32_t new_cps = calculateCPS(app);
    if (new_cps != app->cookies_per_second) {
        app->cookies_per_second = new_cps;
        app->screen_needs_redraw = true;
    }
}

void handleGameNavigation(application_t *app) {
    // Handle building navigation (joystick up/down) - reversed
    if (checkJoystickUp(app)) {
        app->building_cursor = (app->building_cursor + 1) % BUILDING_COUNT;
        app->screen_needs_redraw = true;
    }
    if (checkJoystickDown(app)) {
        app->building_cursor = (app->building_cursor == 0) ? 
                              (BUILDING_COUNT - 1) : (app->building_cursor - 1);
        app->screen_needs_redraw = true;
    }
    // Handle upgrade navigation (joystick left/right)
    if (checkJoystickLeft(app)) {
        app->upgrade_cursor = (app->upgrade_cursor == 0) ? 
                             (BUILDING_COUNT - 1) : (app->upgrade_cursor - 1);
        app->screen_needs_redraw = true;
    }
    if (checkJoystickRight(app)) {
        app->upgrade_cursor = (app->upgrade_cursor + 1) % BUILDING_COUNT;
        app->screen_needs_redraw = true;
    }
}

void handleGameBuildingTransaction(application_t *app, buttons_t *buttons) {
    // Handle building purchase/sell (BB1)
    if (buttons->BB1tapped) {
        building_t *building = &app->buildings[app->building_cursor];
        if (app->transaction_mode == MODE_BUY) {
            uint64_t price = calculateBuildingPrice(building);
            if (app->cookie_count >= price) {
                upgrade_t *upgrade = &app->upgrades[app->building_cursor];
                bool upgrade_now_available = (building->quantity == 0);
                app->cookie_count -= price;
                building->quantity++;
                building->current_price = calculateBuildingPrice(building);
                // Play buzzer if upgrade just became available
                if (upgrade_now_available) {
                    uint16_t note_freq;
                    if (app->building_cursor == BUILDING_CURSOR) {
                        note_freq = NOTE_D4;
                    } else if (app->building_cursor == BUILDING_GRANDMA) {
                        note_freq = NOTE_G4;
                    } else {
                        note_freq = NOTE_A4;
                    }
                    note_t alert_note = Note_Construct(note_freq, 100, 0.5);
                    Buzzer_Play(&alert_note);
                    StartHWTimer1(100);
                }
                app->screen_needs_redraw = true;
            }
        } else {
            // Sell building
            if (building->quantity > 0) {
                uint64_t refund;
                if (building->quantity == 1) {
                    refund = building->starting_price;
                } else {
                    uint32_t temp_qty = building->quantity - 1;
                    refund = building->starting_price;
                    uint32_t j;
                    for (j = 0; j < temp_qty; j++) {
                        refund *= building->price_multiplier;
                    }
                }
                app->cookie_count += refund;
                building->quantity--;
                building->current_price = calculateBuildingPrice(building);
                app->screen_needs_redraw = true;
            }
        }
    }
}

void handleGameUpgradeTransaction(application_t *app, buttons_t *buttons) {
    // Handle upgrade purchase/sell (BB2)
    if (buttons->BB2tapped) {
        upgrade_t *upgrade = &app->upgrades[app->upgrade_cursor];
        building_t *building = &app->buildings[upgrade->building_type];
        if (app->transaction_mode == MODE_BUY) {
            if (building->quantity > 0) {
                uint64_t price = calculateUpgradePrice(upgrade);
                if (app->cookie_count >= price) {
                    app->cookie_count -= price;
                    upgrade->tier++;
                    upgrade->current_price = calculateUpgradePrice(upgrade);
                    app->screen_needs_redraw = true;
                }
            }
        } else {
            // Sell upgrade
            if (upgrade->tier > 0) {
                uint64_t refund;
                if (upgrade->tier == 1) {
                    refund = upgrade->starting_price;
                } else {
                    uint32_t temp_tier = upgrade->tier - 1;
                    refund = upgrade->starting_price;
                    uint32_t j;
                    for (j = 0; j < temp_tier; j++) {
                        refund *= upgrade->price_multiplier;
                    }
                }
                app->cookie_count += refund;
                upgrade->tier--;
                upgrade->current_price = calculateUpgradePrice(upgrade);
                app->screen_needs_redraw = true;
            }
        }
    }
}

void handleGameState(Graphics_Context *g_sContext_p, application_t *app, buttons_t *buttons) {
    handleGameBuzzer(app);
    sampleJoystick(app);
    handleGameCookieClick(app, buttons);
    updateEvents(app);
    handleGameCookieGeneration(app);
    handleGameNavigation(app);
    // Handle buy/sell mode toggle (LB1 or LB2)
    if (buttons->LB1tapped || buttons->LB2tapped) {
        app->transaction_mode = (app->transaction_mode == MODE_BUY) ? 
                                MODE_SELL : MODE_BUY;
        app->screen_needs_redraw = true;
    }
    handleGameBuildingTransaction(app, buttons);
    handleGameUpgradeTransaction(app, buttons);
    // Draw game screen if needed
    if (app->screen_needs_redraw) {
        drawGameScreen(g_sContext_p, app);
        drawEvents(g_sContext_p, app);
        app->screen_needs_redraw = false;
    }
}

void initialize() {
    // Stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    InitSystemTiming();

    initLEDs();
    initButtons();
    Buzzer_Init();
    // Joystick ADC initialization happens after graphics init
}

// Helper function to draw the banner consistently across screens
void drawBanner(Graphics_Context *g_sContext_p) {
    // Draw blue banner background
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_Rectangle bannerRect = {0, 0, 127, 16};
    Graphics_fillRectangle(g_sContext_p, &bannerRect);
    
    // Draw border around banner for definition
    Graphics_setForegroundColor(g_sContext_p, COLOR_LIGHT_BLUE);
    Graphics_Rectangle borderRect = {0, 0, 127, 16};
    Graphics_drawRectangle(g_sContext_p, &borderRect);
    
    // Draw "COOKIE CLICKER" title centered in banner
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_drawString(g_sContext_p, (int8_t*)"COOKIE CLICKER", -1, 20, 8, OPAQUE_TEXT);
}

void drawTitleScreen(Graphics_Context *g_sContext_p) {
    Graphics_clearDisplay(g_sContext_p);
    
    // Draw banner
    drawBanner(g_sContext_p);
    
    // Draw "IDLE GAME" below banner
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawString(g_sContext_p, (int8_t*)"IDLE GAME", -1, 40, 25, OPAQUE_TEXT);
    
    // Draw credits
    Graphics_drawString(g_sContext_p, (int8_t*)DEVELOPER_NAME, -1, 20, 50, OPAQUE_TEXT);
    
    // Draw simple cat graphic in bottom right
    int16_t cat_x = 100;
    int16_t cat_y = 100;
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    // Cat head (circle approximation)
    Graphics_drawCircle(g_sContext_p, cat_x, cat_y, 8);
    // Ears
    Graphics_drawLine(g_sContext_p, cat_x-6, cat_y-6, cat_x-4, cat_y-10);
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y-10, cat_x-2, cat_y-6);
    Graphics_drawLine(g_sContext_p, cat_x+2, cat_y-6, cat_x+4, cat_y-10);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y-10, cat_x+6, cat_y-6);
    // Eyes (dots)
    Graphics_fillCircle(g_sContext_p, cat_x-2, cat_y-2, 1);
    Graphics_fillCircle(g_sContext_p, cat_x+2, cat_y-2, 1);
    // Nose
    Graphics_drawLine(g_sContext_p, cat_x-1, cat_y+1, cat_x, cat_y+2);
    Graphics_drawLine(g_sContext_p, cat_x, cat_y+2, cat_x+1, cat_y+1);
    // Mouth
    Graphics_drawLine(g_sContext_p, cat_x, cat_y+2, cat_x, cat_y+4);
    // Whiskers
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y, cat_x-8, cat_y);
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y+2, cat_x-8, cat_y+3);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y, cat_x+8, cat_y);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y+2, cat_x+8, cat_y+3);
}

void drawMenuScreen(Graphics_Context *g_sContext_p, application_t *app) {
    Graphics_clearDisplay(g_sContext_p);
    
    // Draw banner
    drawBanner(g_sContext_p);
    
    // "IDLE GAME" below banner
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawString(g_sContext_p, (int8_t*)"IDLE GAME", -1, 40, 25, OPAQUE_TEXT);
    
    // Credits
    Graphics_drawString(g_sContext_p, (int8_t*)DEVELOPER_NAME, -1, 20, 40, OPAQUE_TEXT);
    
    // Draw menu options with cursor
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    int16_t play_y = 60;
    int16_t inst_y = 75;
    
    // Draw cursor at selected option
    int16_t cursor_y = (app->menu_cursor == MENU_PLAY) ? play_y : inst_y;
    Graphics_drawString(g_sContext_p, (int8_t*)">", -1, 20, cursor_y, OPAQUE_TEXT);
    
    // Draw menu items
    Graphics_drawString(g_sContext_p, (int8_t*)"Play", -1, 35, play_y, OPAQUE_TEXT);
    Graphics_drawString(g_sContext_p, (int8_t*)"Instructions", -1, 35, inst_y, OPAQUE_TEXT);
    
    // Draw simple cat graphic in bottom right
    int16_t cat_x = 100;
    int16_t cat_y = 100;
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawCircle(g_sContext_p, cat_x, cat_y, 8);
    Graphics_drawLine(g_sContext_p, cat_x-6, cat_y-6, cat_x-4, cat_y-10);
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y-10, cat_x-2, cat_y-6);
    Graphics_drawLine(g_sContext_p, cat_x+2, cat_y-6, cat_x+4, cat_y-10);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y-10, cat_x+6, cat_y-6);
    Graphics_fillCircle(g_sContext_p, cat_x-2, cat_y-2, 1);
    Graphics_fillCircle(g_sContext_p, cat_x+2, cat_y-2, 1);
    Graphics_drawLine(g_sContext_p, cat_x-1, cat_y+1, cat_x, cat_y+2);
    Graphics_drawLine(g_sContext_p, cat_x, cat_y+2, cat_x+1, cat_y+1);
    Graphics_drawLine(g_sContext_p, cat_x, cat_y+2, cat_x, cat_y+4);
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y, cat_x-8, cat_y);
    Graphics_drawLine(g_sContext_p, cat_x-4, cat_y+2, cat_x-8, cat_y+3);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y, cat_x+8, cat_y);
    Graphics_drawLine(g_sContext_p, cat_x+4, cat_y+2, cat_x+8, cat_y+3);
}

void drawInstructionsScreen(Graphics_Context *g_sContext_p) {
    Graphics_clearDisplay(g_sContext_p);
    
    // Draw banner
    drawBanner(g_sContext_p);
    
    // "IDLE GAME" below banner
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawString(g_sContext_p, (int8_t*)"IDLE GAME", -1, 40, 25, OPAQUE_TEXT);
    
    // Instructions in white text for better contrast
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    int16_t y_pos = 40;
    Graphics_drawString(g_sContext_p, (int8_t*)"JSB for Cookies.", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"JSB L/R to See Upgrade", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"JSB U/D to See Building", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"BB1 to B/S Building.", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"BB2 to B/S Upgrade.", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"LB1/LB2 to Switch", -1, 5, y_pos, OPAQUE_TEXT);
    y_pos += 12;
    Graphics_drawString(g_sContext_p, (int8_t*)"between Buy/Sell Mode.", -1, 5, y_pos, OPAQUE_TEXT);
    
    // Navigation instruction at bottom
    y_pos = 120;
    Graphics_drawString(g_sContext_p, (int8_t*)"JSB: Go Back", -1, 5, y_pos, OPAQUE_TEXT);
}

void drawGameCookieSection(Graphics_Context *g_sContext_p, application_t *app) {
    // Format cookie count and CPS
    char cookie_str[16];
    char cps_str[16];
    formatNumber(app->cookie_count, cookie_str, 16);
    formatNumber(app->cookies_per_second, cps_str, 16);
    
    // Top left: Cookie count with label
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    char cookie_display[32];
    snprintf(cookie_display, 32, "Cookies: %s", cookie_str);
    Graphics_drawString(g_sContext_p, (int8_t*)cookie_display, -1, 2, 4, OPAQUE_TEXT);
    
    // Left side: Cookie icon
    int16_t cookie_x = 32;
    int16_t cookie_y = 40;
    Graphics_setForegroundColor(g_sContext_p, COLOR_LIGHT_BLUE);
    Graphics_fillCircle(g_sContext_p, cookie_x, cookie_y, 18);
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawCircle(g_sContext_p, cookie_x, cookie_y, 18);
    Graphics_setForegroundColor(g_sContext_p, COLOR_DARK_RED);
    Graphics_fillCircle(g_sContext_p, cookie_x-7, cookie_y-8, 3);
    Graphics_fillCircle(g_sContext_p, cookie_x+7, cookie_y-8, 3);
    Graphics_fillCircle(g_sContext_p, cookie_x-10, cookie_y, 3);
    Graphics_fillCircle(g_sContext_p, cookie_x+10, cookie_y, 3);
    Graphics_fillCircle(g_sContext_p, cookie_x, cookie_y+8, 3);
    
    // CPS label and value
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawString(g_sContext_p, (int8_t*)"CPS", -1, 20, 65, OPAQUE_TEXT);
    Graphics_drawString(g_sContext_p, (int8_t*)cps_str, -1, 20, 75, OPAQUE_TEXT);
}

void drawGameBuildingSection(Graphics_Context *g_sContext_p, application_t *app) {
    // Draw building list frame
    Graphics_Rectangle buildingFrameRect = {55, 18, 127, 97};
    Graphics_drawRectangle(g_sContext_p, &buildingFrameRect);
    
    // Draw buildings with cursor highlighting
    int16_t build_y = 25;
    uint32_t i;
    for (i = 0; i < BUILDING_COUNT; i++) {
        building_t *building = &app->buildings[i];
        bool is_selected = (app->building_cursor == i);
        char qty_str[16];
        char price_str[16];
        formatNumber(building->quantity, qty_str, 16);
        uint64_t price = calculateBuildingPrice(building);
        formatNumber(price, price_str, 16);
        
        if (is_selected) {
            Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
            Graphics_drawString(g_sContext_p, (int8_t*)">", -1, 58, build_y, OPAQUE_TEXT);
        } else {
            Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
        }
        
        Graphics_drawString(g_sContext_p, (int8_t*)building->name, -1, 65, build_y, OPAQUE_TEXT);
        char qty_display[20];
        snprintf(qty_display, 20, " %s", qty_str);
        Graphics_drawString(g_sContext_p, (int8_t*)qty_display, -1, 95, build_y, OPAQUE_TEXT);
        Graphics_drawString(g_sContext_p, (int8_t*)"Cost:", -1, 58, build_y+10, OPAQUE_TEXT);
        Graphics_drawString(g_sContext_p, (int8_t*)price_str, -1, 87, build_y+10, OPAQUE_TEXT);
        build_y += 25;
    }
}

void drawGameUpgradeSection(Graphics_Context *g_sContext_p, application_t *app) {
    // UPGRADES section
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_drawString(g_sContext_p, (int8_t*)"UPGRADES", -1, 2, 105, OPAQUE_TEXT);
    
    upgrade_t *upgrade = &app->upgrades[app->upgrade_cursor];
    building_t *building = &app->buildings[upgrade->building_type];
    char upgrade_price_str[16];
    uint64_t upgrade_price = calculateUpgradePrice(upgrade);
    formatNumber(upgrade_price, upgrade_price_str, 16);
    
    Graphics_drawString(g_sContext_p, (int8_t*)building->name, -1, 2, 118, OPAQUE_TEXT);
    char tier_str[8];
    snprintf(tier_str, 8, "T%u", upgrade->tier);
    Graphics_drawString(g_sContext_p, (int8_t*)tier_str, -1, 55, 118, OPAQUE_TEXT);
    Graphics_drawString(g_sContext_p, (int8_t*)"<", -1, 70, 118, OPAQUE_TEXT);
    Graphics_drawString(g_sContext_p, (int8_t*)">", -1, 90, 118, OPAQUE_TEXT);
    
    if (building->quantity > 0) {
        Graphics_drawString(g_sContext_p, (int8_t*)upgrade_price_str, -1, 75, 118, OPAQUE_TEXT);
    } else {
        Graphics_drawString(g_sContext_p, (int8_t*)"N/A", -1, 75, 118, OPAQUE_TEXT);
    }
    
    // Buy/sell mode indicator
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    if (app->transaction_mode == MODE_BUY) {
        Graphics_drawString(g_sContext_p, (int8_t*)"BUY", -1, 2, 20, OPAQUE_TEXT);
    } else {
        Graphics_drawString(g_sContext_p, (int8_t*)"SELL", -1, 2, 20, OPAQUE_TEXT);
    }
}

void drawGameScreen(Graphics_Context *g_sContext_p, application_t *app) {
    Graphics_clearDisplay(g_sContext_p);
    drawGameCookieSection(g_sContext_p, app);
    drawGameBuildingSection(g_sContext_p, app);
    drawGameUpgradeSection(g_sContext_p, app);
}

void initJoystick() {
    // Initialize ADC for joystick (based on Proj2)
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_SYSOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1, 0);
    
    // Configure ADC for joystick X and Y
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    
    // Configure joystick X (A15) and Y (A9) channels
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, 
                                    ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);
    ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS, 
                                    ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);
    
    // Configure GPIO pins for joystick
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, 
                                               GPIO_TERTIARY_MODULE_FUNCTION); // X (A15)
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, 
                                               GPIO_TERTIARY_MODULE_FUNCTION); // Y (A9)
    
    // Start ADC conversion
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
    
    // Small delay to ensure ADC is ready
    volatile int delay = 0;
    for (delay = 0; delay < 10000; delay++);
}

void sampleJoystick(application_t *app) {
    // Read joystick values from ADC
    // With automatic iteration enabled, ADC continuously samples automatically
    app->joystickX = ADC14_getResult(ADC_MEM0);
    app->joystickY = ADC14_getResult(ADC_MEM1);
}

bool checkJoystickUp(application_t *app) {
    // Joystick center is around 8192 (14-bit ADC range 0-16383)
    // Lower Y values = joystick pushed UP
    const unsigned CENTER = 8192;
    const unsigned DEAD_ZONE = 1000;  // Larger dead zone to prevent accidental triggers
    const unsigned TAP_THRESHOLD = 2000;  // Higher threshold - requires more deliberate movement
    const uint32_t DEBOUNCE_TIME_MS = 400;  // Longer debounce to prevent rapid triggers
    
    uint32_t current_time = getCurrentTimeMs();
    
    // Check if joystick is pushed up
    bool currently_up = (app->joystickY < (CENTER - DEAD_ZONE));
    bool currently_centered = (app->joystickY >= (CENTER - DEAD_ZONE) && 
                               app->joystickY <= (CENTER + DEAD_ZONE));
    bool last_was_centered = (app->last_joystickY >= (CENTER - DEAD_ZONE) && 
                             app->last_joystickY <= (CENTER + DEAD_ZONE));
    
    bool tap_detected = false;
    
    // If joystick is currently up and we weren't tracking it before
    if (currently_up && !app->joystick_up_active) {
        unsigned offset = CENTER - app->joystickY;
        if (offset > TAP_THRESHOLD) {
            // Check debounce time since last tap
            uint32_t time_since_last = current_time - app->last_up_tap_time;
            if (time_since_last >= DEBOUNCE_TIME_MS) {
                tap_detected = true;
                app->last_up_tap_time = current_time;
                app->joystick_up_active = true;
            }
        }
    }
    
    // Reset active flag when joystick returns to center or moves away
    if (currently_centered || (!currently_up && app->joystick_up_active)) {
        app->joystick_up_active = false;
        // Update centered state
        if (currently_centered) {
            app->joystick_was_centered = true;
        }
    }
    
    app->last_joystickY = app->joystickY;
    return tap_detected;
}

bool checkJoystickDown(application_t *app) {
    // Joystick center is around 8192 (14-bit ADC range 0-16383)
    // Higher Y values = joystick pushed DOWN
    const unsigned CENTER = 8192;
    const unsigned DEAD_ZONE = 1000;  // Larger dead zone to prevent accidental triggers
    const unsigned TAP_THRESHOLD = 2000;  // Higher threshold - requires more deliberate movement
    const uint32_t DEBOUNCE_TIME_MS = 400;  // Longer debounce to prevent rapid triggers
    
    uint32_t current_time = getCurrentTimeMs();
    
    // Check if joystick is pushed down
    bool currently_down = (app->joystickY > (CENTER + DEAD_ZONE));
    bool currently_centered = (app->joystickY >= (CENTER - DEAD_ZONE) && 
                               app->joystickY <= (CENTER + DEAD_ZONE));
    bool last_was_centered = (app->last_joystickY >= (CENTER - DEAD_ZONE) && 
                             app->last_joystickY <= (CENTER + DEAD_ZONE));
    
    bool tap_detected = false;
    
    // If joystick is currently down and we weren't tracking it before
    if (currently_down && !app->joystick_down_active) {
        unsigned offset = app->joystickY - CENTER;
        if (offset > TAP_THRESHOLD) {
            // Check debounce time since last tap
            uint32_t time_since_last = current_time - app->last_down_tap_time;
            if (time_since_last >= DEBOUNCE_TIME_MS) {
                tap_detected = true;
                app->last_down_tap_time = current_time;
                app->joystick_down_active = true;
            }
        }
    }
    
    // Reset active flag when joystick returns to center or moves away
    if (currently_centered || (!currently_down && app->joystick_down_active)) {
        app->joystick_down_active = false;
        // Update centered state
        if (currently_centered) {
            app->joystick_was_centered = true;
        }
    }
    
    app->last_joystickY = app->joystickY;
    return tap_detected;
}

bool checkJoystickLeft(application_t *app) {
    // Joystick center is around 8192 (14-bit ADC range 0-16383)
    // Lower X values = joystick pushed LEFT
    const unsigned CENTER = 8192;
    const unsigned DEAD_ZONE = 1000;
    const unsigned TAP_THRESHOLD = 2000;
    const uint32_t DEBOUNCE_TIME_MS = 400;
    
    uint32_t current_time = getCurrentTimeMs();
    
    // Check if joystick is pushed left
    bool currently_left = (app->joystickX < (CENTER - DEAD_ZONE));
    bool currently_centered = (app->joystickX >= (CENTER - DEAD_ZONE) && 
                               app->joystickX <= (CENTER + DEAD_ZONE));
    
    bool tap_detected = false;
    
    // If joystick is currently left and we weren't tracking it before
    if (currently_left && !app->joystick_left_active) {
        unsigned offset = CENTER - app->joystickX;
        if (offset > TAP_THRESHOLD) {
            uint32_t time_since_last = current_time - app->last_left_tap_time;
            if (time_since_last >= DEBOUNCE_TIME_MS) {
                tap_detected = true;
                app->last_left_tap_time = current_time;
                app->joystick_left_active = true;
            }
        }
    }
    
    // Reset active flag when joystick returns to center or moves away
    if (currently_centered || (!currently_left && app->joystick_left_active)) {
        app->joystick_left_active = false;
    }
    
    app->last_joystickX = app->joystickX;
    return tap_detected;
}

bool checkJoystickRight(application_t *app) {
    // Joystick center is around 8192 (14-bit ADC range 0-16383)
    // Higher X values = joystick pushed RIGHT
    const unsigned CENTER = 8192;
    const unsigned DEAD_ZONE = 1000;
    const unsigned TAP_THRESHOLD = 2000;
    const uint32_t DEBOUNCE_TIME_MS = 400;
    
    uint32_t current_time = getCurrentTimeMs();
    
    // Check if joystick is pushed right
    bool currently_right = (app->joystickX > (CENTER + DEAD_ZONE));
    bool currently_centered = (app->joystickX >= (CENTER - DEAD_ZONE) && 
                               app->joystickX <= (CENTER + DEAD_ZONE));
    
    bool tap_detected = false;
    
    // If joystick is currently right and we weren't tracking it before
    if (currently_right && !app->joystick_right_active) {
        unsigned offset = app->joystickX - CENTER;
        if (offset > TAP_THRESHOLD) {
            uint32_t time_since_last = current_time - app->last_right_tap_time;
            if (time_since_last >= DEBOUNCE_TIME_MS) {
                tap_detected = true;
                app->last_right_tap_time = current_time;
                app->joystick_right_active = true;
            }
        }
    }
    
    // Reset active flag when joystick returns to center or moves away
    if (currently_centered || (!currently_right && app->joystick_right_active)) {
        app->joystick_right_active = false;
    }
    
    app->last_joystickX = app->joystickX;
    return tap_detected;
}

uint32_t getCurrentTimeMs() {
    return GetSystemTimeMs();
}

void initGameState(application_t *app) {
    // Initialize cookie count and CPS
    app->cookie_count = 0;
    app->cookies_per_second = 0;
    app->transaction_mode = MODE_BUY;
    app->building_cursor = BUILDING_CURSOR;
    app->upgrade_cursor = 0;
    // Initialize event state
    app->active_event = EVENT_NONE;
    app->event_start_time = 0;
    app->event_duration_ms = 0;
    app->last_event_spawn_time = getCurrentTimeMs();
    app->event_spawn_interval_ms = EVENT_SPAWN_INTERVAL_MIN_MS;
    app->base_cps_backup = 0;
    
    // Initialize Cursor building
    app->buildings[BUILDING_CURSOR].name = "Cursor";
    app->buildings[BUILDING_CURSOR].quantity = 0;
    app->buildings[BUILDING_CURSOR].starting_price = CURSOR_STARTING_PRICE;
    app->buildings[BUILDING_CURSOR].price_multiplier = CURSOR_PRICE_MULTIPLIER;
    app->buildings[BUILDING_CURSOR].starting_multiplier = CURSOR_STARTING_MULTIPLIER;
    app->buildings[BUILDING_CURSOR].upgrade_multiplier = CURSOR_UPGRADE_MULTIPLIER;
    app->buildings[BUILDING_CURSOR].generation_interval_ms = CURSOR_GENERATION_INTERVAL_MS;
    app->buildings[BUILDING_CURSOR].current_price = CURSOR_STARTING_PRICE;
    app->buildings[BUILDING_CURSOR].last_generation_time = getCurrentTimeMs();
    
    // Initialize Grandma building
    app->buildings[BUILDING_GRANDMA].name = "Grandma";
    app->buildings[BUILDING_GRANDMA].quantity = 0;
    app->buildings[BUILDING_GRANDMA].starting_price = GRANDMA_STARTING_PRICE;
    app->buildings[BUILDING_GRANDMA].price_multiplier = GRANDMA_PRICE_MULTIPLIER;
    app->buildings[BUILDING_GRANDMA].starting_multiplier = GRANDMA_STARTING_MULTIPLIER;
    app->buildings[BUILDING_GRANDMA].upgrade_multiplier = GRANDMA_UPGRADE_MULTIPLIER;
    app->buildings[BUILDING_GRANDMA].generation_interval_ms = GRANDMA_GENERATION_INTERVAL_MS;
    app->buildings[BUILDING_GRANDMA].current_price = GRANDMA_STARTING_PRICE;
    app->buildings[BUILDING_GRANDMA].last_generation_time = getCurrentTimeMs();
    
    // Initialize Factory building
    app->buildings[BUILDING_FACTORY].name = "Factory";
    app->buildings[BUILDING_FACTORY].quantity = 0;
    app->buildings[BUILDING_FACTORY].starting_price = FACTORY_STARTING_PRICE;
    app->buildings[BUILDING_FACTORY].price_multiplier = FACTORY_PRICE_MULTIPLIER;
    app->buildings[BUILDING_FACTORY].starting_multiplier = FACTORY_STARTING_MULTIPLIER;
    app->buildings[BUILDING_FACTORY].upgrade_multiplier = FACTORY_UPGRADE_MULTIPLIER;
    app->buildings[BUILDING_FACTORY].generation_interval_ms = FACTORY_GENERATION_INTERVAL_MS;
    app->buildings[BUILDING_FACTORY].current_price = FACTORY_STARTING_PRICE;
    app->buildings[BUILDING_FACTORY].last_generation_time = getCurrentTimeMs();
    
    // Initialize Cursor upgrade
    app->upgrades[BUILDING_CURSOR].building_type = BUILDING_CURSOR;
    app->upgrades[BUILDING_CURSOR].name = "C";
    app->upgrades[BUILDING_CURSOR].tier = 0;
    app->upgrades[BUILDING_CURSOR].starting_price = CURSOR_UPGRADE_STARTING_PRICE;
    app->upgrades[BUILDING_CURSOR].price_multiplier = CURSOR_UPGRADE_PRICE_MULTIPLIER;
    app->upgrades[BUILDING_CURSOR].current_price = CURSOR_UPGRADE_STARTING_PRICE;
    
    // Initialize Grandma upgrade
    app->upgrades[BUILDING_GRANDMA].building_type = BUILDING_GRANDMA;
    app->upgrades[BUILDING_GRANDMA].name = "G";
    app->upgrades[BUILDING_GRANDMA].tier = 0;
    app->upgrades[BUILDING_GRANDMA].starting_price = GRANDMA_UPGRADE_STARTING_PRICE;
    app->upgrades[BUILDING_GRANDMA].price_multiplier = GRANDMA_UPGRADE_PRICE_MULTIPLIER;
    app->upgrades[BUILDING_GRANDMA].current_price = GRANDMA_UPGRADE_STARTING_PRICE;
    
    // Initialize Factory upgrade
    app->upgrades[BUILDING_FACTORY].building_type = BUILDING_FACTORY;
    app->upgrades[BUILDING_FACTORY].name = "F";
    app->upgrades[BUILDING_FACTORY].tier = 0;
    app->upgrades[BUILDING_FACTORY].starting_price = FACTORY_UPGRADE_STARTING_PRICE;
    app->upgrades[BUILDING_FACTORY].price_multiplier = FACTORY_UPGRADE_PRICE_MULTIPLIER;
    app->upgrades[BUILDING_FACTORY].current_price = FACTORY_UPGRADE_STARTING_PRICE;
}

uint64_t calculateBuildingPrice(building_t *building) {
    // Price = starting_price * (price_multiplier ^ quantity)
    // For efficiency, we'll calculate incrementally
    if (building->quantity == 0) {
        return building->starting_price;
    }
    // Calculate: starting_price * (multiplier ^ quantity)
    uint64_t price = building->starting_price;
    uint32_t i;
    for (i = 0; i < building->quantity; i++) {
        price *= building->price_multiplier;
    }
    return price;
}

uint64_t calculateUpgradePrice(upgrade_t *upgrade) {
    // Price = starting_price * (price_multiplier ^ tier)
    if (upgrade->tier == 0) {
        return upgrade->starting_price;
    }
    uint64_t price = upgrade->starting_price;
    uint32_t i;
    for (i = 0; i < upgrade->tier; i++) {
        price *= upgrade->price_multiplier;
    }
    return price;
}

void formatNumber(uint64_t value, char *buffer, uint8_t buffer_size) {
    // Format numbers with k, M, B, T, Q, q prefixes
    // k = thousand, M = million, B = billion, T = trillion, Q = quadrillion, q = quintillion
    if (value < 1000) {
        snprintf(buffer, buffer_size, "%llu", (unsigned long long)value);
    } else if (value < 1000000) {
        // Thousands (k)
        uint32_t thousands = (uint32_t)(value / 1000);
        uint32_t remainder = (uint32_t)(value % 1000);
        if (remainder >= 100) {
            snprintf(buffer, buffer_size, "%u.%u%uk", thousands, remainder / 100, (remainder / 10) % 10);
        } else {
            snprintf(buffer, buffer_size, "%uk", thousands);
        }
    } else if (value < 1000000000) {
        // Millions (M)
        uint32_t millions = (uint32_t)(value / 1000000);
        uint32_t remainder = (uint32_t)((value % 1000000) / 10000);
        if (remainder > 0) {
            snprintf(buffer, buffer_size, "%u.%uM", millions, remainder);
        } else {
            snprintf(buffer, buffer_size, "%uM", millions);
        }
    } else if (value < 1000000000000ULL) {
        // Billions (B)
        uint32_t billions = (uint32_t)(value / 1000000000);
        uint32_t remainder = (uint32_t)((value % 1000000000) / 10000000);
        if (remainder > 0) {
            snprintf(buffer, buffer_size, "%u.%uB", billions, remainder);
        } else {
            snprintf(buffer, buffer_size, "%uB", billions);
        }
    } else if (value < 1000000000000000ULL) {
        // Trillions (T)
        uint64_t trillions = value / 1000000000000ULL;
        uint32_t remainder = (uint32_t)((value % 1000000000000ULL) / 10000000000ULL);
        if (remainder > 0) {
            snprintf(buffer, buffer_size, "%llu.%uT", (unsigned long long)trillions, remainder);
        } else {
            snprintf(buffer, buffer_size, "%lluT", (unsigned long long)trillions);
        }
    } else if (value < 1000000000000000000ULL) {
        // Quadrillions (Q)
        uint64_t quadrillions = value / 1000000000000000ULL;
        uint32_t remainder = (uint32_t)((value % 1000000000000000ULL) / 10000000000000ULL);
        if (remainder > 0) {
            snprintf(buffer, buffer_size, "%llu.%uQ", (unsigned long long)quadrillions, remainder);
        } else {
            snprintf(buffer, buffer_size, "%lluQ", (unsigned long long)quadrillions);
        }
    } else {
        // Quintillions (q)
        uint64_t quintillions = value / 1000000000000000000ULL;
        uint32_t remainder = (uint32_t)((value % 1000000000000000000ULL) / 100000000000000ULL);
        if (remainder > 0) {
            snprintf(buffer, buffer_size, "%llu.%uq", (unsigned long long)quintillions, remainder);
        } else {
            snprintf(buffer, buffer_size, "%lluq", (unsigned long long)quintillions);
        }
    }
}

uint32_t calculateCPS(application_t *app) {
    // Calculate cookies per second based on buildings and upgrades
    uint32_t total_cps = 0;
    uint32_t i;
    for (i = 0; i < BUILDING_COUNT; i++) {
        building_t *building = &app->buildings[i];
        if (building->quantity > 0) {
            // Base CPS per building
            uint32_t base_cps = building->starting_multiplier;
            
            // Apply upgrade multiplier
            upgrade_t *upgrade = &app->upgrades[i];
            uint32_t upgrade_mult = 1;
            uint32_t j;
            for (j = 0; j < upgrade->tier; j++) {
                upgrade_mult *= building->upgrade_multiplier;
            }
            
            // Total CPS for this building type = quantity * base_cps * upgrade_mult
            // But we need to account for generation interval
            // CPS = (base_cps * upgrade_mult * quantity) / (interval_ms / 1000)
            uint32_t cps_per_building = (base_cps * upgrade_mult * 1000) / building->generation_interval_ms;
            total_cps += cps_per_building * building->quantity;
        }
    }
    // Apply cookie storm multiplier if active
    if (app->active_event == EVENT_COOKIE_STORM) {
        total_cps *= COOKIE_STORM_CPS_MULTIPLIER;
    }
    return total_cps;
}

// Simple pseudo-random number generator using system time
uint32_t randomRange(uint32_t min, uint32_t max) {
    uint32_t time = getCurrentTimeMs();
    uint32_t range = max - min + 1;
    // Use time as seed, mix with some operations
    uint32_t rand = (time * 1103515245 + 12345) & 0x7FFFFFFF;
    return min + (rand % range);
}

void spawnRandomEvent(application_t *app) {
    // Randomly choose between golden cookie and cookie storm
    uint32_t event_choice = randomRange(0, 1);
    
    if (event_choice == 0) {
        // Spawn golden cookie
        app->active_event = EVENT_GOLDEN_COOKIE;
        app->event_start_time = getCurrentTimeMs();
        app->event_duration_ms = GOLDEN_COOKIE_DURATION_MS;
    } else {
        // Spawn cookie storm
        app->active_event = EVENT_COOKIE_STORM;
        app->event_start_time = getCurrentTimeMs();
        app->event_duration_ms = COOKIE_STORM_DURATION_MS;
        app->base_cps_backup = app->cookies_per_second;
    }
    app->screen_needs_redraw = true;
}

void handleEventClick(application_t *app) {
    if (app->active_event == EVENT_GOLDEN_COOKIE) {
        // Give reward: 100x current CPS
        uint64_t reward = (uint64_t)app->cookies_per_second * GOLDEN_COOKIE_REWARD_MULTIPLIER;
        if (reward < 100) reward = 100;  // Minimum reward
        app->cookie_count += reward;
        app->active_event = EVENT_NONE;
        app->screen_needs_redraw = true;
    }
}

void updateEvents(application_t *app) {
    uint32_t current_time = getCurrentTimeMs();
    
    // Check if current event has expired
    if (app->active_event != EVENT_NONE) {
        uint32_t elapsed = current_time - app->event_start_time;
        if (elapsed >= app->event_duration_ms) {
            // Event expired
            if (app->active_event == EVENT_COOKIE_STORM) {
                app->base_cps_backup = 0;
            }
            app->active_event = EVENT_NONE;
            app->screen_needs_redraw = true;
        }
    }
    
    // Check if we should spawn a new event
    if (app->active_event == EVENT_NONE) {
        uint32_t time_since_last = current_time - app->last_event_spawn_time;
        if (time_since_last >= app->event_spawn_interval_ms) {
            spawnRandomEvent(app);
            app->last_event_spawn_time = current_time;
            // Set next spawn interval randomly
            app->event_spawn_interval_ms = randomRange(EVENT_SPAWN_INTERVAL_MIN_MS, 
                                                       EVENT_SPAWN_INTERVAL_MAX_MS);
        }
    }
}

void drawEvents(Graphics_Context *g_sContext_p, application_t *app) {
    if (app->active_event == EVENT_GOLDEN_COOKIE) {
        // Draw golden cookie in top right area
        int16_t cookie_x = 100;
        int16_t cookie_y = 30;
        // Golden cookie (yellow/gold color - using bright colors)
        Graphics_setForegroundColor(g_sContext_p, 0xFFFF00);  // Yellow
        Graphics_fillCircle(g_sContext_p, cookie_x, cookie_y, 12);
        Graphics_setForegroundColor(g_sContext_p, 0xFFAA00);  // Orange-gold
        Graphics_drawCircle(g_sContext_p, cookie_x, cookie_y, 12);
        // Add sparkle effect (small dots)
        Graphics_setForegroundColor(g_sContext_p, 0xFFFFFF);  // White
        Graphics_fillCircle(g_sContext_p, cookie_x-4, cookie_y-4, 1);
        Graphics_fillCircle(g_sContext_p, cookie_x+4, cookie_y-4, 1);
        Graphics_fillCircle(g_sContext_p, cookie_x, cookie_y+4, 1);
        // Draw "Click!" text
        Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
        Graphics_drawString(g_sContext_p, (int8_t*)"Click!", -1, 90, 45, OPAQUE_TEXT);
    } else if (app->active_event == EVENT_COOKIE_STORM) {
        // Draw cookie storm indicator (text at top)
        Graphics_setForegroundColor(g_sContext_p, 0xFFFF00);  // Yellow
        Graphics_drawString(g_sContext_p, (int8_t*)"STORM!", -1, 50, 4, OPAQUE_TEXT);
        // Draw multiplier indicator
        char storm_str[16];
        snprintf(storm_str, 16, "%ux CPS", COOKIE_STORM_CPS_MULTIPLIER);
        Graphics_drawString(g_sContext_p, (int8_t*)storm_str, -1, 50, 14, OPAQUE_TEXT);
    }
}

void initGraphics(Graphics_Context *g_sContext_p) {
    // initializing the display
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // setting up the graphics
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(g_sContext_p, &g_sFontFixed6x8);

    // set colors - dark red background, blue text for retro style
    Graphics_setForegroundColor(g_sContext_p, COLOR_BRIGHT_BLUE);
    Graphics_setBackgroundColor(g_sContext_p, COLOR_DARK_RED);

    // apply changes by clearing background
    Graphics_clearDisplay(g_sContext_p);
}
