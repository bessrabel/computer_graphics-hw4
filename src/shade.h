#include <iostream>
#include <stdio.h>
#include "Light.h"

class Shade{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    int p;
    Light light;

    public:
        Shade(vec3 ka, vec3 kd, vec3 ks, int p, Light light) : ka(ka), kd(kd), ks(ks), p(p), light(light) {};

        // 삼각형의 중심 계산
        vec3 calculate_centroid(vec3 a, vec3 b, vec3 c) { return {(a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3, (a.z + b.z + c.z) / 3}; }

        // normal (per-triangle)
        vec3 calculate_normal(vec3 a, vec3 b, vec3 c) {
            vec3 ab = b - a;
            vec3 ac = c - a;
            vec3 normal = vec3(ab.y * ac.z - ab.z * ac.y, ab.z * ac.x - ab.x * ac.z, ab.x * ac.y - ab.y * ac.x);
            return normal;
        }

        // normal (per-vertex)
        vec3 getGouraudNormal(vec3 point, vec3 center){
            vec3 n = normalize(point-center);
            if(n.z < 0)
                n = -n;
            return n;
        }

        // 두벡터의 곱 계산
        float dot(vec3 a, vec3 b){ 
            float result = a.x * b.x + a.y * b.y + a.z * b.z;
            
            return result;
        }

        vec3 getAmbient(){ return ka * light.getIntensity(); }

        vec3 phongShade(vec3 e, vec3 n, vec3 point){
            n = normalize(n);
            if(n.z < 0)
                n = -n;
            vec3 v = normalize(e - point);           
            vec3 l = normalize(light.getPoint() - point);
            vec3 h = normalize(v + l);

            vec3 ambient = getAmbient();
            vec3 diffuse = kd * light.getI() * std::max(dot(n,l), 0.0f);
            vec3 phong = ks * light.getI() * float(pow(std::max(dot(n,h), 0.0f), p));
            vec3 color = ambient + diffuse + phong;
            return color;
        }

        vec3 flatShade(vec3 e, vec3 a, vec3 b, vec3 c){
            vec3 point = calculate_centroid(a, b, c);
            vec3 n = calculate_normal(a, b, c);
            vec3 color = phongShade(e, n, point);
            return color;
        }

        vec3 gouraudShade(vec3 e, vec3 point, vec3 center){
            vec3 n = normalize(point - center);
            vec3 color = phongShade(e, n, point);
            return color;
        }
};


