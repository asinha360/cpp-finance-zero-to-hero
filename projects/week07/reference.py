import math

prices = []
bad_rows = 0

with open("data/prices.csv") as f:
    next(f)  # skip header
    for line in f:
        line = line.strip()
        pos = line.find(',')
        if pos == -1:
            bad_rows += 1
            continue
        try:
            prices.append(float(line[pos + 1:]))
        except ValueError:
            bad_rows += 1

log_rets = [math.log(prices[i + 1] / prices[i]) for i in range(len(prices) - 1)]

n = len(log_rets)
mean_val = sum(log_rets) / n
variance = sum((r - mean_val) ** 2 for r in log_rets) / (n - 1)
stdev = math.sqrt(variance)

print(f"Rows loaded:      {len(prices)}")
print(f"Bad rows skipped: {bad_rows}")
print(f"Log returns:      {n}")
print(f"Mean:             {mean_val:.10f}")
print(f"Stdev:            {stdev:.10f}")
