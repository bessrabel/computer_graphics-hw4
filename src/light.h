#include <glm.hpp>

using namespace glm;

class Light{
    vec3 point;
    vec3 illumination;
    float intensity;

    public: 
        Light(vec3 point, vec3 illumination, float intensity) : point(point), illumination(illumination), intensity(intensity) {}
        
        vec3 getPoint(){ return point; }
        vec3 getI(){ return illumination; }
        float getIntensity(){ return intensity; }
};