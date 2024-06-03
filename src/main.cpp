#include <iostream>
#include <stdio.h>

#include <glad.h>
#include <glfw3.h>

using namespace std;

#include "frame_timer.cpp"

#define Nx 512
#define Ny 512

void glinit(){

    // transform
    glViewport(0, 0, 512, 512);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1000);
	
	glMatrixMode(GL_MODELVIEW); 
	glm::mat4 Mcam = glm::inverse(glm::mat4(1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     0, 0, 0, 1));
	glLoadMatrixf(mat4ToFloatPtr(Mcam)); //gllookat matrics
	glTranslatef(0.1, -1, -1.5);
	glScalef(10, 10, 10);
	
    //shading
	float ka[] = {1,1,1,1};
    float kd[] = {1,1,1,1};
    float ks[] = {0,0,0,1};
    float p = 0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, p);

    // light 
	glEnable(GL_LIGHTING);
    float Ia[] = {0.2, 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ia);

	glEnable(GL_LIGHT0);
	glm::vec3 a = normalize(glm::vec3(-1,-1,-1));
    float l[] = {-a.x, -a.y, -a.z, 0.0};
    // float l[] = {a.x, a.y, a.z,0};
    float la[] = {0.0, 0.0, 0.0, 1.0};
    float ld[] = {10, 10, 10, 1.0};
    float ls[] = {0.0, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, l); 
    glLightfv(GL_LIGHT0, GL_AMBIENT, la); 
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ld); 
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);
}

int main(){

    string input;

    while(true){
        cout << "Please enter the output result(exit: 0): a(ImmediateMode), b(VertexArrays)" << endl; 
        cin >> input;
        int mode;
        glfwInit();
        GLFWwindow* window;
        
        if (1 != input.length()){
            cout << "You entered incorrectly. Please re-enter!" << endl; 
            continue;
        }
        else{
            if(input[0] == 'a'){
                mode = 1;
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW5_(a)ImmediateMode 202372001_김소영", NULL, NULL);

            }
            else if(input[0] == 'b'){
                mode = 2;
                window = glfwCreateWindow(Nx, Ny, "CGIP_HW5_(b)VertexArrays 202372001_김소영", NULL, NULL);
            }
            else if(input[0] == '0'){
                break;
            }
            else{
                cout << "You entered incorrectly. Please re-enter!" << endl; 
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

        load_mesh("bunny.obj");
        init_timer();
        glinit();

        while(!glfwWindowShouldClose(window))
        {   
            display(window, mode); 
        }
        glfwTerminate();
    }
    return 0;
}