#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <opencv2/opencv.hpp>

void imageToAudio(const std::string& imagePath, const std::string& audioPath) {
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Unable to read image: " << imagePath << std::endl;
        return;
    }
    int width = image.cols;
    int height = image.rows;
    std::ofstream audioFile(audioPath, std::ios::out | std::ios::binary);
    if (!audioFile.is_open()) {
        std::cerr << "Unable to open audio file: " << audioPath << std::endl;
        return;
    }
    audioFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
    audioFile.write(reinterpret_cast<const char*>(&height), sizeof(height));
    std::vector<uint8_t> imageData;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            uint8_t pixelValue = image.at<uint8_t>(y, x);
            audioFile.write(reinterpret_cast<const char*>(&pixelValue), sizeof(pixelValue));
        }
    }
    audioFile.close();
    std::cout << "Image converted to audio successfully." << std::endl;
}

int main() {
    std::string imagePath = "input_image.jpg";
    std::string audioPath = "output_audio.dat";
    imageToAudio(imagePath, audioPath);
    return 0;
}
