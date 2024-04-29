#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

#include "scene.h"

class Unshaded{
    int Nx;
    int Ny;
    unsigned char* Image = NULL;
    
    public:
        Unshaded(int Nx, int Ny) : Nx(Nx), Ny(Ny) {};

        unsigned char* getImage(){ return Image; }

        void unshaded(Modeling model, Camera cam, PerspectiveProjection projection, Viewport view){
            Image = new unsigned char[Nx * Ny * 3] ();
            Scene s;
            s.create_scene(model, cam, projection, view);
            vec3* vertices = s.getVertices();
            int* gIndexBuffer = s.getGlndexBuffer();
            int gNumTriangles = s.getGNumTriangles();
            int gNumVertices = s.getGNumVertices();

            mat4 Mm = model.doModelingTransformation();
            mat4 Mcam = cam.doCameraTransformation();
            mat4 Mper = projection.doPerspectiveProjectionTransformation();
            mat4 Mvp = view.doViewportPositionTranformation();

            mat4 Mtrans = mulmat4(mulmat4(mulmat4(Mvp, Mper), Mcam), Mm); //순서대로 행렬 곱 계산

            // 픽셀당 DEPTHBUFFER를 저장할 배열
            vector<float> depthBuffer(Nx * Ny, -INFINITY);

            for(int i = 0; i < gNumTriangles; i++){
                int k0 = gIndexBuffer[3*i + 0]; 
                int k1 = gIndexBuffer[3*i + 1];
                int k2 = gIndexBuffer[3*i + 2];

                vec3 a = vertices[k0]; // 삼각형 꼭짓점 좌표 a
                vec3 b = vertices[k1]; // 삼각형 꼭짓점 좌표 b
                vec3 c = vertices[k2]; // 삼각형 꼭짓점 좌표 c

                a = w_normalize(mulmatvec4(Mtrans, a));
                b = w_normalize(mulmatvec4(Mtrans, b));
                c = w_normalize(mulmatvec4(Mtrans, c));

                // Bounding Rectangle
                int xmin = floor(std::min(std::min(a.x, b.x), c.x));
                int xmax = ceil(std::max(std::max(a.x, b.x), c.x));
                int ymin = floor(std::min(std::min(a.y, b.y), c.y));
                int ymax = ceil(std::max(std::max(a.y, b.y), c.y));
                
                // Barycentric Coordinates
                float beta = ((a.y - c.y)* xmin + (c.x - a.x) * ymin + a.x * c.y - c.x * a.y)/
                             ((a.y - c.y)* b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);
                float gamma = ((a.y - b.y)* xmin + (b.x - a.x) * ymin + a.x * b.y - b.x * a.y)/
                              ((a.y - b.y)* c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y); 

                // // incremental algorithm 
                float betax = (a.y - c.y) / ((a.y - c.y)* b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);
                float betay = (c.x - a.x) / ((a.y - c.y)* b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);
                float gammax = (a.y - b.y) / ((a.y - b.y)* c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);
                float gammay = (b.x - a.x) / ((a.y - b.y)* c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);
                int n = (xmax-xmin) + 1;

                for(int y = ymin; y <= ymax; y ++){
                    for(int x = xmin; x <= xmax; x ++){
                        if (beta > 0 && gamma > 0 && beta + gamma < 1){
                            float depth = (1-(beta+gamma)) * a.z + beta * b.z + gamma * c.z; // 픽셀 깊이 구하기 
                            if(depth > depthBuffer[y * Nx + x]) { //삼각형이 앞에 있으면 출력
                                depthBuffer[y * Nx + x] = depth;
                                for (int i = 0; i < 3; i ++){
                                    int idx = (y * Nx + x) * 3;
                                    Image[idx+i] = 255;
                                }
                            } 
                        }
                        beta += betax;
                        gamma += gammax;
                    }
                    beta += betay -n * betax;
                    gamma += gammay -n * gammax;
                }     
            }
        }
};