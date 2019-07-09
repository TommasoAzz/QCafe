#include "FileException.h"

FileException::FileException(bool ioput, const std::string& message): io(ioput), error_message(message) {}

const char* FileException::what() const noexcept {
    return error_message.c_str();
}

bool FileException::io_mode() const {
    return io;
}
