# Backend

## Introduction

This package provides optimized computational backends for Brokly, supporting multiple hardware architectures and data types. It enables high-performance mathematical operations by leveraging specialized CPU instruction sets when available.

## Architecture

The backend is organized in a hierarchical structure:

```tree
backend/
├── [hardware]/           # Target hardware architecture
│   ├── [precision]/      # Data type precision
│   │   ├── [entity].h    # Function declarations
│   │   └── [entity].c    # Function implementations
```

### Directory Structure

- **Hardware Level** (`plain`, `avx`, ...): Target CPU instruction set
  - `plain`: Standard C implementation (portable, no special instructions)
  - `avx`: Intel AVX instruction set optimized implementation

- **Precision Level** (`fp32`, `fp16`, `int8`, ...): Data type precision
  - `fp32`: 32-bit floating point
  - `fp16`: 16-bit floating point
  - `int8`: 8-bit integer
  - And others as supported

- **Entity Level** (`vec`, `mat`, ...): The data structure being operated on
  - `vec`: Vector operations
  - `mat`: Matrix operations

### Implementation Details

Each implementation file contains multiple functions that perform operations on arrays or scalars. Functions are typically named following the pattern:
`[operation]_[datatype]_[hardware]`

For example:

- `add_fp32_avx`: Vector addition for 32-bit floats using AVX
- `ipr_fp32`: Inner product for 32-bit floats using plain C

## Current Implementations

### Vector Operations (vec)

- `add`: Element-wise vector addition
- `ipr`: Inner product (dot product) of two vectors

## Future Improvements

- [ ] Implement proper AVX vectorized functions in `src/backend/avx/fp32/vec.c`
- [ ] Add CPU feature detection mechanism to automatically select the best backend at runtime
- [ ] Create a unified interface for backend functions that abstracts the implementation details
- [ ] Update CMakeLists.txt to properly build and link the backend implementations
- [ ] Add support for other data types (fp16, int8, etc.)
- [ ] Add support for other instruction sets (SSE, AVX2, AVX-512)
- [ ] Implement additional mathematical operations (multiplication, division, etc.)
- [ ] Add benchmarking tools to compare performance across implementations
  