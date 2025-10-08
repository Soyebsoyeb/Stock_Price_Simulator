# 📊 Stock Price Simulator

The **Stock Price Simulator** is a C++ program designed to simulate future prices of a stock using **Geometric Brownian Motion (GBM)** and **Monte Carlo Simulations**.

---

## 🌟 Nature of Stock Prices

Stock prices are random yet somewhat predictable. They are influenced by:

- Market news, earnings, and economic factors  
- Investor behavior  
- Random shocks  

**Statistical properties:**

1. **Non-negative:** Prices cannot go below zero  
2. **Log-normal returns:** Logarithm of returns roughly follows a normal distribution  
3. **Random walk:** Prices move up or down with some average drift and volatility  

---

## 🖼 Screenshots

<div align="center">

<img width="400" alt="Stock Simulator 1" src="https://github.com/user-attachments/assets/070138df-0f40-4c60-8ccf-602cf8572b42" />  
<img width="400" alt="Stock Simulator 2" src="https://github.com/user-attachments/assets/ed3d3488-59bd-4ec1-a8f8-6db00d1168d5" />  
<img width="400" alt="Stock Simulator 3" src="https://github.com/user-attachments/assets/c87961a4-f90e-4bfb-ab2e-28e638e7ff5e" />  
<img width="400" alt="Stock Simulator 4" src="https://github.com/user-attachments/assets/04d45590-903b-4037-ac03-ef485f46034d" />

</div>

---

## 🔑 Key Terms

<div align="center">

<img width="500" alt="Key Terms 1" src="https://github.com/user-attachments/assets/7af8a2f4-ed66-4547-b3ba-5349c463ed1a" />  
<img width="500" alt="Key Terms 2" src="https://github.com/user-attachments/assets/56a86e3b-758b-484d-86d5-8ad32e68096a" />  
<img width="500" alt="Key Terms 3" src="https://github.com/user-attachments/assets/3b8f49dc-40c9-4e43-802e-6f1482424c15" />

</div>

**OS Entropy Pool:** Modern operating systems maintain a pool of randomness collected from unpredictable system events.

- `rd()` → generates a hardware/OS random integer  
- `mt19937 gen(rd())` → initializes the fast PRNG  
- `dis(gen)` → produces uniformly distributed floating-point numbers between 0 and 1  

**Box-Muller Function:** Converts uniform random values to standard normal values, essential for GBM simulations.

**Other Important Terms:**

- **Volatility (σ):** How much a stock price fluctuates. High → big swings, Low → stable  
- **Risk:** Chance stock moves against expectations; partially captured by volatility  
- **Drift (μ):** Expected upward/downward trend  

---

## 📈 Stock Price Simulation

### 1️⃣ Geometric Brownian Motion (GBM)

**Continuous-time SDE (stochastic differential equation):**

dS_t = μ * S_t * dt + σ * S_t * dW_t


Where:  
- `S_t` = stock price at time t  
- `μ` = drift (expected return)  
- `σ` = volatility  
- `W_t` = standard Brownian motion  

**Discrete-time (Euler approximation):**

S_{t+Δt} = S_t * exp[(μ - 0.5 * σ^2) * Δt + σ * sqrt(Δt) * Z]



Where `Z` is a standard normal random variable (Z ~ N(0,1)).  
GBM ensures **log-normal distribution**, which aligns with real-world stock returns.

---

### 2️⃣ Monte Carlo Simulation

Monte Carlo is a **method** to generate many random paths of stock prices.

**Steps:**

1. Define parameters: `S_0`, `μ`, `σ`, `T`  
2. Simulate a single path using GBM  
3. Repeat thousands of times  
4. Analyze the distribution of outcomes  

**Outputs:**

- Expected final price  
- Probability of loss/profit  
- Risk metrics (standard deviation, Value at Risk)  
- Option pricing (e.g., Black-Scholes estimation)  

---

### 🔗 GBM & Monte Carlo Relationship

- **GBM** = the model of price evolution  
- **Monte Carlo** = method to simulate & analyze many GBM paths  

**Analogy:**  
- GBM = the dice rule  
- Monte Carlo = rolling the dice 10,000 times and analyzing results  

---

## 📝 Problem Summary

Stock prices are uncertain. Predicting future values is crucial for **risk management, investments, and options pricing**, but exact prediction is impossible.  

**Goal:** Simulate possible future prices of a stock over a time horizon considering **drift** and **volatility**.

---

## 🔧 Solution Approach

1. **GBM Model:**
   - Simulates stochastic price movement  
   - Incorporates drift (μ) and volatility (σ)  
   - Ensures positivity and log-normal distribution  

2. **Monte Carlo Simulation:**
   - Generates multiple independent GBM paths  
   - Computes mean, standard deviation, probability distribution of outcomes  

---

### ✅ Implementation Overview

- Initialize parameters: `S_0`, `μ`, `σ`, `T`, steps, simulations  
- Run GBM simulation for each path  
- Collect final prices from all simulations  
- Save results for visualization (CSV/graphs)  
- Compute statistics: mean, standard deviation, etc.  

This approach provides a **probabilistic estimate of future stock prices**, widely used in **quantitative finance**.

