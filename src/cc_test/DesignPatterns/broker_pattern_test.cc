#include "../cc_learning_test.h"

#include <unordered_map>

namespace cc_test {
namespace broker_test {
class Service {
public:
    virtual std::string process(const std::string &message) = 0;
};

class ServiceImpl : public Service {
public:
    std::string process(const std::string &message) override {
        return message + " handled";
    }
};

class ServiceRegistry {
private:
    std::unordered_map<std::string, Service *> services;

public:
    void register_service(const std::string &service_name, Service *service) {
        services[service_name] = service;
    }

    Service *get_service(const std::string &service_name) {
        return services[service_name];
    }
};

class Broker {
private:
    ServiceRegistry &_registry;

public:
    Broker(ServiceRegistry &registry) :
        _registry(registry){};
    std::string handle_service(const std::string service_name, const std::string &message) {
        Service *service = _registry.get_service(service_name);
        return service->process(message);
    }
};

TEST(CCTest, BrokerPatternTest) {
    ServiceImpl service;
    ServiceRegistry service_registry;
    service_registry.register_service("my_service", &service);

    Broker broker(service_registry);
    std::string result = broker.handle_service("my_service", "hell world");
    std::cout << "handle result: " << result << std::endl;
}

}
} // namespace cc_test::broker_test