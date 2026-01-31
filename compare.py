import matplotlib.pyplot as plt

# =======================
# DỮ LIỆU THỰC NGHIỆM
# =======================
N = [

    2560000, 5120000, 10240000,
    20480000, 40960000, 81920000, 163840000
]

tim_sort = [

    374.11, 820.462, 1502.07,
    3347.9, 6794.32, 13629.3, 34914
]

merge_sort = [

    346.277, 780.304, 1532,
    3368.12, 7113.17, 13619.5, 52501.5
]

quick_sort = [

    369.782, 783.887, 1390.98,
    3278.93, 6874.11, 16644.4, 50690.8
]

heap_sort = [

    311.017, 731.489, 1456.75,
    3330.85, 6930.61, 29470.3, 34964.1
]

# =======================
# VẼ BIỂU ĐỒ
# =======================
plt.figure()

plt.plot(N, tim_sort, marker='o', label='Tim Sort')
plt.plot(N, merge_sort, marker='o', label='Merge Sort')
plt.plot(N, quick_sort, marker='o', label='Quick Sort')
plt.plot(N, heap_sort, marker='o', label='Heap Sort')

plt.xlabel("Input Size (N)")
plt.ylabel("Execution Time (ms)")
plt.title("Sorting Algorithms Performance Comparison")

plt.legend()
plt.grid(True)

# Dùng log scale cho trục X để nhìn rõ xu hướng tăng
plt.xscale("log")

plt.tight_layout()
plt.show()
