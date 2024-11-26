module;
#include <thread>  // For std::thread, std::this_thread
#include <chrono>  // For std::chrono
#include <algorithm> // For std::min
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive

export module timer_thread;

import game;

export namespace timer_thread
{
    class TimerThread
    {
        const float& public_demand;
        int min_delay_ms;
        int max_delay_ms;
        int delay_ms;

    public:
        TimerThread(const float& public_demand)
            : public_demand(public_demand)
        {
            update_delay();
        }

        void auto_sell_paperclips(int& unsold_paperclips, float& funds, float& price, ftxui::ScreenInteractive& screen)
        {
            while (true)
            {
                update_delay();
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

                int chance = rand() % 100 + 1;

                int pb_demand_i = static_cast<int>(public_demand);
                if (chance <= pb_demand_i)
                {
                    if (unsold_paperclips > 0)
                    {
                        int max_possible_sale = std::min(unsold_paperclips, 10);
                        int sold = rand() % max_possible_sale + 1;
                        unsold_paperclips -= sold;
                        funds += sold * price;
                    }
                }
                screen.RequestAnimationFrame();
            }
        }

        void update_delay()
        {

            float effective_demand = std::max(public_demand, 1.0f);

            float base_delay = 100.0f;

            min_delay_ms = static_cast<int>(base_delay * std::exp(-effective_demand / 50.0f));
            max_delay_ms = min_delay_ms + 500;

            delay_ms = min_delay_ms + (rand() % (max_delay_ms - min_delay_ms + 1));

        }
    };
}
