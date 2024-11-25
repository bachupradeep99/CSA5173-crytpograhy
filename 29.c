#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// SHA-3 parameters
#define LANES 25 // Total lanes in state matrix
#define LANE_BITS 64 // Each lane is 64 bits
#define CAPACITY_LANES 8 // Last 512 bits (8 lanes) are capacity

// Function to check if all capacity lanes are non-zero
bool allCapacityNonZero(uint64_t state[]) {
    for (int i = 17; i < LANES; i++) { // Capacity lanes: 17 to 24
        if (state[i] == 0) return false;
    }
    return true;
}

int main() {
    uint64_t state[LANES] = {0}; // State matrix initialized to zeros
    uint64_t P0[LANES];          // Message block

    // Initialize P0 with non-zero values in all lanes
    for (int i = 0; i < LANES; i++) {
        P0[i] = i + 1; // Example: Non-zero unique values
    }

    int iterations = 0;

    // Iterate until all capacity lanes are non-zero
    while (!allCapacityNonZero(state)) {
        // XOR state with P0
        for (int i = 0; i < LANES; i++) {
            state[i] ^= P0[i];
        }
        iterations++;
    }

    // Output results
    printf("Total iterations to make all capacity lanes non-zero: %d\n", iterations);

    return 0;
}

