#include "ScreenShoter.hpp"
#include <boost/beast/core/detail/base64.hpp>
#include <vector>

ScreenShoter::ScreenShoter(Xibo::Window& window) : window_(window) {}

void ScreenShoter::takeBase64(const ScreenShotTaken& callback)
{
    takeScreenshotNative(nativeWindow(), [callback = std::move(callback)](const ImageBuffer& buffer) {
        // Calculate the size of the base64-encoded output
        std::size_t encodedSize = boost::beast::detail::base64::encoded_size(buffer.size());

        // Allocate a buffer for the base64-encoded output
        std::vector<char> base64Buffer(encodedSize);

        // Perform the base64 encoding
        std::size_t actualSize = boost::beast::detail::base64::encode(
            base64Buffer.data(), // Output buffer
            buffer.data(),       // Input data
            buffer.size()        // Input data size
        );

        // Resize the buffer to the actual encoded size
        base64Buffer.resize(actualSize);

        // Pass the base64-encoded data to the callback
        callback(std::string(base64Buffer.data(), base64Buffer.size()));
    });
}

NativeWindow ScreenShoter::nativeWindow() const
{
    return window_.nativeWindow();
}
