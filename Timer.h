#pragma once

class ImpTimer
{
    public:
        ImpTimer();
        ~ImpTimer();

        void start();// bắt đầu
        void stop();// dừng lại
        void pause();// tạm dừng
        void unpause();// tiếp tục

        int get_ticks();

        bool is_started();
        bool is_paused();
    private:

        int start_tick_;// bắt đầu
        int paused_tick_;// tạm dừng

        bool is_paused_;// kiểm tra có tạm dừng không
        bool is_started_;// kiểm tra có bắt đầu không
};
