#ifndef Vector2D_hpp_
#define Vector2D_hpp_

/* Vector2D là class vector được định nghĩa bởi 2 giá trị x, y
* Dùng để biễu diễn các đại lượng có 2 chiều: size, point, ...
* Template parameter T là 1 kiểu dữ liệu ( vd: int hoặc float) được hỗ trợ các operations (+,-,*,/) and comparisons (==, !=)
*/
template<typename T> 
class Vector2D {
public:
	Vector2D(); //Default constructor
	Vector2D(T X, T Y); // Tạo vector cụ thể (X; Y)
	template<typename U>
	explicit Vector2D(const Vector2D<U>& vector);	// Constructor này không thay thế copy constructor
													// Chỉ được called khi U != T
													// Chuyển đổi giữa các kiểu vector. vd: float -> int
	T x;
	T y;
};
template<typename T>
Vector2D<T> operator-(const Vector2D<T>& right); // Chuyển nghịch vector
template<typename T>
Vector2D<T> operator+=(Vector2D<T>& left, const Vector2D<T>& right);	// Cộng right vào left => trả về left
template<typename T>
Vector2D<T> operator-=(Vector2D<T>& left, const Vector2D<T>& right);	// Left trừ right => trả về left
template<typename T>
Vector2D<T> operator+(const Vector2D<T>& left, const Vector2D<T>& right); // Cộng 2 vector trả về vector 
template<typename T>
Vector2D<T> operator-(const Vector2D<T>& left, const Vector2D<T>& right); // Trả về hiệu 2 vector
template<typename T>
Vector2D<T> operator*(const Vector2D<T>& left, T right); // Nhân từng phần với 1 số thực
template<typename T>
Vector2D<T> operator*(T left, const Vector2D<T>& right); // Tương tự trên nhưng đảo chiều các toán hạng
template<typename T>
Vector2D<T> operator*=(Vector2D<T>& left, T right); // Nhân với right trả về left
template<typename T>
Vector2D<T> operator/(const Vector2D<T>& left, T right); // Chia left cho 1 số thực
template<typename T>
Vector2D<T> operator/=(Vector2D<T>& left, T right); // Chia và trả về left
template<typename T>
bool operator==(const Vector2D<T>& left, const Vector2D<T>& right);
template<typename T>
bool operator!=(const Vector2D<T>& left, const Vector2D<T>& right);

// các loại vector
typedef Vector2D<int> Vector2Di;
typedef Vector2D<unsigned int>  Vector2Du;
typedef Vector2D<float> Vector2Df;

template< typename T >
inline Vector2D< T >::Vector2D() : x(0), y(0) {}

template< typename T >
inline Vector2D< T >::Vector2D(T X, T Y) : x(X), y(Y) {}

template< typename T >
template< typename U >
inline Vector2D< T >::Vector2D(const Vector2D< U >& vector)
    : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) {
}

template< typename T >
inline Vector2D< T > operator-(const Vector2D< T >& right) {
    return Vector2D< T >(-right.x, -right.y);
}

template< typename T >
inline Vector2D< T >& operator+=(Vector2D< T >& left, const Vector2D< T >& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template< typename T >
inline Vector2D< T >& operator-=(Vector2D< T >& left, const Vector2D< T >& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template< typename T >
inline Vector2D< T > operator+(const Vector2D< T >& left, const Vector2D< T >& right) {
    return Vector2D< T >(left.x + right.x, left.y + right.y);
}

template< typename T >
inline Vector2D< T > operator-(const Vector2D< T >& left, const Vector2D< T >& right) {
    return Vector2D< T >(left.x - right.x, left.y - right.y);
}

template< typename T >
inline Vector2D< T > operator*(const Vector2D< T >& left, T right) {
    return Vector2D< T >(left.x * right, left.y * right);
}

template< typename T >
inline Vector2D< T > operator*(T left, const Vector2D< T >& right) {
    return Vector2D< T >(right.x * left, right.y * left);
}

template< typename T >
inline Vector2D< T >& operator*=(Vector2D< T >& left, T right) {
    left.x *= right;
    left.y *= right;
    return left;
}

template< typename T >
inline Vector2D< T > operator/(const Vector2D< T >& left, T right) {
    return Vector2D< T >(left.x / right, left.y / right);
}

template< typename T >
inline Vector2D< T >& operator/=(Vector2D< T >& left, T right) {
    left.x /= right;
    left.y /= right;
    return left;
}

template< typename T >
inline bool operator==(const Vector2D< T >& left, const Vector2D< T >& right) {
    return (left.x == right.x) && (left.y == right.y);
}

template< typename T >
inline bool operator!=(const Vector2D< T >& left, const Vector2D< T >& right) {
    return (left.x != right.x) || (left.y != right.y);
}

#endif