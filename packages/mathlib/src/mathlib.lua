-- mathlib: Simple math utilities for REX projects

local mathlib = {}

-- Returns the sum of two numbers
function mathlib.add(a, b)
  return a + b
end

-- Returns the difference of two numbers
function mathlib.sub(a, b)
  return a - b
end

-- Returns the product of two numbers
function mathlib.mul(a, b)
  return a * b
end

-- Returns the quotient of two numbers; errors on division by zero
function mathlib.div(a, b)
  if b == 0 then
    error("mathlib.div: division by zero")
  end
  return a / b
end

-- Returns the absolute value of a number
function mathlib.abs(n)
  if n < 0 then return -n end
  return n
end

return mathlib
