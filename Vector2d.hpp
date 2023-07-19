#ifndef __VECTOR_2D__
#define __VECTOR_2D__

#include <math.h>

class Vector2d
{
public:
    Vector2d() {}

    Vector2d(float _x, float _y)
        : x(_x), y(_y)
    {
    }

    float getX() { return x; }
    float getY() { return y; }

    void setX(float _x) { x = _x; }
    void setY(float _y) { y = _y; }

    float length() { return sqrt(x * x + y * y); }

    // Soma
    Vector2d operator+(const Vector2d &v2) const
    {
        return Vector2d(x + v2.x, y + v2.y);
    }
    friend Vector2d &operator+=(Vector2d &v1, const Vector2d &v2)
    {
        v1.x += v2.x;
        v1.y += v2.y;

        return v1;
    }

    // Multiplicação por escalar
    Vector2d operator*(float scalar)
    {
        return Vector2d(x * scalar, y * scalar);
    }
    Vector2d &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Subtração
    Vector2d operator-(const Vector2d &v2) const
    {
        return Vector2d(x - v2.x, y - v2.y);
    }
    friend Vector2d &operator-=(Vector2d &v1, const Vector2d &v2)
    {
        v1.x -= v2.x;
        v1.y -= v2.y;
        return v1;
    }

    // Divisão por escalar
    Vector2d operator/(float scalar)
    {
        return Vector2d(x / scalar, y / scalar);
    }
    Vector2d &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    void normalize()
    {
        float l = length();
        if (l > 0) // we never want to attempt to divide by 0
        {
            (*this) *= 1 / l;
        }
    }

    static float innerProduct(Vector2d v1, Vector2d v2)
    {
        return v1.getX() * v2.getX() + v1.getY() * v2.getY();
    }

    static double getAngleTwoVectors(Vector2d v1, Vector2d v2)
    {
        double dotProduct = Vector2d::innerProduct(v1, v2);
        double magProduct = v1.length() * v2.length();
        double cosine = dotProduct / magProduct;
        double angRad = acos(cosine);
        double angle = angRad * (180 / M_PI);

        return angle;
    }

private:
    float x, y;
};

#endif