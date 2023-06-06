#pragma once


struct Vector2       // 2d Vector type
{
    float x, y;

    Vector2(float val) : x(val), y(val) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    Vector2 operator+(Vector2 const& other) { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(Vector2 const& other) { return Vector2(x - other.x, y - other.y); }
    Vector2 operator*(Vector2 const& other) { return Vector2(x * other.x, y * other.y); }
    Vector2 operator/(Vector2 const& other) { return Vector2(x / other.x, y / other.y); }

};

struct Vector3        // 3d Vector type
{
    float x, y, z ;

    Vector3(float val) : x(val), y(val), z(val) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(float _x, Vector2 const& _v) : x(_x), y(_v.x), z(_v.y) {}
    Vector3(Vector2 _v, float _z) : x(_v.x), y(_v.y), z(_z) {}


    Vector3 operator+(Vector3 const& other) { return Vector3(x + other.x, y + other.y ,z + other.z); }
    Vector3 operator-(Vector3 const& other) { return Vector3(x - other.x, y - other.y, z - other.z); }
    Vector3 operator*(Vector3 const& other) { return Vector3(x * other.x, y * other.y, z * other.z); }
    Vector3 operator/(Vector3 const& other) { return Vector3(x / other.x, y / other.y, z / other.z); }
    Vector3 operator-() { return Vector3(-x , -y, -z); }
};

// Vector operations

float valClamp(float val, float min, float max) {
    return fmax(fmin(val, max), min);
}

double step(double edge, double x) { return x > edge; }

double sign(double a) { return (a > 0) - (a < 0); }


float length(Vector2 const& v) { return sqrt(v.x * v.x + v.y * v.y); }

float length(Vector3 const& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

float dot(Vector3 const& a, Vector3 const& b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }

Vector3 sign(Vector3 const& v) { return Vector3(sign(v.x), sign(v.y), sign(v.z)); }

Vector3 step(Vector3 const& edge, Vector3 const& v) { return Vector3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); }

Vector3 abs(Vector3 const& v) { return Vector3(fabs(v.x), fabs(v.x), fabs(v.x) ); }

Vector3 cross(Vector3 a, Vector3 b) { return Vector3((a.y * b.z - a.z * b.y), -(a.x * b.z - a.z * b.x), (a.x * b.y - a.y * b.x)); }

Vector3 normalize(Vector3 v) { return v / length(v); }



// 3d mesh intersection

Vector2 box(Vector3 ro, Vector3 rd, Vector3 boxSize, Vector3& outNormal) {
    Vector3 m = Vector3(1.0) / rd;
    Vector3 n = m * ro;
    Vector3 k = abs(m) * boxSize;
    Vector3 t1 = -n - k;
    Vector3 t2 = -n + k;

    float tN = fmax(fmax(t1.x, t1.y), t1.z);
    float tF = fmax(fmax(t2.x, t2.y), t2.z);
    if (tN > tF || tF < 0.0) return Vector2(-1.0);
    Vector3 yzx = Vector3(t1.y, t1.z, t1.x);
    Vector3 zxy = Vector3(t1.z, t1.x, t1.y);
    outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);
    return Vector2(tN, tF);

}

Vector2 sphere(Vector3 ro, Vector3 rd, float r) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - r*r;
    float h = b * b - c;
    if (h < 0.0) return Vector2(-1, 0);
    h = sqrt(h);
    return Vector2(-b -h, -b +h);
}