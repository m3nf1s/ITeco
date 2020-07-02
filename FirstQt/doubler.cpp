#include "doubler.h"

#include <random>
#include <QRandomGenerator>
#include <QMessageBox>

void Doubler::GenerateNewValues(quint16 minimum_value, quint16 maximum_value)
{
    current_value_       = 1;
    current_count_steps_ = 0;
    minimal_count_steps_ = 0;

    std::uniform_int_distribution<int> dis(minimum_value, maximum_value);
    final_value_ = dis(*QRandomGenerator::global());

    quint16 value = final_value_;
    while(value != 1)
    {
        if(value % 2 == 1)
        {
            --value;
            ++minimal_count_steps_;
        }
        else
        {
            value /= 2;
            ++minimal_count_steps_;
        }
    }
}

quint16& Doubler::GetCurrentValue()
{
    return current_value_;
}

quint16& Doubler::GetCurrentCountSteps()
{
    return current_count_steps_;
}

quint16 Doubler::GetCurrentValue() const
{
    return current_value_;
}

quint16 Doubler::GetFinalValue() const
{
    return final_value_;
}

quint16 Doubler::GetCurrentCountSteps() const
{
    return current_count_steps_;
}

quint16 Doubler::GetFinalCountSteps() const
{
    return minimal_count_steps_;
}
