#ifndef cudaCheck_h
#define cudaCheck_h

// C++ standard headers
#include <iostream>
#include <sstream>
#include <stdexcept>

// CUDA headers
#include <cuda.h>
#include <cuda_runtime.h>

namespace {

  [[noreturn]] inline void printCudaErrorMessage(
      const char* file, int line, const char* cmd, const char* error, const char* message) {
    std::ostringstream out;
    out << "\n";
    out << file << ", line " << line << ":\n";
    out << "cudaCheck(" << cmd << ");\n";
    out << error << ": " << message << "\n";
    throw std::runtime_error(out.str());
  }

}  // namespace

inline bool cudaCheck_(const char* file, int line, const char* cmd, CUresult result) {
  if (__builtin_expect(result == CUDA_SUCCESS, true))
    return true;

  const char* error;
  const char* message;
  cuGetErrorName(result, &error);
  cuGetErrorString(result, &message);
  printCudaErrorMessage(file, line, cmd, error, message);
  return false;
}

inline bool cudaCheck_(const char* file, int line, const char* cmd, cudaError_t result) {
  if (__builtin_expect(result == cudaSuccess, true))
    return true;

  const char* error = cudaGetErrorName(result);
  const char* message = cudaGetErrorString(result);
  printCudaErrorMessage(file, line, cmd, error, message);
  return false;
}

#define cudaCheck(ARG) (cudaCheck_(__FILE__, __LINE__, #ARG, (ARG)))

#define CUDA_CHECK(ARG) (cudaCheck_(__FILE__, __LINE__, #ARG, (ARG)))

#endif  // cudaCheck_h
