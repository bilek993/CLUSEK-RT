//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_BASESYSTEM_H
#define CLUSEK_RT_BASESYSTEM_H

#include <string>

class BaseSystem
{
public:
    void Start();
    void Update(float deltaTime);

    void Enable();
    void Disable();
    [[nodiscard]] bool IsEnabled() const;

    virtual std::string GetName() = 0;

protected:
    virtual void StartSystem() = 0;
    virtual void UpdateSystem(float deltaTime) = 0;

private:
    bool Enabled = true;
};


#endif //CLUSEK_RT_BASESYSTEM_H
