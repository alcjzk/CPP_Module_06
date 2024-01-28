#pragma once

class Data
{
    public:
        ~Data() = default;
        Data(int value = 0);
        Data(const Data&) = default;
        Data(Data&&) = default;

        Data& operator=(const Data&) = default;
        Data& operator=(Data&&) = default;

        int     value() const;
        void    value(int value);

    private:
        int _value;
};
