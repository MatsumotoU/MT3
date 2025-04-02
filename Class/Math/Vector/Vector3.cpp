#include "Vector3.h"
#include "../Matrix/Matrix4x4.h"
#include <math.h>
#include <assert.h>

float Vector3::Length() const {
    return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::Normalize() const {
    Vector3 result = {};

    if (this->Length() == 0.0f) {
        assert(false);
    }
    result.x = this->x / this->Length();
    result.y = this->y / this->Length();
    result.z = this->z / this->Length();
    
    return result;
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2) {
    Vector3 result = {};
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

Vector3 Vector3::Transform(const Vector3& vector, const Matrix4x4& matrix) {
    Vector3 result = {};
    
    float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
    if (w != 0.0f) {
        result.x = (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w;
        result.y = (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w;
        result.z = (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w;
    } 

    return result;
}

Vector3 Vector3::Project(const Vector3& v1, const Vector3& v2) {
    Vector3 result{};
    if (powf(v2.Length(), 2) != 0.0f) {
        float t = Dot(v1, v2) / powf(v2.Length(), 2);
        result = v2 * t;
    }
    return result;
}