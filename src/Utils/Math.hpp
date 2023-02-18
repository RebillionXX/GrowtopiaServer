#pragma once
#include <utility>

template<class T>
class CL_Vec2 {
public:
    constexpr inline CL_Vec2(const T& x = 0, const T& y = 0) noexcept : X(x), Y(y) {}

    constexpr inline bool operator==(const CL_Vec2<T>& other) const noexcept { return X == other.X && Y == other.Y; }
    constexpr inline bool operator!=(const CL_Vec2<T>& other) const noexcept { return X != other.X || Y != other.Y; }

    constexpr inline CL_Vec2<T> operator+(const CL_Vec2<T>& other) noexcept { return CL_Vec2<T>(X + other.X, Y + other.Y); }
    constexpr inline CL_Vec2<T> operator-(const CL_Vec2<T>& other) noexcept { return CL_Vec2<T>(X - other.X, Y - other.Y); }
    constexpr inline CL_Vec2<T> operator/(const CL_Vec2<T>& other) noexcept { return CL_Vec2<T>(X / other.X, Y / other.Y); }
    constexpr inline CL_Vec2<T> operator*(const CL_Vec2<T>& other) noexcept { return CL_Vec2<T>(X * other.X, Y * other.Y); }

    T X, Y;
};

template<class T>
class CL_Vec3 {
public:
    constexpr inline CL_Vec3(const T& x = 0, const T& y = 0, const T& z = 0) noexcept : X(x), Y(y), Z(z) {}

    constexpr inline bool operator==(const CL_Vec3<T>& other) const noexcept { return X == other.X && Y == other.Y && Z == other.Z; }
    constexpr inline bool operator!=(const CL_Vec3<T>& other) const noexcept { return X != other.X || Y != other.Y || other.Z; }

    constexpr inline CL_Vec3<T> operator+(const CL_Vec3<T>& other) noexcept { return CL_Vec3<T>(X + other.X, Y + other.Y, Z + other.Z); }
    constexpr inline CL_Vec3<T> operator-(const CL_Vec3<T>& other) noexcept { return CL_Vec3<T>(X - other.X, Y - other.Y, Z - other.Z); }
    constexpr inline CL_Vec3<T> operator/(const CL_Vec3<T>& other) noexcept { return CL_Vec3<T>(X / other.X, Y / other.Y, Z / other.Z); }
    constexpr inline CL_Vec3<T> operator*(const CL_Vec3<T>& other) noexcept { return CL_Vec3<T>(X * other.X, Y * other.Y, Z * other.Z); }

    T X, Y, Z;
};
