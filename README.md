# computer_graphics-hw4

## CGIP_hw5
---

### Prerequisites
#### 1. Visual Studio Code & Extensions
Visual Studio Code 설치 및 아래의 2개 확장 설치 필요

+ CMake

![CMake](https://github.com/bessrabel/computer_graphics-hw4/blob/main/readmePng/cmake.PNG)

+ CMake Tools

![CMake Tools](https://github.com/bessrabel/computer_graphics-hw4/blob/main/readmePng/cmakeTools.PNG)

#### 2. g++
Using GCC with MinGW

설치 참조: <https://code.visualstudio.com/docs/cpp/config-mingw#_create-hello-world> **PATH 추가 필수**

#### 3. CMake 
Using CMake

설치 참조: <https://cmake.org/download/> **version 3.29.2**

---

### Directory Layout
> + data
> + include
> + lib
> + src
> + readmePng
> + screenshot

#### data
bunny.obj 데이터가 들어있는 폴더(실제 빌드 시 CmakeList.txt 파일에 의해 같이 실행됨)

#### include & lib
라이브러리 폴더
+ GLFW (Version 3.3.bin.win32)
+ GLAD (gl: 4.6, profile: Core, extensions: none)
+ GLM (Version 0.9.9.6)
+ lib (libglfwdll.a & 실제 빌드 시 같이 실행되는 glfw3.dll)

#### readmePng
README.md 파일 이미지 첨부를 위한 폴더

#### screenshot
코드 실행 결과 스크린샷

#### src
소스 코드 폴더 (.cpp파일)
+ main.cpp : opengl을 실행하는 main 파일(transform 및 shading parameter를 설정하고 a)immediateMode, b) vertexArray 각각의 경우에 bunny.obj를 렌더링 하는 main 파일)  
+ frame_timer.cpp : fps 및 타이머를 설정하고 display() 함수에 rendering 관련 코드 작성 파일
+ load_mesh.cpp : bunny.obj를 로드하고 Triangle Mesh 형식으로 저장하는 파일
---

### compilation instructions

```
1. vscode를 실행 후, 다운받은 파일 폴더를 프로젝트 폴더로 선택 
2. 명령창(F1 단축키)으로 CMake:configure 명령 선택하여 운영체제에 맞는 컴파일러 도구(gcc 등) 선택
3. 다시 command를 입력할 수 있는 명령창을 열고 CMake:Build로 빌드(이때 CMakeList.txt 파일을 참고하여 자동으로 빌드됨)
4. 마지막으로 디버그(명령창 CMake:dubug or ctrl+ F5)하여 실행 결과를 확인
5. 실행 시 실행 터미널(실행 창)에 'Please enter the output result(exit: 0): a(ImmediateMode), b(VertexArrays)'라는 문구가 뜨면 원하는 출력결과 입력
    ex) a -> a(ImmediateMode)결과 창 출력
```

 ---
 
### result

+ ImmediateMode
  
![input_a](https://github.com/bessrabel/computer_graphics-hw4/blob/main/readmePng/input_a.PNG)

![unshaded](https://github.com/bessrabel/computer_graphics-hw4/blob/main/screenshot/a_immediateMode.PNG)
 
 ballpark values: 818FPS

+ VertexArrays

![input_b](https://github.com/bessrabel/computer_graphics-hw4/blob/main/readmePng/input_b.PNG)

![flatshading](https://github.com/bessrabel/computer_graphics-hw4/blob/main/screenshot/b_vertexArray.PNG)

 ballpark values: 376FPS

