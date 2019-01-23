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

job			object		the amount of income obtained each period
  type			string		allowable values: "AgeLinear" and "Flat". income = round(intercept + slope * age)
AgeLinear				job where income is changes linear with age.  It will round to nearest dollar.
  intercept		float		income at age 0.  Note, first period is age 1.
  slope			float		income change per age.
Flat			integer		job where income is constant across life
  rate			integer		the fixed income per period.  income = rate

health			object		health as a function of fitness and accumulated shock count
  type			string		allowable values: "QuadraticDecline"
QuadraticDecline			health = 1 - (lin_decline * (shocks+1) + quad_decline * (shocks+1)^2)*(1 - max_frac * fitness/(fitness + i))
  linear_decline	real		the linear rate at which health declines with shock count
  quadratic_decline	real		the quadratic rate at which health declines with shock count
  max_prevent_fraction	real		the maximum fraction of the health loss that can be prevented through fitness
  i			real		a number that affects how much fitness affects the amount of health loss prevented

enjoyment		object		the amount of life enjoyment gained as a function of health and joy_investment
  type			string		allowable values: "Fractional"
Fractional				enjoyment = health * spending/(spending + j)
  j			real		a number that affects how much spending affects the amount of joy obtained

fitnesses		object array	A list of objects that together determine how fitness changes each based on current fitness and amount invested period.  Runs each object sequentially.
  type			string 		allowable values: "FixedPrice", "FlatLoss", "ProportionalLoss"
FixedPrice				increases fitness 1 unit for every price spent.  Rounded down.  fitness = fitness + spending/price
  price			int		the price per unit of fitness
FlatLoss				decreases fitness by a fixed amount each period.  fitness = fitness - degen
  degen			int		the amount decreased each period
ProportionalLoss			decreases fitness by a fixed percentage each period. fitness = (1-rate) * fitness
rate			real		the percentage lost each period

probability		object		the probability of a shock each period as a function of health
  type			string		allowable values: "LinearInterpolation"
LinearInterpolation			ranges linearly from a minimum probabilty at health 1, and a max at health 0, prob = health * min_prob + (1-health) * max_prob
  min_prob		real		the probability at 1 health (should be the minimum probability)
  max_prob		real		the probability at 0 health (should be the maximum probability)

insurance		object		the cost of insurance as a function of health.  Insurance prevents the cash loss when shocked.
  type					allowable values: "Actuarial" and "Fixed"
Actuarial				charges the expected cost, scaled by some factor, rounded to the nearest dollar: cost = round(scale * prob * shock_income_size).  Note prob is a function of current health
  scale			real		a factor to scale the cost of insurance by.  1 is actuarially fair, 1.2 is 20% above expected, etc.
Fixed					charges a flat rate regardless of health.  cost = premium
  premium		int		the fixed price of the insurance
  
