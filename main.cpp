#include <iostream>
#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>
#include <dxgi.h>
#include <d3d11.h>

int main() {
    std::cout << "Testing Eigen with DirectX on Windows\n";

    try {
        // Create a simple tensor
        Eigen::Tensor<float, 2> a(2, 3);
        a.setValues({
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f}
        });

        // Setup DirectX device
        ID3D11Device* device;
        ID3D11DeviceContext* context;
        D3D_FEATURE_LEVEL featureLevel;
        
        HRESULT hr = D3D11CreateDevice(
            nullptr,                    // Default adapter
            D3D_DRIVER_TYPE_HARDWARE,  // Hardware acceleration
            nullptr,                    // No software driver
            0,                         // No flags
            nullptr,                    // Feature levels
            0,                         // Number of feature levels
            D3D11_SDK_VERSION,         // SDK version
            &device,                   // Device
            &featureLevel,             // Actual feature level
            &context                   // Device context
        );

        if (FAILED(hr)) {
            throw std::runtime_error("Failed to create DirectX device");
        }

        // Create buffer description
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(float) * 6;  // 2x3 tensor
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        bufferDesc.CPUAccessFlags = 0;

        // Create initial data
        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = a.data();

        // Create buffer
        ID3D11Buffer* buffer;
        hr = device->CreateBuffer(&bufferDesc, &initData, &buffer);
        if (FAILED(hr)) {
            throw std::runtime_error("Failed to create buffer");
        }

        // Print results
        std::cout << "Original tensor:\n" << a << "\n";

        // Cleanup
        buffer->Release();
        context->Release();
        device->Release();
        
        std::cout << "Test completed successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}