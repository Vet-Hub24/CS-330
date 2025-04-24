#include <GLFW/glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

using namespace std;

const float DEG2RAD = 3.14159f / 180;

void processInput(GLFWwindow* window);

enum BRICKTYPE { REFLECTIVE, DESTRUCTABLE };
enum ONOFF { ON, OFF };

class Brick {
public:
    float red, green, blue;
    float x, y, width;
    int hitPoints = 2;
    BRICKTYPE brick_type;
    ONOFF onoff;

    Brick(BRICKTYPE bt, float xx, float yy, float ww, float rr, float gg, float bb)
    {
        brick_type = bt; x = xx; y = yy; width = ww; red = rr; green = gg; blue = bb;
        onoff = ON;
    };

    void drawBrick()
    {
        if (onoff == ON)
        {
            double halfside = width / 2;
            glColor3d(red, green, blue);
            glBegin(GL_POLYGON);
            glVertex2d(x + halfside, y + halfside);
            glVertex2d(x + halfside, y - halfside);
            glVertex2d(x - halfside, y - halfside);
            glVertex2d(x - halfside, y + halfside);
            glEnd();
        }
    }

    void hit()
    {
        hitPoints--;
        if (hitPoints <= 0) {
            onoff = OFF;
        }
        else {
            red *= 0.6f; green *= 0.6f; blue *= 0.6f; // dim color to show damage
        }
    }
};

class Circle {
public:
    float red, green, blue;
    float radius;
    float x, y;
    float speed = 0.03f;
    int direction; // 1=up 2=right 3=down 4=left 5=up-right 6=up-left 7=down-right 8=down-left

    Circle(float xx, float yy, float rr, int dir, float rad, float r, float g, float b)
    {
        x = xx; y = yy; radius = rad; direction = dir;
        red = r; green = g; blue = b;
    }

    void CheckCollision(Brick* brk)
    {
        if (brk->onoff == OFF) return;

        bool hit = (x > brk->x - brk->width && x <= brk->x + brk->width) &&
            (y > brk->y - brk->width && y <= brk->y + brk->width);
        if (hit)
        {
            if (brk->brick_type == REFLECTIVE)
            {
                direction = GetRandomDirection();
                x += 0.03f; y += 0.04f;
            }
            else if (brk->brick_type == DESTRUCTABLE)
            {
                brk->hit();
            }
        }
    }

    void CheckCircleCollision(Circle& other)
    {
        float dx = x - other.x;
        float dy = y - other.y;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < radius + other.radius)
        {
            red = 1.0f; green = 0.0f; blue = 0.0f; // visual feedback
            speed += 0.01f;
            direction = GetRandomDirection();
        }
    }

    int GetRandomDirection()
    {
        return (rand() % 8) + 1;
    }

    void MoveOneStep()
    {
        if (direction == 1 || direction == 5 || direction == 6) y -= speed;
        if (direction == 2 || direction == 5 || direction == 7) x += speed;
        if (direction == 3 || direction == 7 || direction == 8) y += speed;
        if (direction == 4 || direction == 6 || direction == 8) x -= speed;

        if (x < -1 + radius || x > 1 - radius) {
            direction = GetRandomDirection();
            speed += 0.005f;
        }
        if (y < -1 + radius || y > 1 - radius) {
            direction = GetRandomDirection();
            red = (float)(rand() % 100) / 100;
            green = (float)(rand() % 100) / 100;
            blue = (float)(rand() % 100) / 100;
        }
    }

    void DrawCircle()
    {
        glColor3f(red, green, blue);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float degInRad = i * DEG2RAD;
            glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
        }
        glEnd();
    }
};

vector<Circle> world;
Brick paddle(DESTRUCTABLE, 0.0f, -0.9f, 0.4f, 0.3f, 0.3f, 1.0f);

int main(void) {
    srand(time(NULL));
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(480, 480, "8-2 Assignment", NULL, NULL);
    if (!window) { glfwTerminate(); exit(EXIT_FAILURE); }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    vector<Brick> bricks;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 7; col++) {
            float x = -0.8f + col * 0.25f;
            float y = 0.8f - row * 0.2f;
            float size = 0.15f - (row * 0.01f);
            float r = (row % 2 == 0) ? 1.0f : 0.5f;
            float g = (col % 2 == 0) ? 0.5f : 1.0f;
            float b = 0.3f;
            BRICKTYPE type = (row + col) % 2 == 0 ? DESTRUCTABLE : REFLECTIVE;
            bricks.push_back(Brick(type, x, y, size, r, g, b));
        }
    }

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)  paddle.x -= 0.02f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) paddle.x += 0.02f;

        for (auto& circle : world) {
            for (auto& brick : bricks)
                circle.CheckCollision(&brick);
            for (auto& other : world)
                if (&circle != &other)
                    circle.CheckCircleCollision(other);
            circle.CheckCollision(&paddle);
            circle.MoveOneStep();
            circle.DrawCircle();
        }

        for (auto& brick : bricks)
            brick.drawBrick();
        paddle.drawBrick();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        float r = rand() / (float)RAND_MAX;
        float g = rand() / (float)RAND_MAX;
        float b = rand() / (float)RAND_MAX;
        Circle B(0, 0, 0.02f, 2, 0.05f, r, g, b);
        world.push_back(B);
    }
}