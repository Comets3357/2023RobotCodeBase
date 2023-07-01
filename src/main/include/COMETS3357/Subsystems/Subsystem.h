#pragma once



namespace COMETS3357
{
    template <typename State>
    class Subsystem
    {
    public:

        void SetState(State state)
        {
            m_state = state;
        }

    private:

        State m_state;

    };
};