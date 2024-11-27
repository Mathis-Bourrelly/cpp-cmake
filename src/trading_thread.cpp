
module;
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <format>  // C++23 pour formater les chaînes de caractères

export module trading_thread;
/*
import game;  // Importation du module Game

export class TradingThread {
public:
    TradingThread(Game& game);

    void depositFunds(float amount);
    void withdrawFunds();
    void setRiskLevel(int level);
    void start(auto& screen);

private:
    Game& game;          // Référence au jeu
    float cash;          // Fonds du joueur
    float investment;    // Argent investi dans la bourse
    float market_price;  // Prix actuel de la bourse
    float buy_price;     // Prix d'achat de la bourse
    int risk_level;      // Niveau de risque (1: faible, 2: moyen, 3: élevé)
    std::random_device rd;
    std::mt19937 gen;

    void updateMarketPrice();
    float getRiskMultiplier();
    void displayStatus();
};

// Constructeur de TradingThread
TradingThread::TradingThread(Game& game)
    : game(game), cash(0.0f), investment(0.0f), market_price(100.0f), buy_price(0.0f), risk_level(2), gen(rd()) {}

// Déposer des fonds dans la bourse
void TradingThread::depositFunds(float amount) {
    if (amount <= 0.0f) {
        std::cout << "Invalid deposit amount!" << std::endl;
        return;
    }
    if (cash < amount) {
        std::cout << "Not enough cash available!" << std::endl;
        return;
    }
    if (investment > 0.0f) {
        std::cout << "You already have an active investment! Withdraw first." << std::endl;
        return;
    }

    investment = amount;
    cash -= amount;
    buy_price = market_price;

    std::cout << std::format("Invested {:.2f} at market price {:.2f}", amount, market_price) << std::endl;
}

// Retirer les fonds de la bourse
void TradingThread::withdrawFunds() {
    if (investment <= 0.0f) {
        std::cout << "No active investment to withdraw!" << std::endl;
        return;
    }

    float value = (investment / buy_price) * market_price;  // Valeur de l'investissement
    float profit_or_loss = value - investment;

    cash += value;
    investment = 0.0f;
    buy_price = 0.0f;

    std::cout << std::format("Withdrew {:.2f}. Profit/Loss: {:.2f}", value, profit_or_loss) << std::endl;
}

// Définir le niveau de risque
void TradingThread::setRiskLevel(int level) {
    if (level >= 1 && level <= 3) {
        risk_level = level;
        std::cout << std::format("Risk level set to {}", risk_level) << std::endl;
    } else {
        std::cout << "Invalid risk level!" << std::endl;
    }
}

// Mettre à jour le prix de la bourse
void TradingThread::updateMarketPrice() {
    float risk_multiplier = getRiskMultiplier();
    std::uniform_real_distribution<float> price_change_dist(-risk_multiplier, risk_multiplier);

    market_price += price_change_dist(gen);

    // Empêcher les prix négatifs
    if (market_price < 1.0f) {
        market_price = 1.0f;
    }
}

// Retourner le multiplicateur de risque
float TradingThread::getRiskMultiplier() {
    switch (risk_level) {
        case 1: return 2.0f;  // Faible risque
        case 2: return 5.0f;  // Risque moyen
        case 3: return 10.0f; // Risque élevé
        default: return 5.0f;
    }
}

// Afficher l'état actuel
void TradingThread::displayStatus() {
    std::cout << std::format("Cash: {:.2f} | Market Price: {:.2f} | Investment: {:.2f} | Buy Price: {:.2f}",
                             cash, market_price, investment, buy_price)
              << std::endl;

    if (investment > 0.0f) {
        float value = (investment / buy_price) * market_price;
        float profit_or_loss = value - investment;

        std::cout << std::format("Current Value: {:.2f} | Profit/Loss: {:.2f}", value, profit_or_loss) << std::endl;
    }
}

// Démarrer la simulation de la bourse
void TradingThread::start(auto& screen) {
    while (true) {
        // Mettre à jour le prix du marché
        updateMarketPrice();

        // Afficher l'état actuel
        displayStatus();

        // Pause entre les mises à jour
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }
}
*/
