#include <smmintrin.h>

inline float npow(float x, int n){
    float res = 1.0f;
    for(int i = 0; i < n; i++){
        res *= x;
    }
    return res;
}

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) < (b)) ? (b) : (a))
#define abs(a) (((a) >= 0) ? (a) : (-(a)))
#define sgn(a) (((a) == 0) ? (0) : (((a) > 0) ? 1 : -1))
#define clamp(val, min_, max_) max(min(val, max_), min_)

inline float floor(float x){
    if(x >= 0){
        return (s32)x;
    }else{
        return (x32)(x - 0.9999999999999999);
    }
}
inline float ceil(float x){
    if(x < 0){
        return (s32)x;
    }else{
        return (s32)x + 1;
    }
}
inline float round(float x){
    if(x >= 0){
        return floor(x + 0.5);
    }else{
        return ceil(x - 0.5);
    }
}
inline float roundn(float x, int n){
    return round(x * npow(10, n)) / npow(10, n);
}
inline float trunc(float x){
    return float(int(x));
}

#define fmod(x, y) ((x) - trunc((x) / (y)) * (y))
#define lerp(start, dest, t) (dest - start) * t + start

#define PI      3.1415926535f
#define E       2.7182818284f
#define SQRT2   1.4142135623f
#define SQRT3   1.73205080756f

inline float _sin_internal(float x){
    float q = 8 * x - 16 * x * x;
    return 0.225 * (q * q - q) + q;
}
inline float fast_sin(float angle){
    angle = fmod(angle, 1);
    
    if(angle < 0){
        angle += 1;
    }
    
    if(angle > 0.5){
        return -_sin_internal(angle - 0.5);
    }
    return _sin_internal(angle);
}
inline float fast_cos(float angle){
    return fast_sin(angle + 0.25);
}
inline float fast_sqrt(float x){
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

struct vec2{
    union{
        float ptr[2];
        struct {float x, y;};
    };
};
inline vec2 operator +(vec2 a, vec2 b)  {return {a.x + b.x, a.y + b.y};}
inline vec2 operator -(vec2 a, vec2 b)  {return {a.x - b.x, a.y - b.y};}
inline vec2 operator *(vec2 a, float s) {return {a.x * s, a.y * s};}
inline vec2 operator /(vec2 a, float s) {return {a.x / s, a.y / s};}
inline vec2 operator -(vec2 a)  {return {-a.x, -a.y};}
inline vec2 operator +=(vec2& a, const vec2& b) {a = a + b;  return a;}
inline vec2 operator -=(vec2& a, const vec2& b) {a = a - b;  return a;}
inline u8 operator ==(vec2 a, vec2 b) {return (a.x == b.x) && (a.y == b.y);}
inline u8 operator !=(vec2 a, vec2 b) {return !(a == b);}
inline vec2 rotate(vec2 v, float angle){
    float cos_value = fast_cos(angle);
    float sin_value = fast_sin(angle);
    
    vec2 res;
    res.x = v.x * sin_value + v.y * cos_value;
    res.y = v.x * cos_value - v.y * sin_value;
    return res;
}
inline float length(vec2 v){
    return fast_sqrt(v.x * v.x + v.y * v.y);
}
inline vec2 normalize(vec2 v){
    float len = length(v);
    return {v.x / len, v.y / len};
}
inline vec2 round(vec2 v)  {return {math_round(v.x), math_round(v.y)};}
inline vec2 floor(vec2 v)  {return {math_floor(v.x), math_floor(v.y)};}
inline vec2 ceil (vec2 v)  {return {math_ceil(v.x), math_ceil(v.y)};}
inline vec2 trunc(vec2 v)  {return {math_trunc(v.x), math_trunc(v.y)};}
inline void printsl(vec2 v) {printf("(%.3f, %.3f)", v.x, v.y);}

struct vec3{
    union{
        float ptr[3];
        struct {float x, y, z;};
    };
};
// Todo(Quattro)
inline vec3 operator +(vec3 a, vec3 b)  {return {a.x + b.x, a.y + b.y, a.z + b.z};}
inline vec3 operator -(vec3 a, vec3 b)  {return {a.x - b.x, a.y - b.y, a.z - b.z};}
inline vec3 operator *(vec3 a, float s) {return {a.x * s, a.y * s, a.z * s};}
inline vec3 operator /(vec3 a, float s) {return {a.x / s, a.y / s, a.z / s};}
inline vec3 operator -(vec3 a)  {return {-a.x, -a.y, -a.z};}
inline vec3 operator +=(vec3& a, const vec3& b) {a = a + b;  return a;}
inline vec3 operator -=(vec3& a, const vec3& b) {a = a - b;  return a;}
inline u8 operator ==(vec3 a, vec3 b)  {return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);}
inline u8 operator !=(vec3 a, vec3 b)  {return !(a == b);}
inline float length(vec3 v){
    return fast_sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
inline vec3 normalize(vec3 v){
    float len = length(v);
    return {v.x / len, v.y / len, v.z / len};
}
inline vec3 round(vec3 v)  {return {math_round(v.x), math_round(v.y), math_round(v.z)};}
inline vec3 floor(vec3 v)  {return {math_floor(v.x), math_floor(v.y), math_floor(v.z)};}
inline vec3 ceil (vec3 v)  {return {math_ceil(v.x), math_ceil(v.y), math_ceil(v.z)};}
inline vec3 trunc(vec3 v)  {return {math_trunc(v.x), math_trunc(v.y), math_trunc(v.z)};}
inline void printsl(vec3 v) {printf("(%.3f, %.3f, %.3f)", v.x, v.y, v.z);}

struct vec4{
    union{
        float ptr[4];
        struct {float x, y, z, w;};
    };
};
inline vec4 operator +(vec4 a, vec4 b)  {return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};}
inline vec4 operator -(vec4 a, vec4 b)  {return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};}
inline vec4 operator *(vec4 a, float s) {return {a.x * s, a.y * s, a.z * s, a.w * s};}
inline vec4 operator /(vec4 a, float s) {return {a.x / s, a.y / s, a.z / s, a.w / s};}
inline vec4 operator -(vec4 a)  {return {-a.x, -a.y, -a.z, -a.w};}
inline vec4 operator +=(vec4& a, const vec4& b) {a = a + b;  return a;}
inline vec4 operator -=(vec4& a, const vec4& b) {a = a - b;  return a;}
inline u8 operator ==(vec4 a, vec4 b)  {return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);}
inline u8 operator !=(vec4 a, vec4 b)  {return !(a == b);}
// Todo(Quattro) add these functions after implemented custom round, floor and ceil (or maybe implement, benchmark and check)
// inline vec4 round(vec4 v)  {...}
// inline vec4 floor(vec4 v)  {...}
// inline vec4 ceil (vec4 v)  {...}
// inline vec4 trunc(vec4 v)  {...}
inline void printsl(vec4 v) {printf("(%.3f, %.3f, %.3f, %.3f)", v.x, v.y, v.z, v.w);}

