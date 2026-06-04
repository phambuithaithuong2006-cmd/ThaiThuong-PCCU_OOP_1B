/**
 * @file Wolf.h
 * @brief Declares the concrete predator species `Wolf`.
 *
 * @details
 * `Wolf` specializes `Animal` by implementing movement, predation, and
 * reproduction rules. This class is used by `World` through polymorphic
 * `Animal*` pointers.
 */

#pragma once

#include "Animal.h"
#include"World.h"
#include<string>
#include<ctime>

class Wolf : public Animal {
public:
    Wolf(int x, int y);
    ~Wolf() override = default;

    void move(World& world) override;
    void eat(World& world) override;
    void reproduce(World& world) override;
};
