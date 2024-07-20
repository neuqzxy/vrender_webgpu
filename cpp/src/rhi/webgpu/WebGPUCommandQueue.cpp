#include "WebGPUCommandQueue.hpp"

int WebGPUCommandQueue::Initialize(WGPUInstance instance, const std::shared_ptr<WebGPUDevice> &device) {
    mQueue = device->GetQueue();
    return 0;
}

void WebGPUCommandQueue::Finalize() {}
