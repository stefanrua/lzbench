#

```bash
mkdir build
cd build
cmake -DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc ..
make -j`nproc` gpu_ans gpu_float_compress
```
