// main.cpp
#include "ProxyImage.h"
#include "RealImage.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Proxy Pattern Demo ===\n";

    int choice;

    do {
        cout << "\nChọn chế độ:\n";
        cout << "1. Dùng RealImage (tải ảnh ngay lập tức)\n";
        cout << "2. Dùng ProxyImage (lazy load + hỏi xác nhận)\n";
        cout << "0. Thoát chương trình\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        Image* img = nullptr;

        switch (choice) {
            case 1:
                cout << "\n[Client] Tạo RealImage:\n";
                img = new RealImage("real_image.jpg");
                cout << "\n[Client] Gọi display():\n";
                img->display();
                delete img;
                break;

            case 2:
                cout << "\n[Client] Tạo ProxyImage:\n";
                img = new ProxyImage("proxy_image.jpg");
                cout << "\n[Client] Gọi display():\n";
                img->display();
                delete img;
                break;

            case 0:
                cout << "\n[Client] Thoát chương trình.\n";
                break;

            default:
                cout << "\n[Error] Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
