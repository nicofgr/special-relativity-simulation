#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>
#include "../include/tensor.h"
#include "../include/special-relativity.h"

using namespace std;

int main(){

    cout << "c: " << sr::get_c() << endl;
    sr::set_c(1);
    cout << "c: " << sr::get_c() << endl;

    sr::spacetime mainref;
    
    double velocity = 0.8;  // USAR % DE c
    double gam = sr::gamma(velocity);
    tsr::Vector4 gam4 = sr::gamma(velocity, velocity, velocity);
    double beta = velocity;
    tsr::Matrix4 matrixF( gam      , -gam*beta, 0, 0,
                    -gam*beta,       gam, 0, 0,
                    0        ,         0, 1, 0,
                    0        ,         0, 0, 1);
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
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello world");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawLine(screenWidth/2.0f, 0, screenWidth/2.0f, screenHeight, WHITE);
        DrawLine(0, screenHeight/2.0f, screenWidth, screenHeight/2.0f, WHITE);
        BeginMode2D(camera);
            for(int i = 0; i < screenWidth/2.0f; i++){
                DrawPixel(0, -i, GREEN);
                DrawPixel(20, -i, GREEN);
            }
            DrawRectangle(0,0,100,100,BLUE);
        EndMode2D();
        DrawRectangle(0,0,100,100,RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
