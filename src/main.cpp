#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <raylib.h>
#include "../include/tensor.h"
#include "../include/special-relativity.h"

using namespace std;

void DrawEvent(tsr::Vector4 event, Color color = RED){
    DrawCircle(event[1], -event[0], 2, color);
}
void DrawWorldLines(sr::spacetime spacetime, int screenWidth, int screenHeight){
    for(int i = -10; i < 10; i++){
        tsr::Vector4 start(-screenHeight/2.0f, i*50, 0, 0);
        tsr::Vector4 finish(screenHeight, i*50, 0, 0);
        start = spacetime.get_fwrd()*start;
        finish = spacetime.get_fwrd()*finish;
        DrawLine(start[1], -start[0], finish[1], -finish[0], GRAY);
    }
    DrawLine(0, -screenHeight, 0, screenHeight, WHITE);     // x0 Ax |
    DrawLine(-screenWidth/2.0f, 0, screenWidth/2.0f, 0, WHITE);  // x1 Ax --
}

int main(){

    cout << "c: " << sr::get_c() << endl;
    sr::set_c(1);
    cout << "c: " << sr::get_c() << endl;

    sr::spacetime mainref;
    
    double velocity = 0.8;  // USAR % DE c
    double gam = sr::gamma(velocity);
    tsr::Vector4 gam4 = sr::gamma(velocity, velocity, velocity);
    double beta = velocity;
    tsr::Matrix4 matrixF = sr::fwrd(velocity);
    tsr::Matrix4 matrixB( gam      , gam*beta, 0, 0,
                    gam*beta,       gam, 0, 0,
                    0        ,         0, 1, 0,
                    0        ,         0, 0, 1);
    
    //cout << matrix << endl;
    cout << "γ: " << gam << endl;
    cout << "β: " << beta << endl;
    tsr::Vector4 A(0, 0, 0, 0);     // Position A
    tsr::Vector4 B(0, 300, 0, 0);  // Position B
    tsr::Vector4 Ai = matrixF*A;
    tsr::Vector4 Bi = matrixF*B;
    cout << "Position B = " << B << endl;
    cout << "Position B' = " << matrixF*B << endl;
    cout << matrixF*tsr::Vector4(240,300,0,0) << endl;

    mainref.add_event(0,0,0,0);
    mainref.add_event(0,180,0,0);
    mainref.list_events();

    cout << "My time: 3 s" << endl;
    cout << "Particle time: "<< sr::own_time(3, velocity) << " s" << endl;
    cout << "My distance: 300 m" << endl;
    cout << "Particle distance: "<< sr::own_distance(300, velocity) << " m" << endl;
    
    sr::spacetime ref;
    for(int i = 0; i < 800; i++){
        ref.add_event(tsr::Vector4(i, 0, 0 ,0));
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
            sr::entity partA(20, 0, 0, 0.5, 0, 0);
            for(int i = 0; i < 4*screenWidth/5.0f; i++){
                DrawPixel(i, -i, YELLOW);
                DrawPixel(-i, -i, YELLOW);
                ref.update_rFrame(vel);
                DrawEvent(ref[i], PINK);
                refPoints.update_rFrame(vel);
                DrawEvent(refPoints[i], GRAY);
            }
        EndMode2D();

        string text = "Velocity: " + to_string(vel*100) + "%";
        string text2 = "Gamma: " + to_string(sr::gamma(vel));
        DrawText(text.c_str(), 20, 20, 10, WHITE);
        DrawText(text2.c_str(), 20, 40, 10, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
