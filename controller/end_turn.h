#ifndef PANDEMIC_END_TURN_H
#define PANDEMIC_END_TURN_H

#include "controller.h"

struct end_turn : controller {
    virtual auto name() const -> std::string override;

    virtual auto description() const -> std::string override;

    virtual auto run(context &ctx, args_t const &args, ostream_t &out) const -> void override;
};

#endif //PANDEMIC_END_TURN_H
