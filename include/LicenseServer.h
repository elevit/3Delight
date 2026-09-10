#pragma once

#include <cstddef>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct LicenseLease {
    std::string token;
    std::string product;
    std::string client;
};

struct ProductStatus {
    std::string product;
    std::size_t total;
    std::size_t inUse;
};

// Educational in-memory simulation; this is not a 3Delight API implementation.
class LicenseServer {
public:
    void addProduct(std::string product, std::size_t seats);
    std::optional<LicenseLease> checkout(const std::string& product,
                                         const std::string& client);
    bool checkin(const std::string& token);
    std::vector<ProductStatus> status() const;

private:
    struct ProductPool {
        std::size_t total = 0;
        std::size_t inUse = 0;
    };

    mutable std::mutex mutex_;
    std::unordered_map<std::string, ProductPool> products_;
    std::unordered_map<std::string, LicenseLease> leases_;
    unsigned long long nextToken_ = 1;
};

