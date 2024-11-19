module;
#include <cmath>
#include <chrono>
#include <random>
#include <thread>
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive

export module wire_market_thread;

import game;

export namespace wire_market_thread
{
    class WireMarket
    {
        float base_wire_price;
        float wire_adjust;
        int wire_adjust_counter;
        std::chrono::steady_clock::time_point last_wire_purchase_time;

        void syncWirePriceToGame(Game& game)
        {
            game.setWirePrice(calculateWirePrice());
        }

    public:
        WireMarket():
            base_wire_price(20.0f),
            wire_adjust(0.0f),
            wire_adjust_counter(0),
            last_wire_purchase_time(std::chrono::steady_clock::now())
        {
        }

        void start_market(ftxui::ScreenInteractive& screen, Game& game)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(1, 8);

            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (dist(gen) == 1)
                {
                    updateWirePrice();
                }
                if (game.getWireBuyerState() && game.getWireStock() < game.getMinimumStock() && game.getWirePrice() <= game.getMaxPrice()) {
                    game.buyWire();
                }

                syncWirePriceToGame(game);

                screen.RequestAnimationFrame();
            }
        }

        void updateWirePrice()
        {
            ++wire_adjust_counter;
            wire_adjust = std::sin(wire_adjust_counter * 0.1f) * 6.0f;

            auto now = std::chrono::steady_clock::now();
            auto time_since_last_purchase = std::chrono::duration_cast<std::chrono::seconds>(
                now - last_wire_purchase_time).count();

            if (time_since_last_purchase >= 25 && base_wire_price > 15.0f)
            {
                base_wire_price -= base_wire_price / 1000.0f;
            }
        }

        float calculateWirePrice() const
        {
            return std::ceil(base_wire_price + wire_adjust);
        }

        void recordWirePurchase()
        {
            base_wire_price += 0.05f; // Augmente le prix de base après un achat
            last_wire_purchase_time = std::chrono::steady_clock::now();
        }
    };
}
