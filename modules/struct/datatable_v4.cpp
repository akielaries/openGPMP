#include <optional>
#include <string>
#include <vector>

class MyClass {
    public:
    using Axes = std::vector<int>; // assuming `Axes` is a type alias for a
                                   // vector of integers
    MyClass(std::optional<Data> data = std::nullopt,
            std::optional<Axes> index = std::nullopt,
            std::optional<Axes> columns = std::nullopt,
            std::optional<bool> copy = std::nullopt) {
        this->data = data;
        this->index = index;
        this->columns = columns;
        this->copy = copy;
    }

    private:
    std::optional<Data> data;
    std::optional<Axes> index;
    std::optional<Axes> columns;
    std::optional<bool> copy;
};
