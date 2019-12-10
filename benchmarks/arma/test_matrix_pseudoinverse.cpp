/*
Code made by Nghia Ho (http://nghiaho.com/uploads/code/test_matrix_pseudoinverse.cpp) with full
authorship.
*/

// With Atlas
// g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lcblas -llapack_atlas -lgsl -lgslcblas -march=native -O3 -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF

// With OpenBLAS
// g++ test_matrix_pseudoinverse.cpp -o test_matrix_pseudoinverse -L/usr/lib/atlas-base -L/usr/lib/openblas-base -lopencv_core -larmadillo -lgomp -fopenmp -lopenblas -llapack_atlas -lgsl -lgslcblas -march=native -O3 -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF

// Short benchmark doing psuedo-inverse of the form:
// AX = B
// X = (A'A)^-1*A'*B
// for various dimension sizes

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <algorithm>
#include <vector>

// GSL can't coexist with Armadillo due to enum conflicts

// Turn each one on one at a time to make the spreadsheet
// #define TEST_OPENCV
// #define TEST_EIGEN
#define TEST_ARMA
//#define TEST_GSL

#include <opencv2/core/core.hpp>

#ifdef TEST_EIGEN
#include <eigen3/Eigen/Dense>
#endif

#ifdef TEST_ARMA
#include <armadillo>
#endif

#ifdef TEST_GSL
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#endif

using namespace std;

double TimeDiff(timeval t1, timeval t2);
double RunOpenCV(int N, int M, vector <double> &A, vector <double> &B, int iterations);
double RunEigen(int N, int M, vector <double> &A, vector <double> &B, int iterations);
double RunArmadillo(int N, int M, vector <double> &A, vector <double> &B, int iterations);
double RunGSL(int N, int M, vector <double> &A, vector <double> &B, int iterations);

int main()
{
    const int N = 1000000;
    const int iterations = 10;

    for(int M=2; M <= 16; M++) { // dimension
        vector <double> A(N*M);
        vector <double> B(N);
        vector <double> X(M);

        // Generate some random data
        for(size_t i=0; i < X.size(); i++) {
            X[i] = rand()/(1.0 + RAND_MAX);
        }

        for(size_t i=0; i < A.size(); i++) {
            A[i] = rand()/(1.0 + RAND_MAX);
        }

        cv::Mat _A(N, M, CV_64F, &A[0]);
        cv::Mat _X(M, 1, CV_64F, &X[0]);
        cv::Mat _B(N, 1, CV_64F, &B[0]);

        _B = _A*_X;

        // Add a bit of noise to B, probably not necessary for benchmarking
        for(size_t i=0; i < B.size(); i++) {
            B[i] += -1.0 + 2*rand()/(1.0+RAND_MAX);
        }
        
        //////////////////////////////////////////////////////

#ifdef TEST_OPENCV
        cout <<  RunOpenCV(N, M, A, B, iterations) << " ";
        //cout << "OpenCV: " << RunOpenCV(N, M, A, B, iterations) << endl;
#endif

#ifdef TEST_EIGEN
        //cout << "Eigen: " << RunEigen(N, M, A, B, iterations) << endl;
        // cout <<"iterations: " <<  iterations << endl;
        // cout <<  RunEigen(N, M, A, B, iterations) << " ";
        printf("N: %d, M: %d, iterations:%d, runtime: %f ms\n",  N, M, iterations, RunEigen(N, M, A, B, iterations));
#endif

#ifdef TEST_ARMA
        //cout << "Arma: " << RunArmadillo(N, M, A, B, iterations) << endl;
        cout << RunArmadillo(N, M, A, B, iterations) << " ";
#endif

#ifdef TEST_GSL
        //cout << "GSL: " << RunGSL(N, M, A, B, iterations) << endl;
        cout << RunGSL(N, M, A, B, iterations) << " ";
#endif
    }

    cout << endl;

	return 0;
}

double TimeDiff(timeval t1, timeval t2)
{
    double t;

    t = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    t += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

    return t;
}

#ifdef TEST_OPENCV
double RunOpenCV(int N, int M, vector <double> &A, vector <double> &B, int iterations)
{
    // OpenCV has a nice constructor to allow using existing memory
    cv::Mat _A(N, M, CV_64F, &A[0]);
    cv::Mat _B(N, 1, CV_64F, &B[0]);
    cv::Mat X;
    timeval t1, t2;

	gettimeofday(&t1, NULL);
    for(int i=0; i < iterations; i++) {
        X = (_A.t()*_A).inv()*(_A.t()*_B);
    }
	gettimeofday(&t2, NULL);

    double d = TimeDiff(t1, t2);

    //for(int i=0; i < M; i++) {
    //    cout << "OpenCV X: " << X.at<double>(i,0) << endl;
    //}

    return d;
}
#endif

