Edge AI Challenge 2026!
Liệu mạng nơ-ron của bạn có thể chạy vừa trong một vi điều khiển không?

Edge AI Challenge 2026 thách thức bạn xây dựng một mô hình nhận dạng biển báo giao thông chạy hoàn toàn trên vi điều khiển ESP32-S3 — không cloud, không GPU, không chip gia tốc ngoài. Chỉ có mô hình của bạn, 512KB SRAM và bộ xử lý Xtensa LX7 dual-core.

Cuộc thi được tổ chức bởi CLB Sinh viên Nghiên cứu Khoa học Pioneer thuộc Khoa Điện tử - Viễn thông, Trường Đại học Bách khoa – ĐH Đà Nẵng, cùng sự hỗ trợ từ Công ty Cổ phần Công nghệ NeuralTrans, Công ty MetaSquare và Công ty Cổ phần BKLOGY. Đây là sân chơi dành cho sinh viên đam mê lĩnh vực giao thoa giữa học sâu và hệ thống nhúng — một lĩnh vực đang phát triển mạnh mẽ mang tên TinyML và Edge AI.

🎯 Bài toán
Nhiệm vụ của bạn là xây dựng một mô hình phân loại ảnh siêu nhẹ nhận dạng chính xác các biển báo giao thông, tuân thủ các ràng buộc phần cứng nghiêm ngặt:

Đầu vào: Ảnh RGB888 kích thước 32×32 pixels (3.072 bytes/ảnh)
Đầu ra: Nhãn biển báo (ví dụ: Stop, Turn Left, Turn Right, Speed Limit, No Entry, …) dưới dạng các class id từ 0 - 9.
Ràng buộc cứng: Số lượng tham số mô hình < 200.000 — không dùng Pre-trained model lớn, không dùng Ensemble.
Bảng xếp hạng Vòng Loại chỉ dựa trên Accuracy trên tập Private Test. Các đội xuất sắc nhất sẽ tiến vào Vòng Chung kết Offline, nơi mô hình được nạp trực tiếp lên board ESP32-S3 N16R8 tiêu chuẩn và đánh giá cả độ chính xác lẫn tốc độ suy luận.

⚙️ Tại sao bài toán này khó?
Triển khai AI trên vi điều khiển là một thách thức kỹ thuật hoàn toàn khác so với huấn luyện trên GPU hay deploy lên cloud server hoặc các thiết bị có phần cứng mạnh:

Bạn phải lượng tử hóa (quantize) mô hình từ float32 → int8 để vừa với Flash và SRAM
Bạn phải khai thác tăng tốc phần cứng thông qua AI Vector Instructions của ESP32-S3 bằng framework ESP-DL
Từng kilobyte RAM và từng mili-giây inference đều ảnh hưởng trực tiếp đến điểm số tại Vòng Chung kết
Bạn phải tối ưu cả mô hình & phần cứng để đảm bảo mô hình đạt hiệu năng cao nhất trên ESP32-S3
🔧 Công cụ & Framework cho phép
Giai đoạn	Công cụ
Huấn luyện	TensorFlow, PyTorch
Tối ưu hóa	TensorFlow Lite, ESP-DL
Triển khai	ESP-IDF, Arduino
Tăng tốc	AI Vector Instructions trên ESP32-S3
