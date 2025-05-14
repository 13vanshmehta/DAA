/*
=============================================================================
                DESIGN AND ANALYSIS OF ALGORITHMS
                    TIME AND SPACE COMPLEXITY
=============================================================================

UNIT 1: DIVIDE AND CONQUER ALGORITHMS
-----------------------------------------------------------------------------
1. Merge Sort:
   - Time Complexity: O(n log n) in all cases (best, average, worst)
   - Space Complexity: O(n) for auxiliary array

2. Quick Sort:
   - Time Complexity: 
     * Best/Average Case: O(n log n)
     * Worst Case: O(n²) 
   - Space Complexity: O(log n) for recursion stack

3. Max-Min Problem:
   - Time Complexity: O(n) using divide and conquer
   - Space Complexity: O(log n) for recursion stack

4. Strassen's Matrix Multiplication:
   - Time Complexity: O(n^2.81) better than traditional O(n³)
   - Space Complexity: O(n²) for storing matrices

UNIT 2: GREEDY ALGORITHMS
-----------------------------------------------------------------------------
1. Fractional Knapsack:
   - Time Complexity: O(n log n) for sorting + O(n) for selection = O(n log n)
   - Space Complexity: O(1) excluding input storage

2. Activity Selection Problem:
   - Time Complexity: O(n log n) for sorting + O(n) for selection = O(n log n) {If Array is not sorted}
   - Time Complexity: O(n) if Array is already sorted in increasing order of finish times.
   - Space Complexity: O(n) for storing activities

3. Job Sequencing with Deadline:
   - Time Complexity: O(n log n) for sorting + O(n²) for scheduling = O(n²)
   - Space Complexity: O(max deadline) for result array

4. Kruskal's Algorithm (MST):
   - Time Complexity: O(E log E) or O(E log V) for sorting edges
   - Space Complexity: O(V + E) for graph representation and disjoint set

5. Prim's Algorithm (MST):
   - Time Complexity: O(E log V) with binary heap, O(V²) with adjacency matrix
   - Space Complexity: O(V + E) for graph and priority queue

6. Dijkstra's Algorithm:
   - Time Complexity: O(E log V) with binary heap, O(V²) with adjacency matrix, O(E + VlogV) with fibonacci heap
   - Space Complexity: O(V) for distance array and priority queue

7. Coin Change Problem (Greedy):
   - Time Complexity: O(n) where n is number of coin denominations
   - Space Complexity: O(1) excluding result storage

UNIT 3: DYNAMIC PROGRAMMING
-----------------------------------------------------------------------------
1. Fibonacci (DP):
   - Time Complexity: O(n) with memoization/tabulation
   - Space Complexity: O(n) for table, O(1) for optimized version

2. Coin Change Problem (DP):
   - Time Complexity: O(n × amount) where n is number of coin denominations
   - Time Complexity: O(2^n) without memoization/tabulation (exponential)
   - Space Complexity: O(amount) for 1D table

3. 0/1 Knapsack:
   - Time Complexity: O(n × W) where n is number of items, W is capacity
   - Space Complexity: O(n × W) for 2D table

4. Floyd-Warshall Algorithm:
   - Time Complexity: O(V³) where V is number of vertices
   - Space Complexity: O(V²) for distance matrix

5. Bellman-Ford Algorithm:
   - Time Complexity: O(V × E) where V is vertices, E is edges
   - Space Complexity: O(V) for distance array

6. Matrix Chain Multiplication:
   - Time Complexity: O(n³) where n is number of matrices
   - Space Complexity: O(n²) for memoization table

7. Traveling Salesperson Problem:
   - Time Complexity: O(n^2 × 2^n) using dynamic programming
   - Space Complexity: O(n × 2^n) for memoization table

8. Longest Common Subsequence:
   - Time Complexity: O(m × n) where m, n are string lengths
   - Space Complexity: O(m × n) for table, can be optimized to O(min(m,n))

UNIT 4: BACKTRACKING AND BRANCH-AND-BOUND
-----------------------------------------------------------------------------
1. N-Queen Problem:
   - Time Complexity: O(n!) in worst case
   - Time Complexity: O(2^n + 1)
   - Space Complexity: O(n) for board representation

2. Sum of Subsets:
   - Time Complexity: O(2ⁿ) in worst case
   - Space Complexity: O(n) for recursion stack

3. Graph Coloring:
   - Time Complexity: O(m^n) where m is colors, n is vertices
   - Space Complexity: O(n) for color assignment and recursion

4. Fifteen Puzzle Problem (Branch-and-Bound):
   - Time Complexity: O(b^d) where b is branching factor, d is solution depth
   - Space Complexity: O(b^d) for storing states

UNIT 5: STRING MATCHING ALGORITHMS
-----------------------------------------------------------------------------
1. Naive String Matching:
   - Time Complexity: O((n-m+1) × m) where n is text length, m is pattern length
   - Space Complexity: O(1)

2. Rabin-Karp Algorithm:
   - Time Complexity: 
     * Average Case: O(n + m)
     * Worst Case: O((n-m+1) × m) when many spurious hits
   - Space Complexity: O(1)

3. Finite Automata String Matching:
   - Time Complexity: O(n) for matching + O(m × |Σ|) for preprocessing
   - Space Complexity: O(m × |Σ|) for transition table

4. Knuth-Morris-Pratt Algorithm:
   - Time Complexity: O(n + m) where n is text length, m is pattern length
   - Space Complexity: O(m) for failure function
*/