#ifndef _VEC_H
#define _VEC_H

#include <fstream>
#include <vector>

namespace VEC {

class VecF;
class VecD;
class VecI;

// BEGIN TEMPLATE

class VecF {

    protected:
    // length
    int _n;
    std::vector<float> _dat;

    public:
    // Constructors:

    // Creates an empty VecF vector.
    VecF();

    // Creates a VecF with given size but data values are NOT set by default.
    explicit VecF(int n);

    // Creates a VecF with given size and initializes all elements to a given
    // default value.
    VecF(int n, const float &val);

    // Construct using an STL vector.
    VecF(int n, std::vector<float>& arr);

    // Construct using another VecF.
    VecF(const VecF &A);

    float first() { return _dat.front(); }
    float last() { return _dat.back(); }

    // Returns the name of the class
    // del needs to be called
    char * class_name();

    // Set the size and internal vector to the given values.
    void set(int n, std::vector<float> arr);

    // Same as `VecF::set` now, but allowed to remain for legacy semantics.
    void take(int n, std::vector<float> arr);

    void to_d(VecD &out);
    void to_i(VecI &out);

    // returns the first index at the value, else -1
    int index(float val);

    // Copies the data and length and essentially becoming a copy of the given
    // VecF.
    void set(VecF &A);

    // Same as its `VecF::set` equivalent now, but allowed to remain for legacy
    // semantics.
    void take(VecF &A);

    VecF & operator=(const float &val);
    VecF & operator=(VecF &A);
    ~VecF();

    // Changes the receiver's data and length to match its own, essentially
    // making them both copies of each other.
    void copy(VecF &receiver) const;

    bool operator==(const VecF &A);

    int length() const { return _n; }
    int len() const { return _n; }
    int size() const { return _n; }
    int dim() const { return _n; }
    int dim1() const { return _n; }

    // Returns in a vector all the values matching mask value
    void mask_as_vec(float return_val, VecI &mask, VecF &vec);

    // Returns true if all values are the same, false otherwise
    bool all_equal() {
        float _min, _max; min_max(_min, _max);
        if (_min == _max) { return 1; }
        else { return 0; }
    }

