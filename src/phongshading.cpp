#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

#include "gouraudshading.cpp"

class Phongshading{
    int Nx;
    int Ny;
    Shade shade;
    unsigned char* Image = NULL;
    
    public:
        Phongshading(int Nx, int Ny, Shade shade) : Nx(Nx), Ny(Ny), shade(shade) {};

        unsigned char* getImage(){ return Image; }

        void phongShading(Modeling model, Camera cam, PerspectiveProjection projection, Viewport view){
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

            mat4 Mtrans = mulmat4(Mcam, Mm); //순서대로 행렬 곱 계산

            // 픽셀당 DEPTHBUFFER를 저장할 배열
            vector<float> depthBuffer(Nx * Ny, -INFINITY);

            for(int i = 0; i < gNumTriangles; i++){
                int k0 = gIndexBuffer[3*i + 0]; 
                int k1 = gIndexBuffer[3*i + 1];
                int k2 = gIndexBuffer[3*i + 2];

                // position
                vec3 a = vertices[k0];
                vec3 b = vertices[k1];
                vec3 c = vertices[k2];

                // Transform position
                mat4 Mtrans = mulmat4(Mcam, Mm);
                vec3 a_pre = w_normalize(mulmatvec4(Mtrans, a));
                vec3 b_pre = w_normalize(mulmatvec4(Mtrans, b));
                vec3 c_pre = w_normalize(mulmatvec4(Mtrans, c));

                // Transform normal
                vec3 n_a = shade.getGouraudNormal(a_pre, model.getCenter());
                vec3 n_b = shade.getGouraudNormal(b_pre, model.getCenter());
                vec3 n_c = shade.getGouraudNormal(c_pre, model.getCenter());

                // Project position
                Mtrans = mulmat4(Mvp, Mper);
                a = w_normalize(mulmatvec4(Mtrans, a_pre));
                b = w_normalize(mulmatvec4(Mtrans, b_pre));
                c = w_normalize(mulmatvec4(Mtrans, c_pre));

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

                // incremental algorithm 
                float betax = (a.y - c.y) / ((a.y - c.y)* b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);
                float betay = (c.x - a.x) / ((a.y - c.y)* b.x + (c.x - a.x) * b.y + a.x * c.y - c.x * a.y);
                float gammax = (a.y - b.y) / ((a.y - b.y)* c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);
                float gammay = (b.x - a.x) / ((a.y - b.y)* c.x + (b.x - a.x) * c.y + a.x * b.y - b.x * a.y);
                int n = (xmax-xmin) + 1;

                // Rasterization
                for(int y = ymin; y <= ymax; y ++){
                    for(int x = xmin; x <= xmax; x ++){
                        if (beta > 0 && gamma > 0 && beta + gamma < 1){
                            float depth = (1-(beta+gamma)) * a.z + beta * b.z + gamma * c.z; // Interpolate depth
                            vec3 point = (1-(beta+gamma)) * a_pre + beta * b_pre + gamma * c_pre;
                            vec3 normal = (1-(beta+gamma)) * n_a + beta * n_b + gamma * n_c; // Interpolate normal
                            // Shade using per-fragment normal
                            vec3 pixel_color = shade.phongShade(cam.getE(), normal, point);
                            if(depth > depthBuffer[y * Nx + x]) { // Write color if depth test passes
                                depthBuffer[y * Nx + x] = depth;
                                for (int i = 0; i < 3; i ++){
                                    int idx = (y * Nx + x) * 3;
                                    float pixel_gamma = 2.2;
                                    Image[idx+i] = pow(pixel_color[i] > 1 ? 1 : pixel_color[i], 1 / pixel_gamma)* 255; // Color (per-pixel)
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