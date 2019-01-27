Basic Parameters

max_age			integer		number of periods
max_fitness		integer		maximum allowable fitness
max_shocks		integer		maximum allowable shocks (more shocks can occur, but shock count will not increase)
max_savings		integer		maximum cash you can end a period with (truncated)
min_savings		integer 	minimum cash you can end a period with (truncated)
min_debt_payment	real		precentage of debt (cash below 0) 0 that is deducted from income
shock_income_size	integer		cash loss when shocked
shock_count_size	integer		number of shock count accumulated upon shock



Function Parameters

job			object		the amount of income obtained each period as a function of age
  type			string		allowable values: "AgeLinear" and "Flat". income = round(intercept + slope * age)
AgeLinear				job where income is changes linear with age.  It will round to nearest dollar.
  intercept		float		income at age 0.  Note, first period is age 1.
  slope			float		income change per age.
Flat			integer		job where income is constant across life
  rate			integer		the fixed income per period.  income = rate

enjoyment		object		the amount of life enjoyment gained as a function of shocks and joy_investment
  type			string		allowable values: "Fractional"
Fractional				enjoyment = (1 - shock_emphasis * shocks/max_shocks) * spending/(spending + j)
  j			real		a number that affects how much spending affects the amount of joy obtained
  shock_emphasis	real		a number between 0-1.  Determines fraction of enjoyment lost from shocks

fitnesses		object array	A list of objects that together determine how fitness changes each based on current fitness and amount invested period.  Runs each object sequentially.
  type			string 		allowable values: "FixedPrice", "FlatLoss", "ProportionalLoss"
FixedPrice				increases fitness 1 unit for every price spent.  Rounded down.  fitness = fitness + spending/price
  price			int		the price per unit of fitness
FlatLoss				decreases fitness by a fixed amount each period.  fitness = fitness - degen
  degen			int		the amount decreased each period
ProportionalLoss			decreases fitness by a fixed percentage each period. fitness = (1-rate) * fitness
rate			real		the percentage lost each period

probability		object		the probability of a shock each period as a function of age, shocks, and fitness
  type			string		allowable values: "LinearInterpolation"
GompertzMakeham				probability follows a Gompertz-Makeham mortality hazard curve.  P(shock) = lambda + alpha * e^(age * beta)
  lambda		real
  alpha			real
  beta			real

insurance		object		the cost of insurance as a function of age, shocks, and fitness.  Insurance prevents the cash loss when shocked.
  type					allowable values: "Actuarial" and "Fixed"
Actuarial				charges the expected cost, scaled by some factor, rounded to the nearest dollar: cost = round(scale * prob * shock_income_size).  Note prob is a function of current age, shocks, and fitness
  scale			real		a factor to scale the cost of insurance by.  1 is actuarially fair, 1.2 is 20% above expected, etc.
Fixed					charges a flat rate regardless of circumstance.  cost = premium
  premium		int		the fixed price of the insurance
  
