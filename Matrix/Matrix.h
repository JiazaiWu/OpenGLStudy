#include<cstring>

template<typename Type>
class Matrix
{
public:
	Matrix(int R=1, int C=1, Type val=0) {
		RowN = R;
		ColumeN = C;
		mSize = R*C;
		Elem = new Type[R*C];
		for (int i = 0; i < mSize; i++) {
			Elem[i] = val;
		}
	}
	Matrix(const Matrix& matrix) {
		RowN = matrix.RowN;
		ColumeN = matrix.ColumeN;
		mSize = matrix.mSize;
		Elem = new Type[RowN * ColumeN];
		memcpy(Elem, matrix.Elem, mSize);
	}
	Matrix(int R, int C, Type* array) {
		RowN = R;
		ColumeN = C;
		mSize = R*C;
		Elem = new Type[R*C];
		for (int i = 0; i < mSize; i++) {
			Elem[i] = array[i];
		}
	}
	Matrix(int R, int C, Type** array) {
		RowN = R;
		ColumeN = C;
		mSize = R*C;
		Elem = new Type[R*C];
		for (int i = 0; i < RowN; i++) {
			for (int j = 0; j < ColumeN; j++) {
				Elem[i*C + j] = array[i][j];
			}
		}
	}
	~Matrix() {
		delete []Elem;
	}

	Type& operator()(int R, int C) {
		return Elem[ColumeN * (R-1) + (C-1)];
	}
	Matrix& operator=(const Matrix& matrix) {
		if (this == &matrix) {
			return *this;
		}
		delete []Elem;
		RowN = matrix.RowN;
		ColumeN = matrix.ColumeN;
		mSize = matrix.mSize;
		Elem = new Type[RowN * ColumeN];
		memcpy(Elem, matrix.Elem, mSize);
		return *this;
	}
	Matrix& operator+=(const Matrix& matrix) {
		if ( (RowN == matrix.RowN) && (ColumeN == matrix.ColumeN) && (mSize == matrix.mSize)) {
			for (int i = 0; i < mSize; i++) {
				Elem[i] += matrix.Elem[i];
			}
		} else {
			throw "matrix size not match";
		}
		return *this;
	}

	Matrix& operator+=(Type val) {
		for (int i = 0; i < mSize; i++) {
			Elem[i] += val;
		}
		return *this;
	}

	Matrix& operator-=(const Matrix& matrix) {
		if ( (RowN == matrix.RowN) && (ColumeN == matrix.ColumeN) && (mSize == matrix.mSize)) {
			for (int i = 0; i < mSize; i++) {
				Elem[i] -= matrix.Elem[i];
			}
		} else {
			throw "matrix size not match";
		}
		return *this;
	}
	Matrix& operator-=(Type val) {
		for (int i = 0; i < mSize; i++) {
			Elem[i] -= val;
		}
		return *this;
	}

	//matrix *= matrix is not allowed
	Matrix& operator*=(Type val) {
		for (int i = 0; i < mSize; i++) {
			Elem[i] *= val;
		}
		return *this;
	}

	bool operator==(const Matrix& matrix) {
		bool flag = true;
		if ( (RowN == matrix.RowN) && (ColumeN == matrix.ColumeN) && (mSize == matrix.mSize)) {
			for (int i = 0; i < mSize; i++) {
				if (Elem[i] != matrix.Elem[i]) {
					flag = false;
				}
			}
		} else { 
			flag = false;
		}
		return flag;
	}

	friend Matrix operator+(const Matrix& M1, const Matrix& M2) {
		if (M1.ColumeN != M2.ColumeN || M1.RowN != M2.RowN || M1.mSize != M2.mSize) {
			throw "matrix size not match";
		}
		Matrix ret(M1);
		ret += M2;
		return ret;
	}

	friend Matrix operator+(const Matrix& matrix, Type val) {
		Matrix ret(matrix);
		ret += val;
		return ret;
	}

	friend Matrix operator+(Type val, const Matrix& matrix) {
		Matrix ret(matrix);
		ret += val;
		return ret;
	}

	friend Matrix operator-(const Matrix& M1, const Matrix& M2) {
		if (M1.ColumeN != M2.ColumeN || M1.RowN != M2.RowN || M1.mSize != M2.mSize) {
			throw "matrix size not match";
		}
		Matrix ret(M1);
		ret -= M2;
		return ret;
	}

	friend Matrix operator-(const Matrix& matrix, Type val) {
		Matrix ret(matrix);
		ret -= val;
		return ret;
	}

	friend Matrix operator-(Type val, const Matrix& matrix) {
		Matrix ret(matrix.RowN, matrix.ColumeN, val);
		ret -= matrix;
		return ret;
	}

	friend Matrix operator*(const Matrix& M1, const Matrix& M2) {
		if (M1.ColumeN != M2.RowN) {
			throw "matrix size not match";
		}
		int row = M1.RowN;
		int colume = M2.ColumeN;
		int mid = M1.ColumeN;
		Matrix ret(row, colume);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colume; j++) {
				Type temp = 0;
				for (int k = 0; k < mid; k++) {
					temp += M1(i,k)*M2(k,j);
				}
				ret(i,j) = temp;
			}
		}
		return ret;
	}

	friend Matrix operator*(const Matrix& matrix, Type val) {
		Matrix ret(matrix);
		ret *= val;
		return ret;
	}

	friend Matrix operator*(Type val, const Matrix& matrix) {
		Matrix ret(matrix);
		ret *= val;
		return ret;
	}

	//TODO
	//void rerange(int R, int C);
	//Matrix T();
	//Matrix Inv();
	

private:
	int RowN;
	int ColumeN;
	int mSize;
	Type *Elem;
};