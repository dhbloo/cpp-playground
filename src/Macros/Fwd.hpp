#pragma once

/// A helper to forward variadic arguments.
#define FWD(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)