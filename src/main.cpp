
#include <ftxui/component/component.hpp>  // For components
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <ftxui/dom/elements.hpp>  // For elements
#include <thread>  // For std::thread, std::this_thread
#include <chrono>  // For std::chrono
#include <cmath>   // For std::pow
#include <string>  // For std::to_string
/*
int main()
{
    using namespace ftxui;
    using namespace std;

    int paperclip_count{0};
    int unsold_paperclips{0};
    float price{0.50};
    int marketing_level{0};
    float public_demand{0.16};
    float funds{0.0};
    float marketing_cost{200.0};



    auto calculate_public_demand = [&]()
    {
        public_demand = pow(1.1, marketing_level) * (8.001 / price);
    };

    calculate_public_demand();



    auto make_paperclip_button = Button("Make Paperclip", [&]
    {
        paperclip_count ++;
        unsold_paperclips ++;
    });

    auto decrease_price_button = Button("Increase Price", [&] {
        float current_price = price;
        if (current_price > 0.01f) {
            price -= 0.01f;
        } else {
            price = 0.01f;
        }
        calculate_public_demand();
    });

    auto increase_price_button = Button("Increase Price", [&]
    {
        price += 0.01f;
        calculate_public_demand();
    });

    auto buy_marketing_button = Button("Increase Marketing", [&]
    {
        if (funds >= marketing_cost)
        {
            funds -= marketing_cost;
            ++marketing_level;
            marketing_cost *= 2; // Coût exponentiel
            calculate_public_demand();
        }
    });


    // Conteneur des boutons
    auto button_container = Container::Vertical({
        make_paperclip_button,
        decrease_price_button,
        increase_price_button,
        buy_marketing_button,
    });

    // Rendu global de l'interface
    auto layout = Renderer(button_container, [&]
    {
        return vbox({
            text("Paperclips: " + to_string(paperclip_count)) | bold,
            text("Unsold Paperclips: " + to_string(unsold_paperclips)) | bold,
            text("Funds: $" + format("({:.2f})",funds)) | bold | color(Color::Green),
            separator(),
            text("Price: $" + format("({:.2f})",price)) | color(Color::Yellow),
            hbox({
                decrease_price_button->Render() | flex,
                increase_price_button->Render() | flex,
            }),
            separator(),
            text("Marketing Level: " + to_string(marketing_level)) | bold,
            text("Next Marketing Cost: $" + format("({:.2f})",marketing_cost)) | color(Color::Yellow),
            text("Public Demand: " + to_string(static_cast<int>(public_demand)) + "%") | bold | color(
                Color::Cyan),
            buy_marketing_button->Render(),
            separator(),
            make_paperclip_button->Render(),
        }) | border;
    });

    // Boucle principale
    auto screen = ScreenInteractive::TerminalOutput();

    auto auto_sell_paperclips = [&]() {
        while (true) {
            // Générer un délai basé sur la Public Demand
            float pd = public_demand; // Public Demand actuelle
            int min_delay_ms = static_cast<int>(1000.0f / (1.0f + pd / 100.0f)); // Réduit le délai avec une PD plus haute
            int max_delay_ms = min_delay_ms + 800; // Ajoute une variation aléatoire
            int delay_ms = min_delay_ms + (rand() % (max_delay_ms - min_delay_ms + 1));

            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

            // Générer une probabilité pour tenter de vendre un ou plusieurs paperclips
            int chance = rand() % 100 + 1; // Aléatoire entre 1 et 100
            if (chance <= static_cast<int>(pd)) { // Comparer avec PD en pourcentage
                if (unsold_paperclips > 0) {
                    // Tirer un nombre aléatoire de paperclips à vendre (entre 1 et 10)
                    int max_possible_sale = min(unsold_paperclips, 10);
                    int sold = rand() % max_possible_sale + 1; // Entre 1 et max_possible_sale
                    unsold_paperclips -= sold; // Déduire les paperclips vendus
                    funds += sold * price; // Ajouter le revenu total
                }
            }

            // Mettre à jour l'interface
            screen.PostEvent(Event::Custom);
        }
    };



    // Lancement de la vente automatique dans un thread
    thread(auto_sell_paperclips).detach();

    screen.Loop(layout);
    return 0;
}
*/

import game;
import ui;
import timer_thread;
import auto_clipper_thread;

int main() {
    Game game;

    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    timer_thread::TimerThread auto_sell_thread(game.getPublicDemand());
    std::thread([&]() {
        auto_sell_thread.auto_sell_paperclips(
            game.getUnsoldPaperclips(),
            game.getFunds(),
            game.getPrice(),
            screen);
    }).detach();

    auto_clipper_thread::AutoClipper auto_clipper_thread(game.getAutoClipperLevel());
    std::thread([&]() {
        auto_clipper_thread.auto_make_paperclips(
            game.getUnsoldPaperclips(),
            game.getPaperclipCount(),
            screen);
    }).detach();


    StartUI(game, screen);
    return 0;
}

