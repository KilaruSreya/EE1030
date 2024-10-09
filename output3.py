import matplotlib.pyplot as plt

def read_vectors_from_file(filename):
    # Reading vectors from the text file
    with open(filename, 'r') as file:
        lines = file.readlines()
        
    # Extracting vector values from the lines
    vectors = []
    for line in lines:
        parts = line.split(':')[-1].strip().replace('(', '').replace(')', '').split(',')
        vectors.append((float(parts[0]), float(parts[1])))
    
    return vectors

def plot_triangle(vectors):
    # Assuming the vectors are in the order BA, BC, AC from the file
    # We will compute A, B, C points from the given vectors
    B = (0, 0)  # Assuming B is at origin
    A = (B[0] + vectors[0][0], B[1] + vectors[0][1])  # A = B + BA
    C = (B[0] + vectors[1][0], B[1] + vectors[1][1])  # C = B + BC
    
    # Plotting the triangle
    plt.figure()
    
    # Plot the triangle sides
    plt.plot([A[0], B[0]], [A[1], B[1]], label="AB")
    plt.plot([B[0], C[0]], [B[1], C[1]], label="BC")
    plt.plot([A[0], C[0]], [A[1], C[1]], label="AC")
    
    # Plot points A, B, C
    plt.scatter([A[0], B[0], C[0]], [A[1], B[1], C[1]], color="red")
    
    # Annotate the points
    plt.text(A[0], A[1], 'A ({:.2f}, {:.2f})'.format(A[0], A[1]), fontsize=12, ha='right')
    plt.text(B[0], B[1], 'B ({:.2f}, {:.2f})'.format(B[0], B[1]), fontsize=12, ha='right')
    plt.text(C[0], C[1], 'C ({:.2f}, {:.2f})'.format(C[0], C[1]), fontsize=12, ha='right')

    # Label the axes and the plot
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.title("Triangle ABC")
    plt.grid(True)
    plt.legend()

    # Display the plot
    plt.show()

if __name__ == "__main__":
    # Reading vectors from the file
    vectors = read_vectors_from_file('points.txt')
    
    # Plot the triangle ABC
    plot_triangle(vectors)
