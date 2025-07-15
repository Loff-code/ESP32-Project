bool iv(int from, int to)
{
  return (second >= from && second <= to);
}

template <typename... Args>
void check(Args... args)
{
  bool cond = (args || ...); // Fold expression to evaluate OR for all arguments
  if (cond && !checkState)
  {
    // Serial.println("Hello");
    checkState = true;
    stateReg = ACTION;
  }
  else if (!cond)
  {
    checkState = false; // Reset the flag if outside the interval
  }
}

bool everyX(int x)
{
  bool a = iv(0, 3);
  for (size_t i = 1; i < 60 / x; i++)
  {
    a = a || iv(x * i - 1, x * i + 1);
  }
  return a;
}