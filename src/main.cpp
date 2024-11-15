#include <ftxui/component/component.hpp>  // For components
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive
#include <ftxui/dom/elements.hpp>  // For elements
#include <thread>  // For std::thread, std::this_thread
#include <chrono>  // For std::chrono
#include <atomic>  // For std::atomic
#include <cmath>   // For std::pow
#include <string>  // For std::to_string

int main()
{
    using namespace ftxui;
    using namespace std;

    // Variables principales
    int paperclip_count{0};
    int unsold_paperclips{0};
    float price{0.50};
    int marketing_level{0};
    float public_demand{0.16};
    float funds{0.0};
    float marketing_cost{200.0};


    // Calcul de la Public Demand avec la nouvelle formule
    auto calculate_public_demand = [&]()
    {
        public_demand = pow(1.1, marketing_level) * (8.001 / price);
    };


    // Initialisation de la Public Demand
    calculate_public_demand();

    // Fonction de vente automatique


    // Boutons et leur logique
    auto make_paperclip_button = Button("Make Paperclip", [&]
    {
        paperclip_count ++;
        unsold_paperclips ++;
    });

    auto decrease_price_button = Button("Increase Price", [&] {
        float current_price = price;
        if (current_price > 0.01f) { // Bloque le prix en dessous de 0.01$
            price -= 0.01f;
        } else {
            price = 0.01f; // Assure que le prix ne descend pas sous 0.01$
        }
        calculate_public_demand(); // Recalculer après modification
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


    auto auto_sell_paperclips = [&]()
    {
        while (true)
        {
            this_thread::sleep_for(chrono::seconds(1)); // Simulation de temps
            screen.PostEvent(Event::Custom);
            int to_sell = static_cast<int>(public_demand); // Basé sur PD
            if (unsold_paperclips > 0 && to_sell > 0)
            {
                int sold = min(unsold_paperclips, to_sell);
                unsold_paperclips -= sold;
                funds += sold * price;
            }
        }
    };

    // Lancement de la vente automatique dans un thread
    thread(auto_sell_paperclips).detach();

    screen.Loop(layout);
    return 0;
}
