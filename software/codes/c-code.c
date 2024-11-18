#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define EPSILON 1e-6

// Function to compute the dot product of two vectors
double dot_product(double a[], double b[], int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Function to compute the norm (magnitude) of a vector
double norm(double a[], int n) {
    return sqrt(dot_product(a, a, n));
}

// Function to subtract two vectors
void subtract(double a[], double b[], double result[], int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] - b[i];
    }
}

// Function to multiply a matrix and a vector
void mat_vec_mult(double mat[MAX_SIZE][MAX_SIZE], double vec[MAX_SIZE], double result[MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
}

// Function to perform QR decomposition of matrix A and return Q and R matrices
void qr_decomposition(double A[MAX_SIZE][MAX_SIZE], double Q[MAX_SIZE][MAX_SIZE], double R[MAX_SIZE][MAX_SIZE], int n) {
    double A_copy[MAX_SIZE][MAX_SIZE];
    
    // Copy matrix A into A_copy for manipulation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }

    // Perform Gram-Schmidt to get Q and R
    for (int i = 0; i < n; i++) {
        // Column of A_copy[i] (A_i)
        double a_i[MAX_SIZE];
        for (int j = 0; j < n; j++) {
            a_i[j] = A_copy[j][i];
        }

        // For each j < i, subtract the projection of a_i on Q_j
        for (int j = 0; j < i; j++) {
            double proj = dot_product(a_i, Q[j], n);
            for (int k = 0; k < n; k++) {
                a_i[k] -= proj * Q[j][k];
            }
        }

        // Normalize a_i to create Q_i
        double norm_a_i = norm(a_i, n);
        for (int j = 0; j < n; j++) {
            Q[j][i] = a_i[j] / norm_a_i;
        }

        // Fill R with the dot products of columns of A_copy with columns of Q
        for (int j = 0; j < n; j++) {
            R[j][i] = dot_product(A_copy[j], Q[i], n);
        }
    }
}

// Function to multiply matrices A and B
void mat_mult(double A[MAX_SIZE][MAX_SIZE], double B[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to check if the matrix is diagonal (to check convergence)
int is_diagonal(double A[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && fabs(A[i][j]) > EPSILON) {
                return 0;  // Matrix is not diagonal
            }
        }
    }
    return 1;  // Matrix is diagonal
}

// Function to compute eigenvalues using QR algorithm
void qr_algorithm(double A[MAX_SIZE][MAX_SIZE], double eigenvalues[MAX_SIZE], int n) {
    double Q[MAX_SIZE][MAX_SIZE], R[MAX_SIZE][MAX_SIZE], A_copy[MAX_SIZE][MAX_SIZE], A_next[MAX_SIZE][MAX_SIZE];
    
    // Initialize A_copy to be the same as A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }

    int iteration = 0;
    while (!is_diagonal(A_copy, n) && iteration < 1000) {
        // Perform QR decomposition
        qr_decomposition(A_copy, Q, R, n);
        
        // Compute A_next = R * Q
        mat_mult(R, Q, A_next, n);
        
        // Copy A_next to A_copy
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A_copy[i][j] = A_next[i][j];
            }
        }

        iteration++;
    }

    // Extract the eigenvalues from the diagonal of the matrix
    for (int i = 0; i < n; i++) {
        eigenvalues[i] = A_copy[i][i];
    }
}

// Function to print a matrix
void print_matrix(double mat[MAX_SIZE][MAX_SIZE], int n) {
    for (inti = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    
    // Input matrix size
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);
    
    double A[MAX_SIZE][MAX_SIZE], eigenvalues[MAX_SIZE];

    // Input the matrix A
    printf("Enter the elements of the matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    // Compute the eigenvalues using the QR algorithm
    qr_algorithm(A, eigenvalues, n);

    // Output the eigenvalues
    printf("\nThe eigenvalues are:\n");
    for (int i = 0; i < n; i++) {
        printf("Eigenvalue %d: %f\n", i + 1, eigenvalues[i]);
    }

    return 0;
} 
