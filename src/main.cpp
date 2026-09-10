#include "LicenseServer.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace {
void printStatus(const LicenseServer& server) {
    std::cout << "\nLicense pool status\n";
    for (const auto& item : server.status()) {
        std::cout << "  " << item.product << ": " << item.inUse << "/"
                  << item.total << " in use\n";
    }
}
}

int main() {
    std::cout << "3Delight-style License Workflow Demo\n"
              << "Educational simulation only; not connected to 3Delight.\n";

    LicenseServer server;
    server.addProduct("3Delight-Render", 2);

    std::vector<std::optional<LicenseLease>> leases;
    for (const std::string client : {"WORKSTATION-01", "WORKSTATION-02", "WORKSTATION-03"}) {
        auto lease = server.checkout("3Delight-Render", client);
        if (lease) {
            std::cout << "GRANTED: " << client << " received " << lease->token << '\n';
        } else {
            std::cout << "DENIED:  " << client << " (all seats are in use)\n";
        }
        leases.push_back(std::move(lease));
    }

    printStatus(server);
    if (leases.front()) {
        std::cout << "\nCHECK-IN: " << leases.front()->client << " returned "
                  << leases.front()->token << '\n';
        server.checkin(leases.front()->token);
    }

    auto retry = server.checkout("3Delight-Render", "WORKSTATION-03");
    std::cout << (retry ? "RETRY GRANTED" : "RETRY DENIED") << ": WORKSTATION-03\n";
    printStatus(server);
    return retry ? 0 : 1;
}

