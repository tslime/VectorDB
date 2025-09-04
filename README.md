# VectorDB (from Scratch with HNSW)

VectorDB is a **vector database** implementation written in C++ that supports approximate nearest neighbor (ANN) search using the **Hierarchical Navigable Small World (HNSW)** algorithm. It is designed from the ground up with no third-party ANN libraries, to provide a clean, educational, and extensible implementation of modern ANN techniques.  


## Features
- **Vector storage**: stores dense vectors of arbitrary dimensionality (e.g., 2D, 3D, or higher).  
- **HNSW graph construction**:
  - Random level assignment for vertices (pyramid structure).  
  - Greedy descent through higher layers.  
  - Layer 0 neighbor collection (`efConstruction`).  
  - Bidirectional linking with duplicate/self-loop checks.  
- **Approximate nearest neighbor search**:
  - Greedy descent from top layer.  
  - Candidate/result heaps at layer 0.  
  - Tunable `efSearch` parameter for recall vs. speed.  
- **Pointer-free, index-based design** for fast access and portability.  
- **CRUD API**:
  - Insert vectors by ID  
  - Update existing vectors  
  - Remove vectors  
  - Retrieve vectors  
- Fully written in modern C++ (C++17), no external dependencies.

## Background

### What is a Vector Database?
A vector database stores high-dimensional numerical vectors (embeddings) and provides efficient **nearest neighbor queries**.  
These are widely used in:
- Recommendation systems  
- Natural Language Processing (semantic search, RAG pipelines)  
- Computer Vision (image similarity, clustering)  
- Robotics and navigation  

### What is HNSW?
HNSW (Hierarchical Navigable Small World) is one of the most powerful algorithms for **Approximate Nearest Neighbor (ANN)** search.  
It builds a **multi-layer graph** where:
- Layer 0 contains **all vectors**.  
- Upper layers contain progressively sparser “express lanes.”  
- Search starts at the top, descends greedily, and finishes at layer 0 using candidate expansion.  

This structure balances **speed and recall**, and scales to millions of vectors.

### 🔍 Design Note: Heap Strategy in `collect_vertices`

In the original HNSW paper by Malkov & Yashunin (2018), the neighbor collection at layer 0 was implemented using **two separate heaps**:

- A **candidate priority queue** (min-heap by distance).
- A **result set** (max-heap, bounded by `efConstruction`).

**Algorithm (Malkov’s design):**
1. Push the entry point into both heaps.
2. Pop the closest element from the candidate heap.
3. Explore its neighbors.
4. If a neighbor is closer than the farthest in the result set, insert it into both heaps.
5. Repeat until the candidate queue is empty or stable.

This works well in practice (especially with larger `efConstruction`), but has a subtle limitation:  
a candidate may be pushed into the result set *before* its closer neighbors are discovered, leading to slightly “noisy” results.


### Current Approach (Improved Heap Design)

In this implementation, I simplify the process by using a **single min-heap** owned by the class:

- When an element is popped, its neighbors are explored and pushed if valid.
- The popped element is then **reinserted** into the same heap.
- This ensures that the heap always reflects the *true closest elements* at every step.

**Advantages:**
- Eliminates the need for a separate result heap.
- Prevents premature acceptance of suboptimal candidates.
- Keeps the top of the heap always aligned with the best current neighbor.

Effectively, this turns neighbor collection into a continuous **best-first search**, making the algorithm both simpler and conceptually cleaner, while maintaining the same guarantees as the original design.


## Usage

### Inserting vectors
```cpp
VectorDB vg;

// generate random 3D vectors in [0, 1]
vector<float> t1 = vg.vector_generator_3D(0.0f, 1.0f);
vg.insert_hnsw("coco", t1);

vector<float> t2 = vg.vector_generator_3D(0.0f, 1.0f);
vg.insert_hnsw("toto", t2);

vector<float> t3 = vg.vector_generator_3D(0.0f, 1.0f);
vg.insert_hnsw("lulu", t3);


