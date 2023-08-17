#include <smmintrin.h>

inline float npow(float x, int n){
    float res = x;
    for(int i = 1; i < n; i++){
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
        return (s32)(x - 0.9999999999f);
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
#define SQRT3   1.7320508075f

inline float _sin_internal(float x){
    float q = 8 * x - 16 * x * x;
    return 0.225 * (q * q - q) + q;
}
inline float sin(float angle){
    angle = fmod(angle, 1);
    
    if(angle < 0){
        angle += 1;
    }
    
    if(angle > 0.5){
        return -_sin_internal(angle - 0.5);
    }
    return _sin_internal(angle);
}
inline float cos(float angle){
    return sin(angle + 0.25);
}
inline float sqrt(float x){
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
inline vec2 operator -(vec2 a)          {return {-a.x, -a.y};}
inline vec2 operator +=(vec2& a, const vec2& b) {a = a + b;  return a;}
inline vec2 operator -=(vec2& a, const vec2& b) {a = a - b;  return a;}
inline bool operator ==(vec2 a, vec2 b) {return (a.x == b.x) && (a.y == b.y);}
inline bool operator !=(vec2 a, vec2 b) {return !(a == b);}
inline vec2 rotate(vec2 v, float angle){
    float cos_value = cos(angle);
    float sin_value = sin(angle);
    
    vec2 res;
    res.x = v.x * cos_value - v.y * sin_value;
    res.y = v.x * sin_value + v.y * cos_value;
    return res;
}
inline float length(vec2 v){
    return sqrt(v.x * v.x + v.y * v.y);
}
inline vec2 normalize(vec2 v){
    float len = length(v);
    return {v.x / len, v.y / len};
}
inline vec2 round(vec2 v) {return {round(v.x), round(v.y)};}
inline vec2 floor(vec2 v) {return {floor(v.x), floor(v.y)};}
inline vec2 ceil(vec2 v)  {return {ceil(v.x), ceil(v.y)};}
inline vec2 trunc(vec2 v) {return {trunc(v.x), trunc(v.y)};}

inline void printsl(vec2 v) {fast_print("(%.3f, %.3f)", v.x, v.y);}

struct vec3{
    union{
        float ptr[3];
        struct {float x, y, z;};
    };
};
inline vec3 operator +(vec3 a, vec3 b)  {return {a.x + b.x, a.y + b.y, a.z + b.z};}
inline vec3 operator -(vec3 a, vec3 b)  {return {a.x - b.x, a.y - b.y, a.z - b.z};}
inline vec3 operator *(vec3 a, float s) {return {a.x * s, a.y * s, a.z * s};}
inline vec3 operator /(vec3 a, float s) {return {a.x / s, a.y / s, a.z / s};}
inline vec3 operator -(vec3 a)  {return {-a.x, -a.y, -a.z};}
inline vec3 operator +=(vec3& a, const vec3& b) {a = a + b;  return a;}
inline vec3 operator -=(vec3& a, const vec3& b) {a = a - b;  return a;}
inline bool operator ==(vec3 a, vec3 b) {return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);}
inline bool operator !=(vec3 a, vec3 b) {return !(a == b);}
inline float length(vec3 v){
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
inline vec3 normalize(vec3 v){
    float len = length(v);
    return {v.x / len, v.y / len, v.z / len};
}
inline vec3 round(vec3 v) {return {round(v.x), round(v.y), round(v.z)};}
inline vec3 floor(vec3 v) {return {floor(v.x), floor(v.y), floor(v.z)};}
inline vec3 ceil(vec3 v)  {return {ceil(v.x),  ceil(v.y),  ceil(v.z)};}
inline vec3 trunc(vec3 v) {return {trunc(v.x), trunc(v.y), trunc(v.z)};}

inline void printsl(vec3 v) {fast_print("(%.3f, %.3f, %.3f)", v.x, v.y, v.z);}

struct vec4{
    union{
        float ptr[4];
        struct {float x, y, z, w;};
        __m128 v;
    };
};
struct col{
    union{
        float ptr[4];
        struct {float r, g, b, a;};
        __m128 v;
    };
};
inline vec4 operator +(vec4 a, vec4 b)  {vec4 res; res.v = _mm_add_ps(a.v, b.v); return res;}
inline vec4 operator -(vec4 a, vec4 b)  {vec4 res; res.v = _mm_sub_ps(a.v, b.v); return res;}
inline vec4 operator *(vec4 a, float s) {vec4 res; res.v = _mm_mul_ps(a.v, _mm_set1_ps(s)); return res;}
inline vec4 operator /(vec4 a, float s) {vec4 res; res.v = _mm_div_ps(a.v, _mm_set1_ps(s)); return res;}
inline vec4 operator -(vec4 a)  {vec4 res;  res.v = _mm_sub_ps(_mm_setzero_ps(), a.v);  return res;}
inline vec4 operator +=(vec4& a, const vec4& b) {a = a + b;  return a;}
inline vec4 operator -=(vec4& a, const vec4& b) {a = a - b;  return a;}
inline bool operator ==(vec4 a, vec4 b) {return _mm_movemask_ps(_mm_cmpeq_ps(a.v, b.v)) == 0b1111;}
inline bool operator !=(vec4 a, vec4 b) {return _mm_movemask_ps(_mm_cmpeq_ps(a.v, b.v)) != 0b1111;}
inline float length(vec4 v){
    vec4 res;
    res.v = _mm_dp_ps(v.v, v.v, 0b11110001);
    res.v = _mm_sqrt_ss(res.v);
    return _mm_cvtss_f32(res.v);
}
inline vec4 normalize(vec4 v){
    vec4 res;
    float len = length(v);
    res.v = _mm_div_ps(v.v, _mm_set1_ps(len));
    return res;
}
inline vec4 round(vec4 v) {vec4 res;  res.v = _mm_round_ps(v.v, _MM_FROUND_TO_NEAREST_INT);  return res;}
inline vec4 floor(vec4 v) {vec4 res;  res.v = _mm_floor_ps(v.v);  return res;}
inline vec4 ceil(vec4 v)  {vec4 res;  res.v = _mm_ceil_ps(v.v);  return res;}
inline vec4 trunc(vec4 v) {return {trunc(v.x), trunc(v.y), trunc(v.z), trunc(v.w)};}

inline void printsl(vec4 v) {fast_print("(%.3f, %.3f, %.3f, %.3f)", v.x, v.y, v.z, v.w);}

inline col normalize(col c) {col res; res.v = _mm_div_ps(c.v, _mm_set1_ps(255)); return res;}

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

inline void printsl(mat4 m) {fast_print("|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n|%.3f %.3f %.3f %.3f|\n", m.m11, m.m12, m.m13, m.m14, m.m21, m.m22, m.m23, m.m24, m.m31, m.m32, m.m33, m.m34, m.m41, m.m42, m.m43, m.m44);}
inline mat4 transpose(mat4 m) {_MM_TRANSPOSE4_PS(m.r1, m.r2, m.r3, m.r4);  return m;}
inline mat4 operator +(mat4 m1, mat4 m2){
    mat4 res;
    res.r1 = _mm_add_ps(m1.r1, m2.r1);
    res.r2 = _mm_add_ps(m1.r2, m1.r2);
    res.r3 = _mm_add_ps(m1.r3, m1.r3);
    res.r4 = _mm_add_ps(m1.r4, m1.r4);
    return res;
}
inline mat4 operator -(mat4 m1, mat4 m2){
    mat4 res;
    res.r1 = _mm_sub_ps(m1.r1, m2.r1);
    res.r2 = _mm_sub_ps(m1.r2, m1.r2);
    res.r3 = _mm_sub_ps(m1.r3, m1.r3);
    res.r4 = _mm_sub_ps(m1.r4, m1.r4);
    return res;
}
inline mat4 operator *(mat4 m1, float s){
    mat4 res;
    res.r1 = _mm_mul_ps(m1.r1, _mm_set1_ps(s));
    res.r2 = _mm_mul_ps(m1.r2, _mm_set1_ps(s));
    res.r3 = _mm_mul_ps(m1.r3, _mm_set1_ps(s));
    res.r4 = _mm_mul_ps(m1.r4, _mm_set1_ps(s));
    return res;
}
inline mat4 operator /(mat4 m1, float s){
    mat4 res;
    res.r1 = _mm_div_ps(m1.r1, _mm_set1_ps(s));
    res.r2 = _mm_div_ps(m1.r2, _mm_set1_ps(s));
    res.r3 = _mm_div_ps(m1.r3, _mm_set1_ps(s));
    res.r4 = _mm_div_ps(m1.r4, _mm_set1_ps(s));
    return res;
}
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

/*
NOTE: CastOperatorBackAndForth
I know we wanted to make a cast from one type to another and also in the other
direction (like casting Vec2 to Vec2i and vice versa), but we couldn't figure out
how to do it.
Well I've figured out how but I don't remember where we needed it, so I'm gonna
add it here and let someone else handle it
                          - Cogno 2023/08/05


struct Vec2;
struct Vec2i;

struct Vec2i {
    s32 x = 0;
    s32 y = 0;
    operator Vec2();
};

struct Vec2 {
    f32 x = 0.0f;
    f32 y = 0.0f;
    operator Vec2i();
};

inline Vec2i::operator Vec2() {
    Vec2 out;
    out.x = (f32)x;
    out.y = (f32)y;
    return out;
}

inline Vec2::operator Vec2i() {
    Vec2i out;
    out.x = (s32)x;
    out.y = (s32)y;
    return out;
}

*/
