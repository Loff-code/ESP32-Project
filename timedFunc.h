bool iv(int from, int to){
  return (second >= from && second <= to);
}

template<typename... Args>
void check(Args... args) {
    bool cond = (args || ...); // Fold expression to evaluate OR for all arguments
    if (cond && !checkState) {
        Serial.println("Hello");
        checkState = true;
        actionState = true;
    } else if (!cond) {
        checkState = false; // Reset the flag if outside the interval
    }
}