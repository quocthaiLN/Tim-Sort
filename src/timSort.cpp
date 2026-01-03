#include "timSort.h"

// Tính toán minRun dựa trên kích thước mảng n
int computeMinRun(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1; // Lưu bit thấp nhất
        n >>= 1;    // Dịch phải 1 bit
    }
    return n + r;
}

// Insertion Sort cơ bản
void insertionSort(vector<int> &a, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= left && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Tìm vị trí chèn sử dụng galloping
int gallopLeft(const vector<int> &a, int key, int base, int len)
{
    int ofs = 1;
    int lastOfs = 0;

    // Exponential search
    while (ofs < len && a[base + ofs] < key)
    {
        lastOfs = ofs;
        ofs = (ofs << 1) + 1;
    }
    if (ofs > len)
        ofs = len;

    // Binary search
    return lower_bound(
               a.begin() + base + lastOfs,
               a.begin() + base + ofs,
               key) -
           a.begin();
}

// Merge 2 run liền kề
void mergeRuns(vector<int> &a, Run left, Run right)
{
    // Mảng bên trái tạm thời
    vector<int> L(a.begin() + left.start,
                  a.begin() + left.start + left.length);

    int i = 0;           // Duyệt mảng L
    int j = right.start; // Duyệt mảng a bên phải
    int k = left.start;  // Vị trí ghi vào a
    int gallopCount = 0; // Đếm số lần gallop liên tiếp

    // Merge chuẩn và galloping
    while (i < left.length && j < right.start + right.length)
    {
        if (L[i] <= a[j])
        {
            a[k++] = L[i++];
            gallopCount++;
        }
        else
        {
            a[k++] = a[j++];
            gallopCount = 0;
        }

        // Nếu mảng L chiếm ưu thế, thực hiện galloping
        if (gallopCount >= GALLOP_THRESHOLD && i < left.length)
        {
            // Tìm vị trí gallop trong mảng a bên phải
            int pos = gallopLeft(
                a, L[i], j,
                right.start + right.length - j);
            // Chèn các phần tử từ mảng a bên phải
            while (j < pos)
                a[k++] = a[j++];
            gallopCount = 0;
        }
    }
    // Chèn các phần tử còn lại từ mảng L
    while (i < left.length)
        a[k++] = L[i++];
}

void mergeCollapse(vector<int> &a, vector<Run> &st)
{
    while (st.size() >= 2)
    {
        int n = st.size();

        // A <= B + C
        bool cond1 = (n >= 3 &&
                      st[n - 3].length <= st[n - 2].length + st[n - 1].length);

        // B <= C
        bool cond2 = (st[n - 2].length <= st[n - 1].length);

        if (cond1)
        {
            // ví dụ: [5, 8, 12] -> merge A và B
            if (st[n - 3].length < st[n - 1].length)
            {
                mergeRuns(a, st[n - 3], st[n - 2]);
                st[n - 3].length += st[n - 2].length; // cập nhật độ dài run -> lấy A + B
                st.erase(st.begin() + n - 2);         // xóa run đã merge -> xóa B
            }
            // ví dụ: [13, 8, 12] -> merge B và C
            else
            {
                mergeRuns(a, st[n - 2], st[n - 1]);
                st[n - 2].length += st[n - 1].length; // cập nhật độ dài run -> lấy B + C
                st.pop_back();                        // xóa run đã merge -> xóa C
            }
        }
        else if (cond2)
        {
            mergeRuns(a, st[n - 2], st[n - 1]);
            st[n - 2].length += st[n - 1].length; // cập nhật độ dài run -> lấy B + C
            st.pop_back();                        // xóa run đã merge -> xóa C
        }
        else
        {
            break;
        }
    }
}

// Hàm chính của Tim Sort
void timSort(vector<int> &a, int n)
{
    // Lấy kích thước minRun
    int minRun = computeMinRun(n);
    // Tạo stack lưu trữ các run
    vector<Run> st;

    // Phân tích mảng thành các run
    for (int i = 0; i < n;)
    {
        int start = i;
        i++;
        // Tìm run giảm -> đảo ngược nó
        if (i < n && a[i - 1] > a[i])
        {

            while (i < n && a[i - 1] > a[i])
                i++;
            reverse(a.begin() + start, a.begin() + i);
        }
        // Tìm run tăng -> giữ nguyên
        else
        {

            while (i < n && a[i - 1] <= a[i])
                i++;
        }

        int len = i - start;

        // Nếu run quá ngắn, mở rộng nó bằng Insertion Sort
        if (len < minRun)
        {
            int end = min(start + minRun, n);
            insertionSort(a, start, end - 1);
            len = end - start;
            i = end;
        }

        // Đẩy run vào stack
        st.push_back({start, len});

        // Kiểm tra và hợp nhất các run trên stack
        mergeCollapse(a, st);
    }

    // Hợp nhất các run còn lại trên stack
    while (st.size() > 1)
    {
        mergeRuns(a, st[st.size() - 2], st.back());
        st[st.size() - 2].length += st.back().length;
        st.pop_back();
    }
}
