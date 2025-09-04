#pragma once

// Memory management configuration options

// Default pool size (1MB)
#ifndef MM_DEFAULT_POOL_SIZE
#define MM_DEFAULT_POOL_SIZE (1024 * 1024)
#endif

// Default block size (64 bytes)
#ifndef MM_DEFAULT_BLOCK_SIZE
#define MM_DEFAULT_BLOCK_SIZE 64
#endif

// Minimum block size (16 bytes)
#ifndef MM_MIN_BLOCK_SIZE
#define MM_MIN_BLOCK_SIZE 16
#endif

// Maximum pool size (64MB)
#ifndef MM_MAX_POOL_SIZE
#define MM_MAX_POOL_SIZE (64 * 1024 * 1024)
#endif

// Enable memory tracking (default: enabled in debug builds)
#ifndef MM_ENABLE_TRACKING
#ifdef DEBUG
#define MM_ENABLE_TRACKING 1
#else
#define MM_ENABLE_TRACKING 0
#endif
#endif

// Enable memory debugging features
#ifndef MM_ENABLE_DEBUGGING
#define MM_ENABLE_DEBUGGING 0
#endif

// Enable thread-local storage
#ifndef MM_ENABLE_TLS
#define MM_ENABLE_TLS 1
#endif

// Memory alignment (32 bytes for AVX compatibility)
#ifndef MM_ALIGNMENT
#define MM_ALIGNMENT 32
#endif

// Threshold for falling back to malloc/free (1MB)
#ifndef MM_FALLBACK_THRESHOLD
#define MM_FALLBACK_THRESHOLD (1024 * 1024)
#endif