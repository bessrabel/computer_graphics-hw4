#include <glm.hpp>
using namespace glm;

class Modeling {
    float scale;
    vec3 transform;

    public:
        Modeling(int scale, vec3 transform) : scale(scale), transform(transform){}

        vec3 getCenter() { return transform; }
        
        mat4 doModelingTransformation(){
            mat4 Mm = mat4(scale, 0.f, 0.f, transform.x,
                           0.f, scale, 0.f, transform.y,
                           0.f, 0.f, scale, transform.z,
                           0.f, 0.f, 0.f, 1.f);
            return Mm; 
        }
};

class Camera {
    vec3 e;
    vec3 u;
    vec3 v;
    vec3 w;

    public:
        Camera(vec3 e, vec3 u, vec3 v, vec3 w) : e(e), u(u), v(v), w(w) {}

        vec3 getE() { return e; }

        mat4 doCameraTransformation(){
            mat4 Mcam = inverse(mat4(u.x, v.x, w.x, e.x,
                                     u.y, v.y, w.y, e.y,
                                     u.z, v.z, w.z, e.z,
                                     0, 0, 0, 1));
            return Mcam; 
        }
};

class PerspectiveProjection {
    float l;
    float r;
    float b;
    float t;
    float n;
    float f;
    
    public:
        PerspectiveProjection(float l, float r, float b, float t, float n, float f) : l(l), r(r), b(b), t(t), n(n), f(f) {}

        mat4 doPerspectiveProjectionTransformation(){
            mat4 Mper = mat4(2*n/(r-l), 0.f, (l+r)/(l-r), 0.f,
                              0.f, 2*n/(t-b), (b+t)/(b-t), 0.f,
                              0.f, 0.f, (f+n)/(n-f), 2*f*n/(f-n),
                              0.f, 0.f, 1.f, 0.f);
            return Mper; 
        }
};

class Viewport {
    float nx;
    float ny;

    public:
    Viewport(int nx, int ny) : nx(nx), ny(ny) {}

    mat4 doViewportPositionTranformation(){
        mat4 Mvp = mat4(nx/2, 0.f, 0.f, (nx-1)/2,
                        0.f, ny/2, 0.f, (ny-1)/2,
                        0.f, 0.f, 1.f, 0.f,
                        0.f, 0.f, 0.f, 1.f);
        return Mvp; 
    }
};

mat4 mulmat4(mat4 a, mat4 b){ // 4x4 행렬 끼리의 곱 계산 함수
    mat4 result;
    for(int i = 0; i<4;i++){
        for(int j =0; j < 4; j ++){
            float sum = 0;
            for(int k =0; k < 4; k ++){
                sum += a[i][k]* b[k][j];
            }
            result[i][j] = sum;
        }
    } return result;
}

vec4 mulmatvec4(mat4 a, vec3 v){ // 4x4 행렬 x 1x4 행렬 곱 계산 함수
    vec4 v4 = vec4(v.x, v.y, v.z, 1);
    vec4 result;
    for(int i = 0; i<4;i++){
        float sum = 0;
        for(int j =0; j < 4; j ++){
            sum += a[i][j] * v4[j];
        }
        result[i] = sum;
    } return result;
}

vec3 w_normalize(vec4 v){ // vec4의 w 값이 1이 되도록 normalize
    v /= v.w;
    return v;
}
