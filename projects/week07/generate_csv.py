import random
import math
import datetime
import os

random.seed(42)

S = 476.32
mu = 0.0001
sigma = 0.015

os.makedirs("data", exist_ok=True)

prices = [S]
for _ in range(999):
    z = random.gauss(0, 1)
    S = S * math.exp((mu - 0.5 * sigma ** 2) + sigma * z)
    prices.append(S)

date = datetime.date(2024, 1, 2)
rows = []
for i, p in enumerate(prices):
    while date.weekday() >= 5:
        date += datetime.timedelta(days=1)
    rows.append((str(date), f"{p:.4f}"))
    date += datetime.timedelta(days=1)

badrow_positions = {199, 499, 799}

with open("data/prices.csv", "w") as f:
    f.write("date,price\n")
    for i, (d, p) in enumerate(rows):
        if i in badrow_positions:
            f.write("BADROW\n")
        f.write(f"{d},{p}\n")

print(f"Written {len(rows)} price rows + {len(badrow_positions)} BADROW entries to data/prices.csv")
