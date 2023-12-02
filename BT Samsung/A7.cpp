#include <iostream>
#include <vector>

using namespace std;

class Image {
private:
    vector<vector<int>> pixels;
    int rows, cols;

public:
    Image(int rows, int cols) : rows(rows), cols(cols) {
        pixels.resize(rows, vector<int>(cols, 0));
    }

    void setPixel(int x, int y, int color) {
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            pixels[x][y] = color;
        }
    }

    int getPixel(int x, int y) const {
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            return pixels[x][y];
        }
        return -1;
    }

    void floodFillDFS(int x, int y, int oldColor, int newColor) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || pixels[x][y] != oldColor) {
            return;
        }

        // Đánh dấu điểm ảnh và tiếp tục đệ quy cho các điểm ảnh kề nhau
        pixels[x][y] = newColor;

        floodFillDFS(x - 1, y, oldColor, newColor); // Trái
        floodFillDFS(x + 1, y, oldColor, newColor); // Phải
        floodFillDFS(x, y - 1, oldColor, newColor); // Trên
        floodFillDFS(x, y + 1, oldColor, newColor); // Dưới
    }

    void printImage() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << pixels[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Image image(5, 5);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            image.setPixel(i, j, 2+i);
        }
    }

    cout << "Original Image:" << endl;
    image.printImage();
    cout << endl;

    image.floodFillDFS(2, 2, image.getPixel(2, 2), 99);

    cout << "Image after Flood Fill:" << endl;
    image.printImage();

    return 0;
}

