
#include <torch/torch.h>

#include <iostream>
//#include <windows.h>

int main(int argc, char** argv) {

  ///LoadLibraryA("torch_hip.dll");

  std::cout << "GPU is available: " << (torch::cuda::is_available() ? "Yes" : "No") << std::endl;

  std::cout << "Creating tensor..." << std::endl;

  // Create a tensor
  int64_t dataSize = 1000;
  torch::Tensor data = torch::zeros({ dataSize }, torch::Device(torch::kHIP));
  std::cout << "Created data tensor" << std::endl << std::flush;

  return 0;
}


