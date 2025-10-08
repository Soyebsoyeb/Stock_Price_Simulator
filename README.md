# Stock_Price_Simulator

The Stock Price Simulator is a C++ program designed to simulate 
the future prices of a stock using geometric Brownian Motion and Monte Carlo Simulations.

(1) THE NATURE OF STOCK PRICES :->
  Stock prices are random and predictable influenced by:
  (a) Market news , earnings , economic factors.
  (b) Investor behaviour.
  (c) Random shocks.


Yet, they exhibit some statistical properties:->
(1) Non-negative -> A stock price can't go below zero
(2) Returns are approximately log - normal -> the logarithm of stock returns roughly follows a normal distribution
(3) Random Walk -> prices move up or down with some average drift and volatility


 
<img width="560" height="633" alt="Screenshot 2025-10-08 124651" src="https://github.com/user-attachments/assets/070138df-0f40-4c60-8ccf-602cf8572b42" />

<img width="595" height="765" alt="Screenshot 2025-10-08 125408" src="https://github.com/user-attachments/assets/ed3d3488-59bd-4ec1-a8f8-6db00d1168d5" />

<img width="663" height="811" alt="Screenshot 2025-10-08 125452" src="https://github.com/user-attachments/assets/c87961a4-f90e-4bfb-ab2e-28e638e7ff5e" />

<img width="699" height="798" alt="Screenshot 2025-10-08 125850" src="https://github.com/user-attachments/assets/04d45590-903b-4037-ac03-ef485f46034d" />



Some important terms we should know:
<img width="821" height="348" alt="Screenshot 2025-10-08 131850" src="https://github.com/user-attachments/assets/7af8a2f4-ed66-4547-b3ba-5349c463ed1a" />

<img width="707" height="691" alt="Screenshot 2025-10-08 132920" src="https://github.com/user-attachments/assets/56a86e3b-758b-484d-86d5-8ad32e68096a" />

<img width="528" height="883" alt="Screenshot 2025-10-08 133317" src="https://github.com/user-attachments/assets/3b8f49dc-40c9-4e43-802e-6f1482424c15" />


What is an OS entropy pool?

Modern operating systems (Linux, Windows, macOS) maintain a pool of randomness called the entropy pool.
This is like a big bucket of unpredictable bits collected from various unpredictable events in the system.


Terms:

rd() → produces a hardware/OS random integer
mt19937 gen(rd()) → initializes the fast PRNG with that seed
dis(gen) → produces uniformly distributed floating-point numbers between 0 and 1



// Box Muller function 
To convert uniform value to normal value as normal distribution is where mostly the nature of law


Important Terms:
(1) Volatility: How much a stock price fluctuates over time.
      It is represented by sigma
      In finance:-> measured as standard deviation of returns  
   High volatility → big swings in price
   Low volatility → price moves slowly and steadily

(2) Risk: The chance that the stock price will move against your expectations
  (*) Volatility is one measure of risks
  (*) Risk is captured by the "Spread of Stimulated Outcomes".

  double stddev = sqrt(sq_sum / simulations - meanPrice*meanPrice);
  
  <img width="319" height="93" alt="Screenshot 2025-10-08 140359" src="https://github.com/user-attachments/assets/4eaf8310-e369-4921-9f59-b0d6cb1bb5ab" />

(3) Drift: It is the expected upward or downward trend of the stock
           It is represented by mu



GBM and MonteCarlo the main algorithms for this purpose:


## 📈 Stock Price Simulation

This project simulates stock prices using **Geometric Brownian Motion (GBM)** and evaluates outcomes with **Monte Carlo simulation**.

---

### 1. Geometric Brownian Motion (GBM)

This is the **standard model** used in finance for simulating stock prices.

**Formula (continuous-time stochastic differential equation):**

\[
dS_t = \mu S_t \, dt + \sigma S_t \, dW_t
\]

Where:
- \( S_t \) = stock price at time \( t \)  
- \( \mu \) = drift (expected return)  
- \( \sigma \) = volatility  
- \( W_t \) = standard Brownian motion (randomness)  

**Discrete-time simulation (Euler approximation):**

\[
S_{t+\Delta t} = S_t \cdot \exp \Big[ \big(\mu - \tfrac{1}{2}\sigma^2\big)\Delta t + \sigma \sqrt{\Delta t} \cdot Z \Big]
\]

where \( Z \sim N(0,1) \) (standard normal random variable).

🔹 GBM assumes **log-normal distribution** of prices, which aligns better with real-world stock returns than a normal distribution.

---

### 2. Monte Carlo Simulation

Monte Carlo is not a model itself, but a **method**: run many random simulations of stock price paths (using GBM or another model) and analyze the results.

**Steps:**
1. Define model parameters \((S_0, \mu, \sigma, T)\)  
2. Simulate one stock price path using GBM  
3. Repeat thousands of times (each run is a “trial”)  
4. Collect outcomes → build a distribution of possible prices  

**From this, we can estimate:**
- Expected final price  
- Probability of loss/profit  
- Value at Risk (VaR)  
- Option pricing (e.g., Black-Scholes can be derived using Monte Carlo with GBM)  

---

### ✨ Relationship between GBM & Monte Carlo

- **GBM** = the model of stock dynamics  
- **Monte Carlo** = the computational method to generate and analyze many GBM paths  

📊 **Analogy:**  
- GBM = the dice rule (e.g., “roll a die, add to score”)  
- Monte Carlo = rolling the die 10,000 times and analyzing the distribution of results  

---

## 📝 Problem Summary

Stock prices are inherently uncertain and fluctuate over time. Predicting their future values is crucial in finance for **risk management, investment decisions, and option pricing**. However, due to randomness in the market, exact prediction is impossible.  

**Problem:**  
Simulate the future behavior of a single stock over a given time horizon, accounting for both **expected returns** and **volatility**, and estimate the statistical properties of its possible outcomes.

---

## 🔧 Solution Approach

To solve this problem, we use a combination of **Geometric Brownian Motion (GBM)** and **Monte Carlo simulation**:

1. **Geometric Brownian Motion (GBM):**
   - A mathematical model that represents the stochastic evolution of stock prices.
   - Accounts for both:
     - **Drift** (\( \mu \)) → expected return
     - **Volatility** (\( \sigma \)) → randomness
   - Ensures stock prices remain positive and follow a **log-normal distribution**.
   - Discretized using:
     \[
     S_{t+\Delta t} = S_t \cdot \exp \Big[ (\mu - 0.5\sigma^2)\Delta t + \sigma \sqrt{\Delta t} \cdot Z \Big]
     \]
     where \( Z \sim N(0,1) \) is a standard normal random variable.

2. **Monte Carlo Simulation:**
   - Runs **many independent simulations** of stock price paths using GBM.
   - Each simulation represents one possible future outcome of the stock.
   - Aggregates results to compute:
     - **Expected final price**
     - **Standard deviation** (risk)
     - **Probability distribution** of prices
   - Allows statistical analysis and visualization of stock behavior.

---

### ✅ Implementation Overview

- Initialize model parameters: \( S_0 \) (initial price), \( \mu \) (drift), \( \sigma \) (volatility), \( T \) (time horizon), number of steps, and number of simulations.  
- Simulate each stock path using GBM.  
- Collect final prices from all simulations.  
- Save results to a CSV file for visualization.  
- Compute summary statistics (mean, standard deviation) to understand the range of possible outcomes.

This approach provides a **probabilistic estimate of future stock prices**, which is widely used in **quantitative finance** and **risk management**.




   


