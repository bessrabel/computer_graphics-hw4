#include <iostream>
#include <stdio.h>

#include <glad.h>
#include <glfw3.h>

using namespace std;

#include "phongShading.cpp"

#define Nx 512
#define Ny 512

unsigned char* Image;

int main(){

    Modeling model = {2, vec3(0,0,-7)};
    Camera cam = {vec3(0,0,0), vec3(1,0,0), vec3(0,1,0), vec3(0,0,1)};
    PerspectiveProjection projection = {-0.1, 0.1, -0.1, 0.1, -0.1, -1000};
    Viewport view= {Nx, Ny};

    Light light = {vec3(-4,4,-3), vec3(1,1,1), 0.2}; 
    Shade shade = {vec3(0,1,0), vec3(0,0.5,0), vec3(0.5,0.5,0.5), 32, light};
    
    string input;

    while(true){
        cout << "원하는 출력결과를 입력해주세요(종료 키: 0): a(unshaded), b(flatshading), c(gouraudshading), d(phongshading)" << endl; 
        cin >> input;
        
        glfwInit();
        GLFWwindow* window;
        
        if (1 != input.length()){
            cout << "잘못 입력하셨습니다. 다시 입력해주세요!" << endl; 
            continue;
        }
        else{
            if(input[0] == 'a'){
                Unshaded unshade(Nx, Ny);
                unshade.unshaded(model, cam, projection, view);
                Image = unshade.getImage();
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW4_(a)Unshaded 202372001_김소영", NULL, NULL);

            }
            else if(input[0] == 'b'){
                Flatshading flat(Nx, Ny, shade);
                flat.flatShading(model, cam, projection, view);
                Image = flat.getImage();
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW4_(a)Flat shading 202372001_김소영", NULL, NULL);
            }
            else if(input[0] == 'c'){
                Gouraudshading gouraud(Nx, Ny, shade);
                gouraud.gouraudShading(model, cam, projection, view);
                Image = gouraud.getImage();
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW4_(c)Gouraud(per-vertex) shading 202372001_김소영", NULL, NULL);
            }
            else if(input[0] == 'd'){
                Phongshading phong(Nx, Ny, shade);
                phong.phongShading(model, cam, projection, view);
                Image = phong.getImage();
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW4_(d)Phong(per-pixel) shading 202372001_김소영", NULL, NULL);
            }
            else if(input[0] == '0'){
                break;
            }
            else{
                cout << "잘못 입력하셨습니다. 다시 입력해주세요!" << endl; 
                continue;
            }
        }
        
        if(window == NULL) 
        {
            cout << "Failed to create GLFW window" << endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
            return -1;
        }   

        while(!glfwWindowShouldClose(window))
        {   
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glad_glDrawPixels(Nx, Ny, GL_RGB, GL_UNSIGNED_BYTE, Image);
            glfwSwapBuffers(window);
            glfwPollEvents();     
        }
        glfwTerminate();
    }
    return 0;
}