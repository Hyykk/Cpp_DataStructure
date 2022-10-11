class MyDoubleVector {
	public:
		MyDoubleVector(static const size_t init_capacity = 100);
		MyDoubleVector(const MyDoubleVector& source);
		~MyDoubleVector();
		MyDoubleVector& operator=(const MyDoubleVector& source);
		void operator +=(const MyDoubleVector& addend);
		double& operator[](int index);
		MyDoubleVector operator+(const MyDoubleVector& v);
		MyDoubleVector operator-(const MyDoubleVector& v);
		double operator*(const MyDoubleVector& v);
		MyDoubleVector operator-();
		bool operator==(const MyDoubleVector& v);
		MyDoubleVector operator()(double x);
		void pop_back();
		void push_back(double x);
		size_t capacity() const;
		size_t size() const;
		void reserve(size_t n);
		bool empty() const;
		void clear();
	private:
		double* data;
		size_t v_capacity;
		size_t v_size;
};