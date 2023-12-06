namespace dip
{
    template<typename T>
    void Coordinate<T>::setCoord(T row, T column)
    {
        this->row = row;
        this->column = column;
    }

    template<typename T>
    Coordinate<T>::Coordinate()
    {
        this->row = 0;
        this->column = 0;
    }

    template<typename T>
    Coordinate<T>::Coordinate(T row, T column)
    {
        this->row = row;
        this->column = column;
    }

    template<typename T>
    Coordinate<T> Coordinate<T>::operator=(const Coordinate<T>& other)
    {
        this->row = other.row;
        this->column = other.column;
        return *this;
    }

    template<typename T>
    bool Coordinate<T>::operator==(const Coordinate<T>& other) const
    {
        bool result = this->row == other.row;
        result &= this->column == other.column;
        return result;
    }

    template<typename T>
    bool Coordinate<T>::operator!=(const Coordinate& other) const
    {
        bool result = Coordinate::row != other.row;
        result |= Coordinate::column != other.column;
        return result;
    }

    template<typename T1, typename T2>
    std::vector<std::vector<double>> multipleMatrix(const std::vector<std::vector<T1>>& left, const std::vector<std::vector<T2>>& right)
    {
        int leftRows = (int)left.size();
        int leftCols = (int)left[0].size();
        int rightRows = (int)right.size();
        int rightCols = (int)right[0].size();

        if (leftCols != rightRows)
        {
            std::cout << "matrixMultiple error: leftCols != rightRows" << std::endl;
            std::exit(-1);
        }

        std::vector<std::vector<double>> multiple(leftRows, std::vector<double>(rightCols, 0.0));

        for (int r = 0; r < leftRows; r++)
            for (int c = 0; c < rightCols; c++)
                for (int k = 0; k < leftCols; k++)
                    multiple[r][c] += left[r][k] * right[k][c];

        return multiple;
    }

    template<typename T>
    std::vector<std::vector<double>> inverseMatrix(const std::vector<std::vector<T>>& matrix)
    {
        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size();
        if (rows != cols)
        {
            std::cout << "inverseMatrix error: rows != cols" << std::endl;
            std::exit(-1);
        }

        T det = determinant(matrix);
        if (det == 0)
        {
            std::cout << "inverseMatrix error: det == 0" << std::endl;
            std::exit(-1);
        }

        std::vector<std::vector<double>> inverse(rows, std::vector<double>(rows, 0));
        for (int i = 1, r = 0; r < rows; r++)
        {
            for (int j = i, c = 0; c < cols; c++)
            {
                std::vector<std::vector<T>> matrixSub = subMatrix(matrix, Coordinate<int>(r, c));
                T subDet = determinant(matrixSub);
                inverse[r][c] = (double)j * subDet / det;
                j = -j;
            }
            i = -i;
        }

        return transposeMatrix(inverse);
    }

    template<typename T>
    T determinant(const std::vector<std::vector<T>>& matrix)
    {
        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size();
        if (rows != cols)
        {
            std::cout << "determinant error" << std::endl;
            std::exit(-1);
        }

        if (rows == 1)
            return matrix[0][0];

        if (rows == 2)
            return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

        T det = 0;
        for (int i = 1, r = 0; r < rows; r++)
        {
            std::vector<std::vector<T>> matrixSub = subMatrix(matrix, Coordinate<int>(r, 0));
            det += i * matrix[r][0] * determinant(matrixSub);
            i = -i;
        }

        return det;
    }

    template<typename T>
    std::vector<std::vector<T>> transposeMatrix(const std::vector<std::vector<T>>& matrix)
    {
        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size();

        std::vector<std::vector<T>> trans(cols, std::vector<T>(rows));

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                trans[c][r] = matrix[r][c];

        return trans;
    }

    template<typename T>
    std::vector<std::vector<T>> subMatrix(const std::vector<std::vector<T>>& matrix, Coordinate<int> coord)
    {
        int rows = (int)matrix.size();
        int cols = (int)matrix[0].size();

        if (rows == 0 || cols == 0 || coord.row >= rows || coord.column >= cols || coord.row < 0 || coord.column < 0)
        {
            std::cout << "subMatrix error" << std::endl;
            std::exit(-1);
        }

        std::vector<std::vector<T>> matrixSub(rows - 1, std::vector<T>(cols - 1));

        for (int i = 0, r = 0; r < rows; r++)
        {
            if (r == coord.row)
                continue;

            for (int j = 0, c = 0; c < cols; c++)
            {
                if (c == coord.column)
                    continue;

                matrixSub[i][j] = matrix[r][c];
                j++;
            }
            i++;
        }

        return matrixSub;
    }
}