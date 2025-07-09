#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <raylib.h>
// #include <stdbool>

#define FPS 30
#define LIFE_TIME 20
#define WIDTH 500
#define HEIGHT 60
#define FONT_SIZE 20
#define WINDOW_PADDING (FONT_SIZE*0.8)

#define BG_COLOR RAYWHITE
#define TEXT_COLOR BLACK

bool is_hover(Vector2 mouse_pos, int screen_width, int screen_height) {
    // TODO:
    return false;
}

void create_notification(const char *window_name, const char *text) {
    InitWindow(WIDTH, HEIGHT, window_name);

    int monitor = GetCurrentMonitor();
    int screen_width = GetMonitorWidth(monitor),
        screen_height = GetMonitorHeight(monitor);

    Rectangle window_pos = {
        .x= screen_width - WIDTH - WINDOW_PADDING,
        .y = screen_height-HEIGHT - WINDOW_PADDING,
        .width = WIDTH,
        .height = HEIGHT
    };

    SetConfigFlags(FLAG_WINDOW_TOPMOST);
    SetTargetFPS(FPS);
    SetWindowPosition(window_pos.x, window_pos.y);


    int frames_counter = 0;
    Vector2 mouse ={.x=(float)GetMouseX(), .y=(float)GetMouseY()};
    printf("%d\n", GetMouseX());
    while (!WindowShouldClose() && (is_hover(mouse, screen_width, screen_height) || frames_counter < LIFE_TIME*FPS )) {
        BeginDrawing();
        ClearBackground(is_hover(mouse, screen_width, screen_height) ? RED : BG_COLOR);
        char title [256]={0};
        sprintf(&title, "%s(%d)", window_name,LIFE_TIME - frames_counter/FPS); 
        SetWindowTitle(&title);
        int text_width = MeasureText(text, FONT_SIZE);
        DrawText(text, (WIDTH-text_width)/2,(HEIGHT-FONT_SIZE)/2 , FONT_SIZE, TEXT_COLOR);

        EndDrawing();

        frames_counter++;
    }

    CloseWindow();
}

int main() {
    const char *fifo_path = "/tmp/drawer_fifo";

    // Create FIFO if it doesn't exist
    mkfifo(fifo_path, 0777);

    char buffer[1024];
    printf("pg_notify drawer starting...\n");
    while (1) {
        int fd = open(fifo_path, O_RDONLY);
        if (fd < 0) {
            perror("Failed to open FIFO");
            exit(EXIT_FAILURE);
        }

        read(fd, buffer, sizeof(buffer));
        close(fd);

        char *window_name = strtok(buffer, ",");
        char *text = strtok(NULL, ",");
        if (window_name && text) {
            if(fork() == 0){
                create_notification(window_name, text);
            }
        }
    }

    return 0;
}
