#pragma once
#include "Bird.h"

class DetectiveGoose : public Bird
{
    public:
    // Constructor, Destructor and Skill function
    DetectiveGoose(std::string);
    ~DetectiveGoose();
    void Skill(BirdList*);
};