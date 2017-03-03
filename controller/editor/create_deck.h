#ifndef PANDEMIC_CREATE_DECK_H
#define PANDEMIC_CREATE_DECK_H

#include "../controller.h"

struct create_deck : controller {
    virtual auto name() const -> std::string override;

    virtual auto description() const -> std::string override;

    virtual auto run(context &c, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_CREATE_DECK_H
