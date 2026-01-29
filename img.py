import matplotlib.pyplot as plt
import math

# =======================
# DỮ LIỆU THỰC NGHIỆM
# =======================
N = [10000, 20000, 40000, 80000, 160000, 320000, 640000, 1280000, 2560000]

best =  [0.033, 0.13, 0.314, 0.207, 0.494, 1.428, 1.809, 3.243, 7.68]
avg =   [3.435, 8.513, 13.288, 17.582, 37.611, 85.902, 193.718, 376.154, 766.014]
worst = [1.395, 3.144, 3.607, 7.617, 21.796, 38.902, 102.5, 201.471, 326.179]

# =======================
# ĐƯỜNG LÝ THUYẾT
# (CHUẨN HÓA ĐỂ SO SÁNH)
# =======================
# dùng avg tại N nhỏ nhất làm mốc
C = avg[0] / (N[0] * math.log2(N[0]))

n = [C * x for x in N]
nlogn = [C * x * math.log2(x) for x in N]

# scale nlogn để cùng thang với avg
scale = avg[-1] / nlogn[-1]
nlogn = [x * scale for x in nlogn]

# =======================
# VẼ BIỂU ĐỒ
# =======================
plt.figure()

plt.plot(N, best, marker='o', label='Best Case')
plt.plot(N, avg, marker='o', label='Average Case')
plt.plot(N, worst, marker='o', label='Worst Case')

plt.plot(N, n, linestyle='--', label='O(n)')
plt.plot(N, nlogn, linestyle='--', label='O(n log n)')

plt.xlabel("Input Size (N)")
plt.ylabel("Time")
plt.title("Performance vs Theoretical Complexity")
plt.legend()
plt.grid(True)

plt.show()
