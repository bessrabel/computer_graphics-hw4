#define _USE_MATH_DEFINES
#include <math.h>

#include "transformation.h"

class Scene{
    int     gNumVertices    = 0;    // Number of 3D vertices.
    int     gNumTriangles   = 0;    // Number of triangles.
    vec3*   vertices        = NULL;
    int*    gIndexBuffer    = NULL; // Vertex indices for the triangles.

    public: 
        Scene() {};

        vec3* getVertices(){ return vertices; }
        int* getGlndexBuffer(){ return gIndexBuffer; }
        int getGNumTriangles(){ return gNumTriangles; }
        int getGNumVertices(){ return gNumVertices; }

        void create_scene(Modeling model, Camera cam, PerspectiveProjection projection, Viewport view)
        {
            int width   = 32;
            int height  = 16;
            
            float theta, phi;
            int t;
            
            gNumVertices    = (height - 2) * width + 2;
            gNumTriangles   = (height - 2) * (width - 1) * 2;
            
            // TODO: Allocate an array for gNumVertices vertices.
            vertices        = new vec3[gNumVertices];
            gIndexBuffer    = new int[3*gNumTriangles];

            t = 0;
            for (int j = 1; j < height-1; ++j)
            {
                for (int i = 0; i < width; ++i)
                {
                    theta = (float) j / (height-1) * M_PI;
                    phi   = (float) i / (width-1)  * M_PI * 2;
                    
                    float   x   = sinf(theta) * cosf(phi);
                    float   y   = cosf(theta);
                    float   z   = -sinf(theta) * sinf(phi);

                    // TODO: Set vertex t in the vertex array to {x, y, z}.
                    vertices[t] = vec3(x,y,z);
                    t++;
                }
            }
            // TODO: Set vertex t in the vertex array to {0, 1, 0}.
            vertices[t] = vec3(0,1,0);;
            t++;
            
            // TODO: Set vertex t in the vertex array to {0, -1, 0}.
            vertices[t] = vec3(0,-1,0);
            t++;

            t = 0;
            for (int j = 0; j < height-3; ++j)
            {
                for (int i = 0; i < width-1; ++i)
                {
                    gIndexBuffer[t++] = j*width + i;
                    gIndexBuffer[t++] = (j+1)*width + (i+1);
                    gIndexBuffer[t++] = j*width + (i+1);
                    gIndexBuffer[t++] = j*width + i;
                    gIndexBuffer[t++] = (j+1)*width + i;
                    gIndexBuffer[t++] = (j+1)*width + (i+1);
                }
            }
            for (int i = 0; i < width-1; ++i)
            {
                gIndexBuffer[t++] = (height-2)*width;
                gIndexBuffer[t++] = i;
                gIndexBuffer[t++] = i + 1;
                gIndexBuffer[t++] = (height-2)*width + 1;
                gIndexBuffer[t++] = (height-3)*width + (i+1);
                gIndexBuffer[t++] = (height-3)*width + i;
            }
        }
};

