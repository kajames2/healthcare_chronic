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

job			object		the income obtained each period as a function of age
  type			string		allowable value: "AgeLinear", "Flat"

AgeLinear				income = round(intercept + slope * age)
  intercept		float		income at age 0.  Note, first period, age = 1.
  slope			float		income change per age.

Flat					income = rate --- Fixed income.  Equivalent to AgeLinear with 0 slope.
  rate			integer		the fixed income per period.  income = rate



joy			object		the amount of life enjoyment gained as a function of age, shocks, fitness, joy_investment
  type			string		allowable values: "Fractional"
  mod			object		modifier function

Fractional				enjoyment = spending/(spending + j)
  j			real		




fitnesses		object array	A list of objects that together determine how fitness changes each period based on current fitness and amount invested.  Runs each object sequentially.
  type			string 		allowable values: "FixedPrice", "QuadraticCost", "FlatLoss", "ProportionalLoss"

FixedPrice				fitness_(t+1) = fitness_t + flooar(spending/price) --- Increases fitness 1 unit for every price spent.  Round down.
  price			int		

QuadraticCost				fitness_(t+1) = fitness_t + floor(sqrt(spending/coeff)) --- Cost of fitness grows quadratically.  Rounds down.
  coeff			float		

FlatLoss				fitness_(t+1) = fitness_t - degen --- Decreases fitness by a fixed amount each period.
  degen			int		

ProportionalLoss			fitness_(t+1) = ceil((1-rate) * fitness_t) --- Decreases fitness by a fixed percentage each period.  Rounds up.
  rate			real		the percentage lost each period




probability		object		the probability of a shock each period as a function of age, shocks, and fitness
  type			string		allowable values: "GompertzMakeham", "GompertzShocks"
  mod			object		modulator function
  
GompertzMakeham				P(shock) = lambda + alpha * e^(age * beta) --- probability follows a Gompertz-Makeham mortality hazard curve.
  lambda		real
  alpha			real
  beta			real

GompertzShocks				P(shock) = (age_coeff * e^(age * age_rate) + shock_coeff * e^(shock * shock_rate)) * modifier(shocks, fitness) --- Probability follows a modified Gompertz to include shocks
  age_coeff		real
  age_rate		real
  shock_coeff		real
  shock_rate		real




modifier				functions that modify the probability/joy functions.  Multiple modifiers can be composited together.
func			string		Allowable values: "Add", "Multiply".  Determines whether the modifier adds to or multiplies the current value.
type		        string		Allowable values: "Linear", "Cosine", "Fractional", "Constant"
param			string		Allowable values: "Age", "Fitness", "Shocks".  (Note, not used for "Constant" type)

Constant		object		value
  value			real

Linear			object		1 - max_modifier * param/max_param
  max_modifier		real

CosineShock		object		1 - max_modifier * cos(pi/(2*max_param) * param)
  max_modifier		real

FractionalShock		object		1 - max_modifier * param/(param + j)
  max_modifier		real		
  j			real		



insurance		object		the cost of insurance as a function of age, shocks, and fitness.  Insurance prevents the cash lost when shocked.
  type					allowable values: "Actuarial" and "Fixed"

Actuarial				cost = round(scale * prob * shock_income_size) --- Charges the expected cost, scaled by some factor, rounded to the nearest dollar.  Note: prob is a function of current age, shocks, and fitness
  scale			real		a factor to scale the cost of insurance by.  1 is actuarially fair, 1.2 is 20% above expected, etc.
  admin_cost		int		a fixed increase in premiums above actuarial

Fixed					cost = premium --- Charges a flat rate regardless of circumstance.  
  premium		int		the fixed price of the insurance
