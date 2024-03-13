#include "../cc_learning_test.h"

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string &) = 0;
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string &message) override {
        std::cout << "log(ConsoleLogger) " << message << std::endl;
    }
};

class FileLogger : public ILogger {
public:
    void log(const std::string &message) override {
        std::cout << "log(FileLogger)" << message << std::endl;
    }
};

class Application {
private:
    std::shared_ptr<ILogger> logger_;

public:
    Application(std::shared_ptr<ILogger> logger) :
        logger_(logger){};

    void run(const std::string &message) {
        logger_->log(message);
    }
};

// ./run.sh TestDependencyInjection
TEST(CCTest, TestDependencyInjection) {
    std::shared_ptr<ConsoleLogger> console_logger = std::make_shared<ConsoleLogger>();
    std::shared_ptr<FileLogger> file_logger = std::make_shared<FileLogger>();

    // 将console_logger注入进app1
    Application app1(console_logger);
    app1.run("console logger inject into app1");

    // 将file_logger注入进app2
    Application app2(file_logger);
    app2.run("file logger inject into app2");
}