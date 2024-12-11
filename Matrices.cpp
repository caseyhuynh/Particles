#include "Matrices.h"

using namespace Matrices;

namespace Matrices
{
    Matrix::Matrix(int _rows, int _cols)
    {
        rows = _rows;
        cols = _cols;

        a.resize(rows); //resizing row

        for (int i = 0; i < a.size(); i++)
        {
            a[i].resize(cols); //resizing col
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                a[i][j] = 0;
            }
        }
    }

    //c = a + b
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        Matrix local(a.getRows(), a.getCols());

        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            throw runtime_error("Error: dimensions must agree");
        }
        else
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    local(i, j) = a(i, j) + b(i, j);
                }
            }
        }

        return local;
    }

    //c = a*b
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }


        //i = elements in row a
        //j = column a
        //j = row b;
        //k = column for b
        Matrix c(a.getRows(), b.getCols());
        int n = a.getCols();


        for (int k = 0; k < b.getCols(); k++)
        {
            for (int i = 0; i < a.getRows(); i++)
            {
                double sum = 0;

                for (int j = 0; j < n; j++)
                {
                    sum += (a(i, j) * b(j, k));
                }

                c(i, k) = sum;
            }
        }

        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) > 0.001)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if ((a.getRows() != b.getRows()) || (a.getCols() != b.getCols()))
        {
            return true; //saying if the matrices are not equal then != is true
        }
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if ((abs(a(i, j) - b(i, j)) >= 0.001))
                {
                    return true; //if (i, j) are >= 0.001, then it's true they are !=
                }
            }
        }

        return false; //If you get here, that means the matrices are equal, so != is false
    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(10) << a(i, j) << ' ';
            }
            os << '\n';
        }

        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2) {
        a.at(0).at(0) = cos(theta);
        a.at(0).at(1) = -sin(theta);
        a.at(1).at(0) = sin(theta);
        a.at(1).at(1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2) {
        a.at(0).at(0) = scale;
        a.at(0).at(1) = 0;
        a.at(1).at(0) = 0;
        a.at(1).at(1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                if (i == 0)
                {
                    a.at(i).at(j) = xShift;
                }
                else if (i == 1)
                {
                    a.at(i).at(j) = yShift;
                }
            }
        }
    }
}