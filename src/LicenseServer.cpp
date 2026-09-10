#include "LicenseServer.h"

#include <algorithm>
#include <sstream>
#include <utility>

void LicenseServer::addProduct(std::string product, std::size_t seats) {
    std::lock_guard<std::mutex> lock(mutex_);
    products_[std::move(product)].total = seats;
}

std::optional<LicenseLease> LicenseServer::checkout(const std::string& product,
                                                    const std::string& client) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto productIt = products_.find(product);
    if (productIt == products_.end() || productIt->second.inUse >= productIt->second.total) {
        return std::nullopt;
    }

    std::ostringstream token;
    token << "DEMO-" << nextToken_++;
    LicenseLease lease{token.str(), product, client};
    leases_.emplace(lease.token, lease);
    ++productIt->second.inUse;
    return lease;
}

bool LicenseServer::checkin(const std::string& token) {
    std::lock_guard<std::mutex> lock(mutex_);
    const auto leaseIt = leases_.find(token);
    if (leaseIt == leases_.end()) {
        return false;
    }

    const auto productIt = products_.find(leaseIt->second.product);
    if (productIt != products_.end() && productIt->second.inUse > 0) {
        --productIt->second.inUse;
    }
    leases_.erase(leaseIt);
    return true;
}

std::vector<ProductStatus> LicenseServer::status() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<ProductStatus> result;
    result.reserve(products_.size());
    for (const auto& entry : products_) {
        result.push_back({entry.first, entry.second.total, entry.second.inUse});
    }
    std::sort(result.begin(), result.end(), [](const auto& left, const auto& right) {
        return left.product < right.product;
    });
    return result;
}