#ifdef TEST_EIGEN
double RunEigen(int N, int M, vector <double> &A, vector <double> &B, int iterations)
{
	Eigen::MatrixXd _A(N,M);
	Eigen::MatrixXd _B(N,1);
    Eigen::MatrixXd X(M,1);
    timeval t1, t2;

    // Copy the data, there's a better way right?
    // Eigen seems to have one but the example only shows using known matrix size at compiled time
    for(int i=0; i < N; i++) {
        _B(i,0) = B[i];
        for(int j=0; j < M; j++) {
            _A(i,j) = A[i*M+j];
        }
    }

	gettimeofday(&t1, NULL);
    for(int i=0; i < iterations; i++) {
        X = (_A.transpose()*_A).inverse()*(_A.transpose()*_B);
    }
	gettimeofday(&t2, NULL);

    double d = TimeDiff(t1, t2);

    //for(int i=0; i < M; i++) {
    //    cout << "Eigen X: " << X(i,0) << endl;
    //}

    return d;
}
#endif

#ifdef TEST_ARMA
double RunArmadillo(int N, int M, vector <double> &A, vector <double> &B, int iterations)
{
	arma::mat _A(N,M);
	arma::mat _B(N,1);
    arma::mat X(M,1);
    timeval t1, t2;

    // Copy the data, there's a better way right?
    for(int i=0; i < N; i++) {
        _B(i,0) = B[i];
        for(int j=0; j < M; j++) {
            _A(i,j) = A[i*M+j];
        }
    }

	gettimeofday(&t1, NULL);
    for(int i=0; i < iterations; i++) {
        X = arma::inv(arma::trans(_A)*_A)*(arma::trans(_A)*_B);
    }
	gettimeofday(&t2, NULL);

    double d = TimeDiff(t1, t2);

    //for(int i=0; i < M; i++) {
    //    cout << "Arma X: " << X(i,0) << endl;
    //}

    return d;
}
#endif

#ifdef TEST_GSL
double RunGSL(int N, int M, vector <double> &A, vector <double> &B, int iterations)
{
    // Use the cblas wrapper in GSL
    // Need some temporary member to do the calculation
    gsl_matrix *_A = gsl_matrix_alloc(N, M);
    gsl_matrix *_B = gsl_matrix_alloc(N, 1);
    gsl_matrix *At = gsl_matrix_alloc(M, N);
    gsl_matrix *AtA = gsl_matrix_alloc(M, M);
    gsl_matrix *At_B = gsl_matrix_alloc(M, 1);
    gsl_matrix *tmp = gsl_matrix_alloc(M, M);
    gsl_matrix *inv_AtA = gsl_matrix_alloc(M, M);
    gsl_matrix *inv_AtA_At = gsl_matrix_alloc(M, N);
    gsl_matrix *X = gsl_matrix_alloc(M, 1);
    gsl_permutation *p = gsl_permutation_alloc(M);

    timeval t1, t2;

    // Copy the data, there's a better way right?
    for(int i=0; i < N; i++) {
        gsl_matrix_set(_B, i, 0, B[i]);
        for(int j=0; j < M; j++) {
            gsl_matrix_set(_A, i, j, A[i*M+j]);
        }
    }

	gettimeofday(&t1, NULL);
    for(int i=0; i < iterations; i++) {
        gsl_matrix_transpose_memcpy(At, _A);

        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, At, _A, 0.0, AtA);

        // Invert AtA
        int s;
        gsl_matrix_memcpy(tmp, AtA);
        gsl_linalg_LU_decomp(tmp, p, &s);
        gsl_linalg_LU_invert(tmp, p, inv_AtA); // doesn't support src and dst being the same

        //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, inv_AtA, At, 0.0, inv_AtA_At);
        //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, inv_AtA_At, _B, 0.0, X);
        gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, _A, _B, 0.0, At_B);
        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, inv_AtA, At_B, 0.0, X);
    }
	gettimeofday(&t2, NULL);

    double d = TimeDiff(t1, t2);

    //for(int i=0; i < M; i++) {
    //    cout << "GSL X: " << gsl_matrix_get(X, i, 0) << endl;
    //}

    gsl_matrix_free(_A);
    gsl_matrix_free(_B);
    gsl_matrix_free(At);
    gsl_matrix_free(AtA);
    gsl_matrix_free(At_B);
    gsl_matrix_free(tmp);
    gsl_matrix_free(inv_AtA);
    gsl_matrix_free(inv_AtA_At);
    gsl_matrix_free(X);
	gsl_permutation_free(p);

    return d;
}
#endif