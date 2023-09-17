#include <core/matrix.h>
#include <core/assert.h>
#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <math.h>

namespace rt {

Matrix::Matrix(const HomogeneousCoord& r1, const HomogeneousCoord& r2, const HomogeneousCoord& r3, const HomogeneousCoord& r4) {
    /* TODO */
    mat[0] = r1;
    mat[1] = r2;
    mat[2] = r3;
    mat[3] = r4;
}

HomogeneousCoord& Matrix::operator[](int idx) {
    /* TODO */ 
    rt_assert(idx<4);
    return mat[idx];
}

HomogeneousCoord Matrix::operator[](int idx) const {
    /* TODO */ 
    rt_assert(idx<4);
    return mat[idx];
}

Matrix Matrix::operator+(const Matrix& b) const {
    /* TODO */ 
    Matrix temp;
    for(int i = 0; i < 4; i++){
        temp[i] = mat[i] + b[i];
    }
    return temp;
}

Matrix Matrix::operator-(const Matrix& b) const {
    /* TODO */ 
    Matrix temp;
    for(int i = 0; i < 4; i++){
        temp[i] = mat[i] - b[i];
    }
    return temp;
}

Matrix Matrix::transpose() const {
    /* TODO */ 
    Matrix temp;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[j][i] = mat[i][j];
        }
    }
    return temp;
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    /* TODO */ 
    for(int i = 0; i < 4; i++){
        if(mat[i] != b[i]) 
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix& b) const {
    /* TODO */ 
    for(int i = 0; i < 4; i++){
        if(mat[i] != b[i]) 
            return true;
    }
    return false;
}

Matrix product(const Matrix& a, const Matrix& b) {
    /* TODO */ 
    Matrix prod;
    Matrix b_t = b.transpose();
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            prod[i][j] = dot(a[i], b_t[j]);
        }
    }
    return prod;
}

Matrix operator*(const Matrix& a, float scalar) {
    /* TODO */ 
    Matrix temp;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[i][j] = a[i][j]*scalar;
        }
    }
    return temp;
}

Matrix operator*(float scalar, const Matrix& a) {
    /* TODO */
    Matrix temp; 
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[i][j] = a[i][j]*scalar;
        }
    }
    return temp;
}

HomogeneousCoord Matrix::operator*(const HomogeneousCoord& b) const {
    /* TODO */ 
    float prod[4];
    for(int i=0; i<4;i++){
        prod[i] = dot(mat[i], b);
    }
    return HomogeneousCoord(prod[0], prod[1], prod[2], prod[3]);
}

Vector Matrix::operator*(const Vector& b) const {
    /* TODO */ 
    float prod[3];
    HomogeneousCoord vec = HomogeneousCoord(b.x, b.y, b.z, 0);
    for(int i=0; i<3;i++){
        prod[i] = dot(mat[i], vec);
    }
    return Vector(prod[0], prod[1], prod[2]);
}

Point Matrix::operator*(const Point& b) const {
    /* TODO */ 
    float prod[3];
    HomogeneousCoord pt = HomogeneousCoord(b.x, b.y, b.z, 1);
    for(int i=0; i<3;i++){
        prod[i] = dot(mat[i], pt);
    }
    return Point(prod[0], prod[1], prod[2]);

}

float Matrix::det() const {
    /* TODO */ 
    //From invert() method:
    Matrix result;
    const Matrix& m = *this;

    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    return det;
}

Matrix Matrix::zero() {
    /* TODO */ 
    Matrix m;
    for(int i=0; i<4; i++){
        m[i] = HomogeneousCoord(0,0,0,0);
    }
    return m;
}

Matrix Matrix::identity() {
    /* TODO */ 
    Matrix m;
    for(int i=0; i<4; i++){
        m[i] = HomogeneousCoord(float(i==0),float(i==1),float(i==2),float(i==3));
    }
    return m;
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    /* TODO */ 
    Matrix m;
    m[0] = HomogeneousCoord(e1.x, e2.x, e3.x, 0);
    m[1] = HomogeneousCoord(e1.y, e2.y, e3.y, 0);
    m[2] = HomogeneousCoord(e1.z, e2.z, e3.z, 0);
    m[3] = HomogeneousCoord(0, 0, 0, 1);
    return m;
}

}