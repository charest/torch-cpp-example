
#include <torch/torch.h>
#include <c10/hip/HIPGuard.h>

#include <iostream>

int main(int argc, char** argv) {
  std::cout << "Creating tensor..." << std::endl;

  // Create a tensor
  int64_t dataSize = 1000;
  torch::Tensor data = torch::zeros({ dataSize }, torch::Device(torch::kHIP));
  std::cout << "Created data tensor" << std::endl << std::flush;

  return 0;
}


