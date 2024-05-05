#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <raylib.h>
#include "../include/tensor.h"
#include "../include/special-relativity.h"

using namespace std;

void DrawEvent(tsr::Vector4 event, Color color = GRAY){
    DrawCircle(event[1], -event[0], 2, color);
}
void DrawEntity(sr::entity entity, Color color = BLUE){
    for(int t = 0; t < 100; t++){
        entity.update_position(1);
        DrawCircle(-entity.get_position()[1], -t, 3, color);
    }
}
void DrawWorldLines(sr::spacetime spacetime, int screenWidth, int screenHeight){
    for(int i = -10; i < 10; i++){
        tsr::Vector4 startV(-screenHeight/2.0f, i*50, 0, 0);
        tsr::Vector4 finishV(screenHeight, i*50, 0, 0);
        startV = spacetime.get_fwrd()*startV;
        finishV = spacetime.get_fwrd()*finishV;
        DrawLine(startV[1], -startV[0], finishV[1], -finishV[0], GRAY);

        tsr::Vector4 startH(i*50, -screenWidth, 0, 0);
        tsr::Vector4 finishH(i*50, screenWidth, 0, 0);
        startH = spacetime.get_fwrd()*startH;
        finishH = spacetime.get_fwrd()*finishH;
        DrawLine(startH[1], -startH[0], finishH[1], -finishH[0], GRAY);
    }
    DrawLine(0, -screenHeight, 0, screenHeight, WHITE);     // x0 Ax |
    DrawLine(-screenWidth/2.0f, 0, screenWidth/2.0f, 0, WHITE);  // x1 Ax --
}
void DrawSpacetime(sr::spacetime spacetime, Color color = PINK){
    for(int i = 0; i < spacetime.get_event_size(); i++)
        DrawEvent(spacetime[i], color);
    for(int i = 0; i < spacetime.get_entity_size(); i++)
        DrawEntity(spacetime.get_entity(i), BLUE);
}

int main(){

    cout << "c: " << sr::get_c() << endl;
    sr::set_c(1);
    cout << "c: " << sr::get_c() << endl;

    sr::spacetime ref;
    for(int i = 0; i < 800; i++){
        ref.add_event(tsr::Vector4(i, 0, 0 ,0));
        ref.add_event(tsr::Vector4(i, i*0.5, 0 ,0));
        ref.add_event(tsr::Vector4(i, i*0.75, 0 ,0));
        ref.add_event(tsr::Vector4(i, i*0.714, 0 ,0));
    }
    sr::spacetime refPoints;
    for(int i = 0; i < 100; i++){
        refPoints.add_event(tsr::Vector4(i*50, 0, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, 50, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, -50, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, 100, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, -100, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, 150, 0, 0));
        refPoints.add_event(tsr::Vector4(i*50, -150, 0, 0));
    }
    ref.add_entity(0.5);
    ref.add_entity(0.75);

    const int screenWidth = 800;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "Hello world");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ screenWidth/2.0f, 4*screenHeight/5.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    double vel = 0;

    SetTargetFPS(60);

    while(WindowShouldClose() == false){
        if (IsKeyDown(KEY_RIGHT)) vel += 0.01/pow(sr::gamma(vel),2);
        else if (IsKeyDown(KEY_LEFT)) vel -= 0.01/pow(sr::gamma(vel),2);


        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
            DrawWorldLines(ref, screenWidth, screenHeight);
            for(int i = 0; i < 4*screenWidth/5.0f; i++){
                DrawPixel(i, -i, YELLOW);
                DrawPixel(-i, -i, YELLOW);
                refPoints.update_rFrame(vel);
                DrawEvent(refPoints[i]);
            }
        ref.update_rFrame(vel);
        DrawSpacetime(ref);
        EndMode2D();

        string text = "Velocity: " + to_string(vel*100) + "%";
        string text2 = "Gamma: " + to_string(sr::gamma(vel));
        string text3 = "Ent vel: " + to_string(ref.get_entity(0).get_velocity()[1]*100);
        DrawText(text.c_str(), 20, 20, 10, WHITE);
        DrawText(text2.c_str(), 20, 40, 10, WHITE);
        DrawText(text3.c_str(), 20, 60, 10, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
