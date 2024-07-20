#include "WGCommandQueue.hpp"

int WGCommandQueue::Initialize(WGPUInstance instance, const std::shared_ptr<WGDevice> &device) {
    mQueue = device->GetQueue();
    return 0;
}

void WGCommandQueue::Finalize() {}
