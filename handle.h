#ifndef PANDEMIC_HANDLE_H
#define PANDEMIC_HANDLE_H

#include <string>

struct handle {
    inline handle() : name{} {
    }

    inline explicit handle(std::string name) : name{name} {
    }

    friend auto operator==(handle const &lhs, handle const &rhs) -> bool;

    friend auto operator<<(std::ostream &os, const handle &h) -> std::ostream &;

    friend struct std::hash<handle>;

private:
    std::string name;
};

inline auto operator ""_h(char const *s, std::size_t count) -> handle {
    return handle{std::string{s, count}};
}

inline auto operator==(handle const &lhs, handle const &rhs) -> bool {
    return lhs.name == rhs.name;
}

inline auto operator<<(std::ostream &os, const handle &h) -> std::ostream & {
    os << h.name;
    return os;
}

namespace std {
    template<>
    struct hash<handle> {
        using argument_type = handle;
        using result_type = std::size_t;

        result_type operator()(argument_type const &s) const {
            return std::hash<std::string>{}(s.name);
        }
    };
}

#endif //PANDEMIC_HANDLE_H
