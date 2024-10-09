#include <stdio.h>

// Structure to represent a 2D vector
typedef struct {
    double x;
    double y;
} Vector;

// Function to calculate vector AC = -BA + BC
Vector calculate_AC(Vector BA, Vector BC) {
    Vector AC;
    AC.x = -BA.x + BC.x;
    AC.y = -BA.y + BC.y;
    return AC;
}

int main() {
    Vector BA, BC, AC;
    
    // Assigning values of vector BA (2a) and vector BC (3b)
    BA.x = 2.0;
    BA.y = 1.0;
    
    BC.x = 3.0;
    BC.y = 2.0;

    // Calculate vector AC
    AC = calculate_AC(BA, BC);

    // Write the vectors to a text file
    FILE *file = fopen("points.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "Vector BA (2a): (%.2f, %.2f)\n", BA.x, BA.y);
    fprintf(file, "Vector BC (3b): (%.2f, %.2f)\n", BC.x, BC.y);
    fprintf(file, "Vector AC: (%.2f, %.2f)\n", AC.x, AC.y);

    fclose(file);
    printf("Vectors written to points.txt successfully.\n");

    return 0;
}