    float& operator[](int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const float& operator[](int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    float& at(int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const float& at(int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    bool shallow() {
        return false;
    }

    std::vector<float> slice(int start, int end);
    std::pair<std::vector<float>::iterator, std::vector<float>::iterator> slice2(int start, int end);
    float* data();

    // NOTE: All operators act on the caller!
    // Operators
    void operator+=(const VecF &A);
    void operator-=(const VecF &A);
    void operator*=(const VecF &A);
    void operator/=(const VecF &A);
    void operator+=(float val);
    void operator-=(float val);
    void operator*=(float val);
    void operator/=(float val);

    void add(const VecF &toadd, VecF &out);
    void sub(const VecF &tosub, VecF &out);
    void mul(const VecF &tomul, VecF &out);
    void div(const VecF &todiv, VecF &out);

    void square_root();
    void logarithm(double base);
    void min_max(float &mn, float &mx);

    // alias for min_max
    void mn_mx(float &mn, float &mx) {min_max(mn,mx);}

    double avg() const;
    void hist(int num_bins, VecD &bins, VecI &freqs);
    void sample_stats(double &mean, double &std_dev);
    double prob_one_side_right(double x);
    float sum();
    float sum_of_sq();

    void abs_val();

    // converts the distribution of values into standard normal
    // Only for floating points right now!
    void std_normal();

    // uses quicksort to sort the values
    void sort();

    // Removes the value at index and shortens the array by one.
    void remove(int index);

    //VecF operator+(const VecF &A);
    //void operator++();
    //void operator--();

    // CLASS FUNCTIONS:
    static int pchst(float arg1, float arg2) {
        if      (arg1*arg2 > 0) { return  1; }
        else if (arg1*arg2 < 0) { return -1; }
        else                    { return  0; }
    }

    static double pearsons_r(VecF &x, VecF &y);
    static double covariance(VecF &x, VecF &y);
    static double euclidean(VecF &x, VecF &y);
    static float dot_product(VecF &x, VecF &y);

    static void xy_to_x(VecF &x, VecF &y);
    static void x_to_xy(VecF &x, VecF &y);
    static void chim(VecF &x, VecF &y, VecF &out_derivs);

    static void calc_cubic_coeff(VecF &x, VecF &y, VecF &derivs, VecF &c2, VecF &c3);
    static void chfe(VecF &xin, VecF &yin, VecF &xe, VecF &out_ye, int sorted=0);
    //static void pchfe(VecF &xin, VecF &yin, VecF &XE, VecF &out_newy);
    // interpolates so that linearity is encouraged along x axis
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static inline void chfev(float X1, float F1, float D1, float C2, float C3, float XE, float &FE);
    static inline void chfev_all(float X1, float X2, float F1, float F2, float D1, float D2, float XE, float &FE);
    // static void chfev(float X1, float X2, float F1, float F2, float D1, float D2, int NE, float *XE, float *FE, int *nlr, int &ierr);

    // interpolates so that linearity is encouraged along the xy line
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static void chfe_xy(VecF &x, VecF &y, VecF &new_x, VecF &out_new_y, int sorted=0);

    static void linear_derivs(VecF &x, VecF &y, VecF &out_derivs);
    static void linear_interp(VecF &xin, VecF &yin, VecF &xe, VecF &out_ye, int sorted=0);
    //##### FOR ANY FUNCTION:
    //                B
    //               /|
    //              / |
    //             /  |
    //          c /   |a
    //           /    |
    //          /     |
    //       A --------C
    //             b
    //
    //  cPerp = Perpendicular from C to c
    //  (sin A)/a = (sin C)/c
    //  sin C = 1
    //  c = sqrt(a^2 + b^2)
    //  sin A = a/c
    //  cPerp = (a/c)*b      note:   = sin A * b
    //  cPerp^2 = (ab)^2/(a^2 + b^2)

    // g(x):  y = x
    // h(y):  x = y
    //  a = y - g(x)

    // b = actual x - (x = actual y)
    // a = actual y - (y = actual x)
    // avg residual = SUM(cPerp^2)/N
    //

    //###### FOR X=Y
    // residual^2 = 1/2((Y-X)^2)        note: [or X-Y]
    static double sum_sq_res_yeqx(VecF &x, VecF &y);
    // divides the sum of square of residuals by the length of the vector
    static double avg_sq_res_yeqx(VecF &x, VecF &y);

    // returns the average of the absolute values of the differences at
    // each index
    static double avg_abs_diff(VecF &x, VecF &y);
    static void rsq_slope_intercept(VecF &x, VecF &y, double &rsq, double &slope, double &y_intercept);

    private:
    static void outliers_from_regression_line(VecF &x, VecF &y, VecI &indices_out);
    double _zScore(double mean, double sigma, double x);

}; // End class VecF

class VecD {

    protected:
    // length
    int _n;
    std::vector<double> _dat;

    public:
    // Constructors:

    // Creates an empty VecD vector.
    VecD();

    // Creates a VecD with given size but data values are NOT set by default.
    explicit VecD(int n);

    // Creates a VecD with given size and initializes all elements to a given
    // default value.
    VecD(int n, const double &val);

    // Construct using an STL vector.
    VecD(int n, std::vector<double>& arr);

    // Construct using another VecD.
    VecD(const VecD &A);

    double first() { return _dat.front(); }
    double last() { return _dat.back(); }

    // Returns the name of the class
    // del needs to be called
    char * class_name();

    // Set the size and internal vector to the given values.
    void set(int n, std::vector<double> arr);

    // Same as `VecD::set` now, but allowed to remain for legacy semantics.
    void take(int n, std::vector<double> arr);

    void to_f(VecF &out);
    void to_i(VecI &out);

    // returns the first index at the value, else -1
    int index(double val);

    // Copies the data and length and essentially becoming a copy of the given
    // VecD.
    void set(VecD &A);

    // Same as its `VecD::set` equivalent now, but allowed to remain for legacy
    // semantics.
    void take(VecD &A);

    VecD & operator=(const double &val);
    VecD & operator=(VecD &A);
    ~VecD();

    // Changes the receiver's data and length to match its own, essentially
    // making them both copies of each other.
    void copy(VecD &receiver) const;

    bool operator==(const VecD &A);

    int length() const { return _n; }
    int len() const { return _n; }
    int size() const { return _n; }
    int dim() const { return _n; }
    int dim1() const { return _n; }

    // Returns in a vector all the values matching mask value
    void mask_as_vec(double return_val, VecI &mask, VecD &vec);

    // Returns true if all values are the same, false otherwise
    bool all_equal() {
        double _min, _max; min_max(_min, _max);
        if (_min == _max) { return 1; }
        else { return 0; }
    }

    double& operator[](int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const double& operator[](int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    double& at(int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const double& at(int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    bool shallow() {
        return false;
    }

    std::vector<double> slice(int start, int end);
    std::pair<std::vector<double>::iterator, std::vector<double>::iterator> slice2(int start, int end);
    double* data();

    // NOTE: All operators act on the caller!
    // Operators
    void operator+=(const VecD &A);
    void operator-=(const VecD &A);
    void operator*=(const VecD &A);
    void operator/=(const VecD &A);
    void operator+=(double val);
    void operator-=(double val);
    void operator*=(double val);
    void operator/=(double val);

    void add(const VecD &toadd, VecD &out);
    void sub(const VecD &tosub, VecD &out);
    void mul(const VecD &tomul, VecD &out);
    void div(const VecD &todiv, VecD &out);

    void square_root();
    void logarithm(double base);
    void min_max(double &mn, double &mx);

    // alias for min_max
    void mn_mx(double &mn, double &mx) {min_max(mn,mx);}

    double avg() const;
    void hist(int num_bins, VecD &bins, VecI &freqs);
    void sample_stats(double &mean, double &std_dev);
    double prob_one_side_right(double x);
    double sum();
    double sum_of_sq();

    void abs_val();

    // converts the distribution of values into standard normal
    void std_normal();

    // uses quicksort to sort the values
    void sort();

    // Removes the value at index and shortens the array by one.
    void remove(int index);

    //VecD operator+(const VecD &A);
    //void operator++();
    //void operator--();

    // CLASS FUNCTIONS:
    static int pchst(double arg1, double arg2) {
        if      (arg1*arg2 > 0) { return  1; }
        else if (arg1*arg2 < 0) { return -1; }
        else                    { return  0; }
    }

    static double pearsons_r(VecD &x, VecD &y);
    static double covariance(VecD &x, VecD &y);
    static double euclidean(VecD &x, VecD &y);
    static double dot_product(VecD &x, VecD &y);

    static void xy_to_x(VecD &x, VecD &y);
    static void x_to_xy(VecD &x, VecD &y);
    static void chim(VecD &x, VecD &y, VecD &out_derivs);

    static void calc_cubic_coeff(VecD &x, VecD &y, VecD &derivs, VecD &c2, VecD &c3);
    static void chfe(VecD &xin, VecD &yin, VecD &xe, VecD &out_ye, int sorted=0);
    //static void pchfe(VecD &xin, VecD &yin, VecD &XE, VecD &out_newy);
    // interpolates so that linearity is encouraged along x axis
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static inline void chfev(double X1, double F1, double D1, double C2, double C3, double XE, double &FE);
    static inline void chfev_all(double X1, double X2, double F1, double F2, double D1, double D2, double XE, double &FE);
    // static void chfev(double X1, double X2, double F1, double F2, double D1, double D2, int NE, double *XE, double *FE, int *nlr, int &ierr);

    // interpolates so that linearity is encouraged along the xy line
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static void chfe_xy(VecD &x, VecD &y, VecD &new_x, VecD &out_new_y, int sorted=0);

    static void linear_derivs(VecD &x, VecD &y, VecD &out_derivs);
    static void linear_interp(VecD &xin, VecD &yin, VecD &xe, VecD &out_ye, int sorted=0);
    //##### FOR ANY FUNCTION:
    //                B
    //               /|
    //              / |
    //             /  |
    //          c /   |a
    //           /    |
    //          /     |
    //       A --------C
    //             b
    //
    //  cPerp = Perpendicular from C to c
    //  (sin A)/a = (sin C)/c
    //  sin C = 1
    //  c = sqrt(a^2 + b^2)
    //  sin A = a/c
    //  cPerp = (a/c)*b      note:   = sin A * b
    //  cPerp^2 = (ab)^2/(a^2 + b^2)

    // g(x):  y = x
    // h(y):  x = y
    //  a = y - g(x)

    // b = actual x - (x = actual y)
    // a = actual y - (y = actual x)
    // avg residual = SUM(cPerp^2)/N
    //

    //###### FOR X=Y
    // residual^2 = 1/2((Y-X)^2)        note: [or X-Y]
    static double sum_sq_res_yeqx(VecD &x, VecD &y);
    // divides the sum of square of residuals by the length of the vector
    static double avg_sq_res_yeqx(VecD &x, VecD &y);

    // returns the average of the absolute values of the differences at
    // each index
    static double avg_abs_diff(VecD &x, VecD &y);
    static void rsq_slope_intercept(VecD &x, VecD &y, double &rsq, double &slope, double &y_intercept);

    private:
    static void outliers_from_regression_line(VecD &x, VecD &y, VecI &indices_out);
    double _zScore(double mean, double sigma, double x);

}; // End class VecD

class VecI {

    protected:
    // length
    int _n;
    std::vector<int> _dat;

    public:
    // Constructors:

    // Creates an empty VecI vector.
    VecI();

    // Creates a VecI with given size but data values are NOT set by default.
    explicit VecI(int n);

    // Creates a VecI with given size and initializes all elements to a given
    // default value.
    VecI(int n, const int &val);

    // Construct using an STL vector.
    VecI(int n, std::vector<int>& arr);

    // Construct using another VecI.
    VecI(const VecI &A);

    int first() { return _dat.front(); }
    int last() { return _dat.back(); }

    // Returns the name of the class
    // del needs to be called
    char * class_name();

    // Set the size and internal vector to the given values.
    void set(int n, std::vector<int> arr);

    // Same as `VecI::set` now, but allowed to remain for legacy semantics.
    void take(int n, std::vector<int> arr);

    void to_f(VecF &out);
    void to_d(VecD &out);

    // returns the first index at the value, else -1
    int index(int val);

    // Copies the data and length and essentially becoming a copy of the given
    // VecI.
    void set(VecI &A);

    // Same as its `VecI::set` equivalent now, but allowed to remain for legacy
    // semantics.
    void take(VecI &A);

    VecI & operator=(const int &val);
    VecI & operator=(VecI &A);
    ~VecI();

    // Changes the receiver's data and length to match its own, essentially
    // making them both copies of each other.
    void copy(VecI &receiver) const;

    bool operator==(const VecI &A);

    int length() const { return _n; }
    int len() const { return _n; }
    int size() const { return _n; }
    int dim() const { return _n; }
    int dim1() const { return _n; }

    // Returns in a vector all the values matching mask value
    void mask_as_vec(int return_val, VecI &mask, VecI &vec);

    // Returns true if all values are the same, false otherwise
    bool all_equal() {
        int _min, _max; min_max(_min, _max);
        if (_min == _max) { return 1; }
        else { return 0; }
    }

    int& operator[](int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const int& operator[](int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    int& at(int i) {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }
    const int& at(int i) const {
#ifdef JTP_BOUNDS_CHECK
        if (i < 0) { puts("index < 0 !"); exit(1); }
        if (i >= _n) { puts("i >= _n !"); exit(1); }
#endif
        return _dat[i];
    }

    bool shallow() {
        return false;
    }

    std::vector<int> slice(int start, int end);
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> slice2(int start, int end);
    int* data();

    // NOTE: All operators act on the caller!
    // Operators
    void operator+=(const VecI &A);
    void operator-=(const VecI &A);
    void operator*=(const VecI &A);
    void operator/=(const VecI &A);
    void operator+=(int val);
    void operator-=(int val);
    void operator*=(int val);
    void operator/=(int val);

    void add(const VecI &toadd, VecI &out);
    void sub(const VecI &tosub, VecI &out);
    void mul(const VecI &tomul, VecI &out);
    void div(const VecI &todiv, VecI &out);

    void square_root();
    void logarithm(double base);
    void min_max(int &mn, int &mx);

    // alias for min_max
    void mn_mx(int &mn, int &mx) {min_max(mn,mx);}

    double avg() const;
    void hist(int num_bins, VecD &bins, VecI &freqs);
    void sample_stats(double &mean, double &std_dev);
    double prob_one_side_right(double x);
    int sum();
    int sum_of_sq();

    void abs_val();

    // converts the distribution of values into standard normal
    void std_normal();

    // uses quicksort to sort the values
    void sort();

    // Removes the value at index and shortens the array by one.
    void remove(int index);

    //VecI operator+(const VecI &A);
    //void operator++();
    //void operator--();

    // CLASS FUNCTIONS:
    static int pchst(int arg1, int arg2) {
        if      (arg1*arg2 > 0) { return  1; }
        else if (arg1*arg2 < 0) { return -1; }
        else                    { return  0; }
    }

    static double pearsons_r(VecI &x, VecI &y);
    static double covariance(VecI &x, VecI &y);
    static double euclidean(VecI &x, VecI &y);
    static int dot_product(VecI &x, VecI &y);

    static void xy_to_x(VecI &x, VecI &y);
    static void x_to_xy(VecI &x, VecI &y);
    static void chim(VecI &x, VecI &y, VecI &out_derivs);

    static void calc_cubic_coeff(VecI &x, VecI &y, VecI &derivs, VecI &c2, VecI &c3);
    static void chfe(VecI &xin, VecI &yin, VecI &xe, VecI &out_ye, int sorted=0);
    //static void pchfe(VecI &xin, VecI &yin, VecI &XE, VecI &out_newy);
    // interpolates so that linearity is encouraged along x axis
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static inline void chfev(int X1, int F1, int D1, int C2, int C3, int XE, int &FE);
    static inline void chfev_all(int X1, int X2, int F1, int F2, int D1, int D2, int XE, int &FE);
    // static void chfev(int X1, int X2, int F1, int F2, int D1, int D2, int NE, int *XE, int *FE, int *nlr, int &ierr);

    // interpolates so that linearity is encouraged along the xy line
    // if out_new_y.length() == 0 then new memory is allocated
    // otherwise, uses whatever memory is allocated in out_new_y
    static void chfe_xy(VecI &x, VecI &y, VecI &new_x, VecI &out_new_y, int sorted=0);

    static void linear_derivs(VecI &x, VecI &y, VecI &out_derivs);
    static void linear_interp(VecI &xin, VecI &yin, VecI &xe, VecI &out_ye, int sorted=0);
    //##### FOR ANY FUNCTION:
    //                B
    //               /|
    //              / |
    //             /  |
    //          c /   |a
    //           /    |
    //          /     |
    //       A --------C
    //             b
    //
    //  cPerp = Perpendicular from C to c
    //  (sin A)/a = (sin C)/c
    //  sin C = 1
    //  c = sqrt(a^2 + b^2)
    //  sin A = a/c
    //  cPerp = (a/c)*b      note:   = sin A * b
    //  cPerp^2 = (ab)^2/(a^2 + b^2)

    // g(x):  y = x
    // h(y):  x = y
    //  a = y - g(x)

    // b = actual x - (x = actual y)
    // a = actual y - (y = actual x)
    // avg residual = SUM(cPerp^2)/N
    //

    //###### FOR X=Y
    // residual^2 = 1/2((Y-X)^2)        note: [or X-Y]
    static double sum_sq_res_yeqx(VecI &x, VecI &y);
    // divides the sum of square of residuals by the length of the vector
    static double avg_sq_res_yeqx(VecI &x, VecI &y);

    // returns the average of the absolute values of the differences at
    // each index
    static double avg_abs_diff(VecI &x, VecI &y);
    static void rsq_slope_intercept(VecI &x, VecI &y, double &rsq, double &slope, double &y_intercept);

    private:
    static void outliers_from_regression_line(VecI &x, VecI &y, VecI &indices_out);
    double _zScore(double mean, double sigma, double x);

}; // End class VecI

// END TEMPLATE

} // End namespace

#endif

