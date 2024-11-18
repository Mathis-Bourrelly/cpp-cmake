module;

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
export module ui;

import game;

using namespace ftxui;

export void StartUI(Game& game, auto& screen) {
    auto make_paperclip_button = Button("Make Paperclip", [&] { game.makePaperclip(); });
    auto decrease_price_button = Button("Decrease Price", [&] { game.decreasePrice(); });
    auto increase_price_button = Button("Increase Price", [&] { game.increasePrice(); });
    auto buy_marketing_button = Button("Increase Marketing", [&] { game.buyMarketing(); });
    auto buy_autoclipper_button = Button("Buy Auto Clipper", [&] { game.buyAutoClipper(); });

    auto button_container = Container::Vertical({
        make_paperclip_button,
        decrease_price_button,
        increase_price_button,
        buy_marketing_button,
        buy_autoclipper_button,
    });

    auto layout = Renderer(button_container, [&] {
        return vbox({
            text("Paperclips: " + std::to_string(game.getPaperclipCount())) | bold,
            text("Unsold Paperclips: " + std::to_string(game.getUnsoldPaperclips())) | bold,
            text("Funds: $" + std::format("{0:.2f}",game.getFunds())) | bold | color(Color::Green),
            separator(),
            text("Price: $" + std::format("{0:.2f}",game.getPrice())) | color(Color::Yellow),
            hbox({
                decrease_price_button->Render() | flex,
                increase_price_button->Render() | flex,
            }),
            separator(),
            text("Marketing Level: " + std::to_string(game.getMarketingLevel())) | bold,
            text("Cost: $" + std::format("{0:.2f}",game.getMarketingCost())) | color(Color::Yellow),
            text("Public Demand: " + std::to_string(static_cast<int>(game.getPublicDemand())) + "%") | bold | color(Color::Cyan),
            buy_marketing_button->Render(),
            separator(),
            text("Auto Clippers: " + std::to_string(game.getAutoClipperLevel())) | bold,
            text("Cost: $" + std::format("{0:.2f}",game.getAutoClipperCost())) | color(Color::Yellow),
            buy_autoclipper_button->Render(),
            separator(),
            make_paperclip_button->Render(),
        }) | border;
    });

    screen.Loop(layout);
}