struct col{
    union{
        float ptr[4];
        struct {float r, g, b, a;};
    };
};
inline col normalize(col c) {return {c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a /255.0f};}

struct mat4{
    union{
        float ptr[16];
        float mat_v[4][4];
        struct {
            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;
        };
        struct {
            __m128 r1, r2, r3, r4;
        };
        __m128 mat[4];
    };
    inline float* operator [](int idx){
        return this->mat_v[idx];
    }
};

inline mat4 mat4_new(float n){
    mat4 res;
    res.r1 = _mm_setr_ps(n, 0, 0, 0);
    res.r2 = _mm_setr_ps(0, n, 0, 0);
    res.r3 = _mm_setr_ps(0, 0, n, 0);
    res.r4 = _mm_setr_ps(0, 0, 0, n);
    return res;
}

inline mat4 translate(mat4 m, vec3 v){
    mat4 res = m;
    res.r4 = _mm_add_ps(m.r4, _mm_setr_ps(v.x, v.y, v.z, 0));
    return res;
}

inline mat4 ortho(float left, float right, float bottom, float top, float z_near, float z_far){
    mat4 res = {};
    res.m11 = 2.0f / (right - left);
    res.m22 = 2.0f / (top - bottom);
    res.m33 = -2.0f / (z_far - z_near);
    res.m41 = -(right + left) / (right - left);
    res.m42 = -(top + bottom) / (top - bottom);
    res.m43 = -(z_far + z_near) / (z_far - z_near);
    res.m44 = 1;
    return res;
}

inline void printsl(mat4 m) {printf("|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n", m.m11, m.m12, m.m13, m.m14, m.m21, m.m22, m.m23, m.m24, m.m31, m.m32, m.m33, m.m34, m.m41, m.m42, m.m43, m.m44);}
inline mat4 transpose(mat4 m) {_MM_TRANSPOSE4_PS(m.r1, m.r2, m.r3, m.r4);  return m;}
inline mat4 operator *(mat4 m1, mat4 m2){
    mat4 temp = m2;
    _MM_TRANSPOSE4_PS(temp.r1, temp.r2, temp.r3, temp.r4);
    
    mat4 res;
    res.r1 = _mm_or_ps(_mm_or_ps(_mm_dp_ps(m1.r1, temp.r1, 0b11110001), _mm_dp_ps(m1.r1, temp.r2, 0b11110010)), _mm_or_ps(_mm_dp_ps(m1.r1, temp.r3, 0b11110100), _mm_dp_ps(m1.r1, temp.r4, 0b11111000)));
    res.r2 = _mm_or_ps(_mm_or_ps(_mm_dp_ps(m1.r2, temp.r1, 0b11110001), _mm_dp_ps(m1.r2, temp.r2, 0b11110010)), _mm_or_ps(_mm_dp_ps(m1.r2, temp.r3, 0b11110100), _mm_dp_ps(m1.r2, temp.r4, 0b11111000)));
    res.r3 = _mm_or_ps(_mm_or_ps(_mm_dp_ps(m1.r3, temp.r1, 0b11110001), _mm_dp_ps(m1.r3, temp.r2, 0b11110010)), _mm_or_ps(_mm_dp_ps(m1.r3, temp.r3, 0b11110100), _mm_dp_ps(m1.r3, temp.r4, 0b11111000)));
    res.r4 = _mm_or_ps(_mm_or_ps(_mm_dp_ps(m1.r4, temp.r1, 0b11110001), _mm_dp_ps(m1.r4, temp.r2, 0b11110010)), _mm_or_ps(_mm_dp_ps(m1.r4, temp.r3, 0b11110100), _mm_dp_ps(m1.r4, temp.r4, 0b11111000)));
    return res;
}
inline mat4 operator +(mat4 m1, mat4 m2){
    mat4 res;
    res.r1 = _mm_add_ps(m1.r1, m2.r1);
    res.r2 = _mm_add_ps(m1.r2, m1.r2);
    res.r3 = _mm_add_ps(m1.r3, m1.r3);
    res.r4 = _mm_add_ps(m1.r4, m1.r4);
    return res;
}
