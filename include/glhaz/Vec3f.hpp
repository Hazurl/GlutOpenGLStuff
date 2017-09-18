#pragma once

#include <cmath>
#include <string>
#include <cassert>

namespace glhaz {
    
template<typename T>
class Vec3 {
public:

    T x, y, z;

    Vec3() {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
/*
    static Vec3<T> up()           { return {0, 1, 0};  }
    static Vec3<T> down()         { return {0, -1, 0}; }
    static Vec3<T> left()         { return {-1, 0, 0}; }
    static Vec3<T> right()        { return {1, 0, 0};  }
    static Vec3<T> front()         { return {0, 0, 1}; }
    static Vec3<T> back()        { return {0, 0, -1};  }

    static Vec3<T> zero()         { return {0, 0, 0};  }
    static Vec3<T> units()        { return {1, 1, 1};  }
*/
    ~Vec3() {}
/*
    void set(T x, T y, T z) { this->x = x; this->y = y; this->z = z; }
    void set(Vec3<T> const& o) { x = o.x; y = o.y; z = o.z; }

    auto magnitude2() const {
        return x * x + y * y + z * z;
    }

    auto magnitude() const {
        return std::sqrt(magnitude2());
    }

    Vec3<T> normalize() const {
        double l = magnitude();
        return { x / l, y / l, z / l };
    }

    Vec3<T> abs() const {
        return { x < 0 ? -x : x, y < 0 ? -y : y, z < 0 ? -z : z };
    }

    T operator [] (unsigned int pos) const {
        switch(pos) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: assert(false);
        }
    }

    std::string to_string() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    Vec3<T>& operator += (Vec3<T> const& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vec3<T>& operator -= (Vec3<T> const& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vec3<T>& operator *= (T f) { x *= f; y *= f; z *= f; return *this; }
    Vec3<T>& operator /= (T f) { x /= f; y /= f; z /= f; return *this; }
    Vec3<T>& operator %= (T f) { x %= f; y %= f; z %= f;return *this; }
    Vec3<T>& operator *= (Vec3<T> const& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    Vec3<T>& operator /= (Vec3<T> const& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
    Vec3<T>& operator %= (Vec3<T> const& v) { x %= v.x; y %= v.y; z %= v.z; return *this; }
    Vec3<T>& operator  = (Vec3<T> const& o) { x = o.x; y = o.y; z = o.z; return *this; }

    bool operator == (Vec3<T> const& v) const { return x == v.x && y == v.y && z == v.z; } 
    bool operator != (Vec3<T> const& v) const { return !(*this == v); } 
    bool operator <  (Vec3<T> const& v) const { return magnitude2() < v.magnitude2(); } 
    bool operator >  (Vec3<T> const& v) const { return magnitude2() > v.magnitude2(); } 
    bool operator <= (Vec3<T> const& v) const { return !(*this > v); } 
    bool operator >= (Vec3<T> const& v) const { return !(*this < v); } 

    Vec3<T> operator + () { return Vec3<T>(+x, +y, +z); } 
    Vec3<T> operator - () { return Vec3<T>(-x, -y, -z); } 

    friend Vec3<T> operator + (Vec3<T> a, Vec3<T> const& b) { return a += b; }
    friend Vec3<T> operator - (Vec3<T> a, Vec3<T> const& b) { return a -= b; }
    friend Vec3<T> operator * (Vec3<T> a, T f) { return a *= f; }
    friend Vec3<T> operator / (Vec3<T> a, T f) { return a /= f; }
    friend Vec3<T> operator % (Vec3<T> a, T f) { return a %= f; }
    friend Vec3<T> operator * (Vec3<T> a, Vec3<T> const& b) { return a *= b; }
    friend Vec3<T> operator / (Vec3<T> a, Vec3<T> const& b) { return a /= b; }
    friend Vec3<T> operator % (Vec3<T> a, Vec3<T> const& b) { return a %= b; }

    friend std::ostream& operator <<(std::ostream& os, Vec3<T> const& v) {
        os << v.to_string();
        return os;
    }

    friend std::istream& operator >>(std::istream& is, Vec3<T>& v) {
        is >> v.x;
        is >> v.y;
        is >> v.z;
        return is;
    }
*/
};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
using Vec3ui = Vec3<unsigned int>;
using Vec3d = Vec3<double>;

}