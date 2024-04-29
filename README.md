# computer_graphics-hw3

## CGIP_hw4
---

### Prerequisites
#### 1. Visual Studio Code & Extensions
Visual Studio Code 설치 및 아래의 2개 확장 설치 필요

+ CMake

![CMake](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/cmake.PNG)

+ CMake Tools

![CMake Tools](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/cmakeTools.PNG)

#### 2. g++
Using GCC with MinGW

설치 참조: <https://code.visualstudio.com/docs/cpp/config-mingw#_create-hello-world> **PATH 추가 필수**

#### 3. CMake 
Using CMake

설치 참조: <https://cmake.org/download/> **version 3.29.2**

---

### Directory Layout
> + include
> + lib
> + src
> + readmePng
> + screenshot

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
소스 코드 폴더 (.cpp파일 or .h파일)
+ main.cpp : opengl을 실행하는 main 파일, 원하는 출력결과에 따라 unshaded.cpp, flatshading.cpp, gouraudshading.cpp, phongshading.cpp를 호출함  
+ unshaded.cpp : transformation.h와 scene.h(기존 create_scene 파일)을 기반으로 main.cpp에 unshaded 수행 결과 Image 배열(픽셀당 컬러가 담긴 배열)로 반환
+ flatshading.cpp : transformation.h, scene.h, light.h, shade.h를 기반으로 main.cpp에 flatshading 수행 결과 Image 배열로 반환
+ gouraudshading.cpp: transformation.h, scene.h, light.h, shade.h를 기반으로 main.cpp에 gouraudshading 수행 결과 Image 배열로 반환
+ phongshading.cpp: transformation.h, scene.h, light.h, shade.h를 기반으로 main.cpp에 phongshading 수행 결과 Image 배열로 반환
+ light.h : 빛 정보(Light Class)가 담긴 헤더 파일
+ transformation.h : 모델링 변환 정보(Modeling, Camera, PerspectiveProjection, Viewport Class)가 담긴 헤더 파일
+ scene.h : 기존 create_scene.cpp 기반 여러 삼각형으로 이루어진 단위 구 만드는 파일 
+ shade.h : shade 관련 정보와 처리 수행 함수가 담긴 파일 
---

### compilation instructions

```
1. vscode를 실행 후, 다운받은 파일 폴더를 프로젝트 폴더로 선택 
2. 명령창(F1 단축키)으로 CMake:configure 명령 선택하여 운영체제에 맞는 컴파일러 도구(gcc 등) 선택
3. 다시 command를 입력할 수 있는 명령창을 열고 CMake:Build로 빌드(이때 CMakeList.txt 파일을 참고하여 자동으로 빌드됨)
4. 마지막으로 디버그(명령창 CMake:dubug or ctrl+ F5)하여 실행 결과를 확인
5. 실행 시 실행 터미널(실행 0창)에 '원하는 출력결과를 입력해주세요(종료 키: 0): a(unshaded), b(flatshading), c(gouraudshading), d(phongshading)'라는 문구가 뜨면 원하는 출력결과 입력
    ex) a -> a(unshaded)결과 창 출력
```

 ---
 
### result

+ unshaded
![input_a](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

![unshaded](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

+ flatshading
![input_b](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

![flatshading](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

+ gouraudshading
![input_c](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

![gouraudshading](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

+ phongshading
![input_d](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)

![phongshading](https://github.com/bessrabel/computer_graphics-hw2/blob/main/readmePng/unshaded.png)
 