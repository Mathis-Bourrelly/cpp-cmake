module;
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <iostream>
#include <ftxui/component/screen_interactive.hpp>  // For ScreenInteractive


export module trading_thread;

import game;

export class TradingThread
{
public:
    TradingThread(Game& game);

    // Thread management
    void start(ftxui::ScreenInteractive& screen);
    void stop();

    // Core trading operations
    void depositFunds();
    void withdrawFunds();
    void updateStocks();

    void setRiskLevel(int risk); // 1 = High, 5 = Medium, 7 = Low
    int getRiskLevel() const;

    // Upgrade investment engine
    void upgradeEngine();

private:
    Game& game;
    std::random_device rd;
    std::mt19937 gen;

    float calculateStockChange(float price, float fluctuation_factor);
};

TradingThread::TradingThread(Game& game)
    : game(game), gen(rd())
{
}

void TradingThread::start(ftxui::ScreenInteractive& screen)
{
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Update every 2.5 seconds
            updateStocks();
            screen.RequestAnimationFrame();
        }
}


void TradingThread::depositFunds()
{
    float amount = game.getFunds();
    // Le montant à déposer est égal à l'argent disponible (funds)
    game.getTradingCash() += amount;
    game.getFunds() = 0; // Retirer tout l'argent du portefeuille du joueur

    // Calculer la nouvelle valeur des stocks à partir de l'argent déposé
    float stock_value = amount * (1 + game.getProfitLossRatio()); // Le profit/perte est calculé ici
    game.getTradingStocks() += stock_value;

    // Calculer la nouvelle valeur totale (cash + stocks)
    game.getTradingTotal() = game.getTradingCash() + game.getTradingStocks();
}

void TradingThread::withdrawFunds()
{
    // Retirer tout l'argent en cash (pas les stocks)
    game.getFunds() += game.getTradingCash();
    game.getTradingCash() = 0; // Mettre les fonds du marché à 0
    game.getTradingTotal() = game.getTradingCash() + game.getTradingStocks();
}

void TradingThread::updateStocks()
{
    std::uniform_real_distribution<float> random_change(0.0f, 1.0f);
    float fluctuation_factor;

    // Calculer le facteur de fluctuation selon le risque
    switch (game.getTradingRiskLevel()) {
    case 0: fluctuation_factor = 0.05f; break; // Low risk
    case 1: fluctuation_factor = 0.1f; break;  // Medium risk
    case 2: fluctuation_factor = 0.15f; break; // High risk
    default: fluctuation_factor = 0.05f; break; // Default to Low risk
    }

    // Mettre à jour les prix des actions
    for (auto& price : game.getStockPrices())
    {
        if (random_change(gen) < 0.6f) // 60% de chance de fluctuation
        {
            float price_change = calculateStockChange(price, fluctuation_factor);
            price += price_change;

            // Enregistrer l'effet sur les stocks et mettre à jour les valeurs
            game.getTradingStocks() += price_change;
            game.getTradingTotal() = game.getTradingCash() + game.getTradingStocks();
        }
    }
}

float TradingThread::calculateStockChange(float price, float fluctuation_factor)
{
    std::uniform_real_distribution<float> change(-fluctuation_factor * price, fluctuation_factor * price);
    return change(gen);
}

void TradingThread::setRiskLevel(int risk)
{
    switch (risk)
    {
    case 1: game.getTradingRiskLevel() = 7; break; // Low risk
    case 2: game.getTradingRiskLevel() = 5; break; // Medium risk
    case 3: game.getTradingRiskLevel() = 1; break; // High risk
    default: game.getTradingRiskLevel() = 7; break; // Default to Low risk
    }
}

int TradingThread::getRiskLevel() const
{
    return game.getTradingRiskLevel();
}

void TradingThread::upgradeEngine()
{
    game.getTradingEngineLevel()++;
    game.getProfitLossRatio() += 0.01f; // Augmente légèrement le ratio de profit/perte
}