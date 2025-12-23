#include <iostream>
#include <algorithm>
#include <stdexcept>  
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;

public:
    DynamicArray(int arraySize) {
        size = arraySize;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void setValue(int index, int value) {
        if (index < 0 || index >= size) {
            throw out_of_range("Error: index out of bounds!");
        }
        if (value < -100 || value > 100) {
            throw invalid_argument("Error: value must be between -100 and 100!");
        }
        data[index] = value;
    }

    int getValue(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Error: index out of bounds!");
        }
        return data[index];
    }

    void pushBack(int value) {
        if (value < -100 || value > 100) {
            throw invalid_argument("Error: value must be between -100 and 100!");
        }

        int newSize = size + 1;
        int* newData = new int[newSize];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        newData[size] = value;
        delete[] data;
        data = newData;
        size = newSize;
    }

    void fillFromUser() {
        cout << "Enter " << size << " array elements (values from -100 to 100):" << endl;
        for (int i = 0; i < size; i++) {
            int value;
            cout << "Element [" << i << "]: ";
            cin >> value;
            setValue(i, value);
        }
    }

    void setValues(int* values, int count) {
        for (int i = 0; i < size && i < count; i++) {
            if (values[i] < -100 || values[i] > 100) {
                throw invalid_argument("Error: value must be between -100 and 100!");
            }
            data[i] = values[i];
        }
    }

    void add(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            if (i < other.size) {
                data[i] += other.data[i];
            }
        }
    }

    void sub(const DynamicArray& other) {
        for (int i = 0; i < size; i++) {
            if (i < other.size) {
                data[i] -= other.data[i];
            }
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int getSize() const {
        return size;
    }
};

class ExtendedDynamicArray : public DynamicArray {
public:
    ExtendedDynamicArray(int arraySize) : DynamicArray(arraySize) {}

    ExtendedDynamicArray(const ExtendedDynamicArray& other) : DynamicArray(other) {}

    double getAverage() {
        if (getSize() == 0) {
            return 0;
        }

        double sum = 0;
        for (int i = 0; i < getSize(); i++) {
            sum += getValue(i);
        }
        return sum / getSize();
    }

    double getMedian() {
        int size = getSize();
        if (size == 0) {
            return 0;
        }

        int* temp = new int[size];
        for (int i = 0; i < size; i++) {
            temp[i] = getValue(i);
        }

        sort(temp, temp + size);

        double median;
        if (size % 2 == 0) {
            median = (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
        }
        else {
            median = temp[size / 2];
        }

        delete[] temp;
        return median;
    }

    int getMin() {
        if (getSize() == 0) {
            return 0;
        }

        int minVal = getValue(0);
        for (int i = 1; i < getSize(); i++) {
            if (getValue(i) < minVal) {
                minVal = getValue(i);
            }
        }
        return minVal;
    }

    int getMax() {
        if (getSize() == 0) {
            return 0;
        }

        int maxVal = getValue(0);
        for (int i = 1; i < getSize(); i++) {
            if (getValue(i) > maxVal) {
                maxVal = getValue(i);
            }
        }
        return maxVal;
    }
};

int main() {
    try {
        int size;
        cout << "Enter array size: ";
        cin >> size;

        ExtendedDynamicArray arr(size);
        arr.fillFromUser();

        cout << "Your array: ";
        arr.print();

        cout << "Average: " << arr.getAverage() << endl;
        cout << "Median: " << arr.getMedian() << endl;
        cout << "Min: " << arr.getMin() << endl;
        cout << "Max: " << arr.getMax() << endl;

    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        return 1;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}