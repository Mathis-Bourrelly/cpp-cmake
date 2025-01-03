module;
#include <thread>  // For std::thread, std::this_thread
#include <chrono>  // For std::chrono
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive

export module auto_clipper_thread;

import game;

export namespace auto_clipper_thread
{
    class AutoClipper
    {
        const int& autoclipper_level;

    public:
        AutoClipper(const int& autoclipper_level)
            : autoclipper_level(autoclipper_level)
        {
        }

        void auto_make_paperclips(ftxui::ScreenInteractive& screen, Game& game)
        {
            while (true)
            {
                if (autoclipper_level > 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / autoclipper_level));
                    game.makePaperclip(1);
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }

            }
            screen.RequestAnimationFrame();
        }
    };
}
